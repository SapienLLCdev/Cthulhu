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

package com.tencent.squeezencnn;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

import java.io.FileNotFoundException;
import java.nio.charset.StandardCharsets;
import java.util.Arrays;

public class MainActivity extends Activity
{
    private static final int SELECT_IMAGE = 1;

    private TextView infoResult;
    private ImageView imageView;
    private Bitmap yourSelectedImage = null;

    private SqueezeNcnn squeezencnn = new SqueezeNcnn();

    /** A 4x4 grid to store information from LAYER_pool10 */
    private byte[][] mGridVals;
    /** An instance of the {@link CthulhuUsbInterface} class used to communicate with a Cthulhu device */
    private CthulhuUsbInterface mCthulhu;

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);

        boolean ret_init = squeezencnn.Init(getAssets());
        if (!ret_init)
        {
            Log.e("MainActivity", "squeezencnn Init failed");
        }

        mCthulhu = new CthulhuUsbInterface(this);
        mCthulhu.connectUsb();

        infoResult = (TextView) findViewById(R.id.infoResult);
        imageView = (ImageView) findViewById(R.id.imageView);

        Button buttonImage = (Button) findViewById(R.id.buttonImage);
        buttonImage.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                Intent i = new Intent(Intent.ACTION_PICK);
                i.setType("image/*");
                startActivityForResult(i, SELECT_IMAGE);
            }
        });

        Button buttonDetect = (Button) findViewById(R.id.buttonDetect);
        buttonDetect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                if (yourSelectedImage == null)
                    return;

                Bitmap result = squeezencnn.Detect(yourSelectedImage, false);

                if (result == null)
                {
                    infoResult.setText("detect failed");
                }
                else
                {
                    //infoResult.setText(result);
                    Bitmap rgba = result.copy(Bitmap.Config.ARGB_8888, true);
                    // resize to 7x7
                    yourSelectedImage = Bitmap.createScaledBitmap(rgba, 7, 7, false);
                    rgba.recycle();

                    imageView.setImageBitmap(result);


                    // Reset grid values
                    mGridVals = new byte[4][4];

                    int[] pixels = new int[7*7];
                    yourSelectedImage.getPixels(pixels, 0, yourSelectedImage.getWidth(), 0, 0, 7, 7);

                    // If a CthulhuUsbInterface has been supplied, send data to turn on LEDs in response to LAYER_pool10 image
                    if(mCthulhu != null) {
                        String send = "";
                        // jump 2 rows of 7x7
                        int jump = 2*7;
                        for(int j = 0; j < 4; j++) {

                            for(int i = 0; i < 4; i++) {
                                int pixel = pixels[j+i+jump];

                                int a = (pixel>>24) & 0xff; //get alpha
                                int r = (pixel>>16) & 0xff; //get red
                                int g = (pixel>>8) & 0xff; //get green
                                int b = pixel & 0xff; //get blue

                                // take max value from RGB channels
                                int maxC = Math.max(Math.max(r,g),b);
                                // maxC can't be 0
                                mGridVals[j][i] = (byte)(maxC == 0 ? 1 : maxC);
                                send += (char) mGridVals[j][i];
                            }
                            // next row same column
                            jump +=7;
                        }
                        // add first 0 for the array end, second will be added on the arduino
                        send += "\0";

                        infoResult.setText(Arrays.toString(send.getBytes()));
                        mCthulhu.write(send.getBytes());
                    }

                    yourSelectedImage = null;
                }
            }
        });

        Button buttonDetectGPU = (Button) findViewById(R.id.buttonDetectGPU);
        buttonDetectGPU.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View arg0) {
                if (yourSelectedImage == null)
                    return;

                Bitmap result = squeezencnn.Detect(yourSelectedImage, true);

                if (result == null)
                {
                    infoResult.setText("detect failed");
                }
                else
                {
                    imageView.setImageBitmap(result);
                    yourSelectedImage = null;
                }
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data)
    {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == RESULT_OK && null != data) {
            Uri selectedImage = data.getData();

            try
            {
                if (requestCode == SELECT_IMAGE) {
                    Bitmap bitmap = decodeUri(selectedImage);

                    Bitmap rgba = bitmap.copy(Bitmap.Config.ARGB_8888, true);

                    // resize to 227x227
                    yourSelectedImage = Bitmap.createScaledBitmap(rgba, 227, 227, false);

                    rgba.recycle();

                    imageView.setImageBitmap(bitmap);
                }
            }
            catch (FileNotFoundException e)
            {
                Log.e("MainActivity", "FileNotFoundException");
                return;
            }
        }
    }

    private Bitmap decodeUri(Uri selectedImage) throws FileNotFoundException
    {
        // Decode image size
        BitmapFactory.Options o = new BitmapFactory.Options();
        o.inJustDecodeBounds = true;
        BitmapFactory.decodeStream(getContentResolver().openInputStream(selectedImage), null, o);

        // The new size we want to scale to
        final int REQUIRED_SIZE = 400;

        // Find the correct scale value. It should be the power of 2.
        int width_tmp = o.outWidth, height_tmp = o.outHeight;
        int scale = 1;
        while (true) {
            if (width_tmp / 2 < REQUIRED_SIZE
               || height_tmp / 2 < REQUIRED_SIZE) {
                break;
            }
            width_tmp /= 2;
            height_tmp /= 2;
            scale *= 2;
        }

        // Decode with inSampleSize
        BitmapFactory.Options o2 = new BitmapFactory.Options();
        o2.inSampleSize = scale;
        return BitmapFactory.decodeStream(getContentResolver().openInputStream(selectedImage), null, o2);
    }

}
