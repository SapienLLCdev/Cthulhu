// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2017 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include <android/asset_manager_jni.h>
#include <android/bitmap.h>
#include <android/log.h>

#include <jni.h>

#include <string>
#include <vector>

// ncnn
#include "net.h"
#include "benchmark.h"

#include "squeezenet_v1.1.id.h"

static ncnn::UnlockedPoolAllocator g_blob_pool_allocator;
static ncnn::PoolAllocator g_workspace_pool_allocator;

static std::vector<std::string> squeezenet_words;
static ncnn::Net squeezenet;

static std::vector<std::string> split_string(const std::string& str, const std::string& delimiter)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}

static std::vector<std::pair<float, int> > print_topk(const std::vector<float>& cls_scores, int topk)
{
    // partial sort topk with index
    int size = cls_scores.size();
    std::vector<std::pair<float, int> > vec;
    vec.resize(size);
    for (int i = 0; i < size; i++)
    {
        vec[i] = std::make_pair(cls_scores[i], i);
    }

    std::partial_sort(vec.begin(), vec.begin() + topk, vec.end(),std::greater<std::pair<float, int> >());

    // print topk and score
    for (int i = 0; i < topk; i++)
    {
        float score = vec[i].first;
        int index = vec[i].second;
        fprintf(stderr, "%d = %f\n", index, score);
    }

    return vec;
}

extern "C" {

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    __android_log_print(ANDROID_LOG_DEBUG, "SqueezeNcnn", "JNI_OnLoad");

    ncnn::create_gpu_instance();

    return JNI_VERSION_1_4;
}

JNIEXPORT void JNI_OnUnload(JavaVM* vm, void* reserved)
{
    __android_log_print(ANDROID_LOG_DEBUG, "SqueezeNcnn", "JNI_OnUnload");

    ncnn::destroy_gpu_instance();
}

// public native boolean Init(AssetManager mgr);
JNIEXPORT jboolean JNICALL Java_com_tencent_squeezencnn_SqueezeNcnn_Init(JNIEnv* env, jobject thiz, jobject assetManager)
{
    ncnn::Option opt;
    opt.lightmode = true;
    opt.num_threads = 4;
    opt.blob_allocator = &g_blob_pool_allocator;
    opt.workspace_allocator = &g_workspace_pool_allocator;

    // use vulkan compute
    if (ncnn::get_gpu_count() != 0)
        opt.use_vulkan_compute = true;

    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);

    squeezenet.opt = opt;

    // init param
    {
        int ret = squeezenet.load_param_bin(mgr, "squeezenet_v1.1.param.bin");
        if (ret != 0)
        {
            __android_log_print(ANDROID_LOG_DEBUG, "SqueezeNcnn", "load_param_bin failed");
            return JNI_FALSE;
        }
    }

    // init bin
    {
        int ret = squeezenet.load_model(mgr, "squeezenet_v1.1.bin");
        if (ret != 0)
        {
            __android_log_print(ANDROID_LOG_DEBUG, "SqueezeNcnn", "load_model failed");
            return JNI_FALSE;
        }
    }

    // init words
    {
        AAsset* asset = AAssetManager_open(mgr, "synset_words.txt", AASSET_MODE_BUFFER);
        if (!asset)
        {
            __android_log_print(ANDROID_LOG_DEBUG, "SqueezeNcnn", "open synset_words.txt failed");
            return JNI_FALSE;
        }

        int len = AAsset_getLength(asset);

        std::string words_buffer;
        words_buffer.resize(len);
        int ret = AAsset_read(asset, (void*)words_buffer.data(), len);

        AAsset_close(asset);

        if (ret != len)
        {
            __android_log_print(ANDROID_LOG_DEBUG, "SqueezeNcnn", "read synset_words.txt failed");
            return JNI_FALSE;
        }

        squeezenet_words = split_string(words_buffer, "\n");
    }

    return JNI_TRUE;
}

// public native String Detect(Bitmap bitmap, boolean use_gpu);
JNIEXPORT jobject JNICALL Java_com_tencent_squeezencnn_SqueezeNcnn_Detect(JNIEnv* env, jobject thiz, jobject bitmap, jboolean use_gpu)
{
    if (use_gpu == JNI_TRUE && ncnn::get_gpu_count() == 0)
    {
        return env->NewStringUTF("no vulkan capable gpu");
    }

    double start_time = ncnn::get_current_time();

    AndroidBitmapInfo info;
    AndroidBitmap_getInfo(env, bitmap, &info);
    int width = info.width;
    int height = info.height;
    if (width != 227 || height != 227)
        return NULL;
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
        return NULL;

    // ncnn from bitmap
    ncnn::Mat in = ncnn::Mat::from_android_bitmap(env, bitmap, ncnn::Mat::PIXEL_BGR);

    // squeezenet
    std::vector<float> cls_scores;
    {
        const float mean_vals[3] = {104.f, 117.f, 123.f};
        in.substract_mean_normalize(mean_vals, 0);

        ncnn::Extractor ex = squeezenet.create_extractor();

        ex.set_vulkan_compute(use_gpu);

        ex.input(squeezenet_v1_1_param_id::BLOB_data, in);
        std::vector<ncnn::Mat> weights(0);


        ncnn::Mat pool10;
        ex.extract(squeezenet_v1_1_param_id::LAYER_pool10, pool10);
        jobject bitmapOut = bitmap;
        pool10.to_android_bitmap(env, bitmapOut, ncnn::Mat::PIXEL_BGR);

        return bitmapOut;

        // manualy apply softmax on pool10 output
        ncnn::Mat out = pool10;
        {
            ncnn::Layer* softmax = ncnn::create_layer("Softmax");

            ncnn::ParamDict pd;
            //pd.set(1, 1);
            softmax->load_param(pd);

            softmax->forward_inplace(out, squeezenet.opt);
            //out = out.reshape(out.w * out.h * out.c);

            delete softmax;
        }

        // sort top 3 softmax channels out of
        cls_scores.resize(out.c);
        for (int j = 0; j < out.c; j++) { cls_scores[j] = out[j]; }
        std::vector<std::pair<float, int> > vec = print_topk(cls_scores, 3);

        // get 3 pool10 channels by their top softmax
        ncnn::Mat ch1 = pool10.channel(vec.at(0).first);
        ncnn::Mat ch2 = pool10.channel(vec.at(1).first);
        ncnn::Mat ch3 = pool10.channel(vec.at(2).first);

        //ch1.to_android_bitmap(env, bitmapOut, ncnn::Mat::PIXEL_CONVERT_SHIFT);

    }

}

}
