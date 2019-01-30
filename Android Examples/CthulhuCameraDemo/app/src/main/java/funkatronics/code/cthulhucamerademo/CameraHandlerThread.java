package funkatronics.code.cthulhucamerademo;

import android.hardware.Camera;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.os.Process;
import android.util.Log;

import java.util.List;

/**
 * Custom {@link HandlerThread} that opens an instance of the {@link Camera} object in a dedicated
 * thread. Once an instance of the the {@link Camera} object has been loaded, a reference is sent
 * back to the main thread for usage.
 *
 * <p>
 *     This thread is used because loading the camera is an expensive operation that should not be
 *     done on the main UI thread. Additionally, any work performed on the camera data is performed
 *     by whatever thread called {@code Camera.open()}, so this allows the image processing to be
 *     contained in a dedicated thread. See
 *     <a href="https://developer.android.com/topic/performance/threads">this</a> article for more
 *     info, particularly the section on {@code HandlerThread}.
 * </p>
 *
 * @author Funkatronics (Marco Martinez)
 *
 * @see HandlerThread
 */
public class CameraHandlerThread extends HandlerThread {

	/** Tag used for Logging */
	private final static String TAG = CameraHandlerThread.class.getSimpleName();

	/** ID of the camera being used */
	private int mCameraId;

	/** Instance of {@link Camera} object that holds the camera being used */
	private Camera mCamera;

	/** {@link Handler} to this thread */
	private Handler mCameraThreadHandler;

	/** {@link Handler} to the the main thread */
	private Handler mMainThreadHandler;

	/** Public Constructor
	 *
	 * @param handler a {@link Handler} to the main thread
	 */
	CameraHandlerThread(Handler handler) {
		super("CameraHandlerThread", Process.THREAD_PRIORITY_DISPLAY);
		start();
		mCameraThreadHandler = new Handler(getLooper());
		mMainThreadHandler = handler;
	}

	/** Start the camera thread and load the camera */
	public void startCamera() {
		mCameraThreadHandler.post(() -> {
			getCameraInstance();
			notifyCameraOpened();
		});
	}

	/** Swap between front and back cameras */
	public void swapCamera() {
		try {
			mCamera.stopPreview();
			mCamera.release();
		} catch (Exception e) {
			// Ignore, tried to stop camera that does not exist
		}
		mCamera = null;

		// swap the id of the camera to be used
		mCameraId = mCameraId == Camera.CameraInfo.CAMERA_FACING_BACK ?
				Camera.CameraInfo.CAMERA_FACING_FRONT : Camera.CameraInfo.CAMERA_FACING_BACK;

		// (re)start the camera
		startCamera();
	}

	/** Get an instance of the {@link Camera} object and set up its parameters */
	private void getCameraInstance(){
		try {
			mCamera = Camera.open(mCameraId); // attempt to get a Camera instance

			Camera.Parameters parameters = mCamera.getParameters();

			// Set Preview size to smallest available
			List<Camera.Size> previewSizes = parameters.getSupportedPreviewSizes();
			Camera.Size minSize = previewSizes.get(0);
			for(Camera.Size size : previewSizes)
				if(size.width < minSize.width)
					minSize = size;
			parameters.setPreviewSize(minSize.width, minSize.height);

			// Set FPS range to max available
			List<int[]> fpsRanges = parameters.getSupportedPreviewFpsRange();
			int[] maxFpsRange = fpsRanges.get(0);
			for(int[] range : fpsRanges)
				if(range[0] > maxFpsRange[0])
					maxFpsRange = range;
			parameters.setPreviewFpsRange(maxFpsRange[0], maxFpsRange[1]);

			// Set parameters
			mCamera.setParameters(parameters);

			// If logging enabled, log preview size and FPS range
			if(MainActivity.LOG) {
				Log.i(TAG, "Size = " + minSize.width + "x" + minSize.height);
				Log.i(TAG, "FPS Range = " + maxFpsRange[0]/1000 + " to " + maxFpsRange[1]/1000);
			}

			// Set camera orientation (always 90 degrees for portrait)
			mCamera.setDisplayOrientation(90);
		} catch (Exception e){
			// Camera is not available (in use or does not exist)
			Log.i(TAG, "Camera not available! It is either already in use, or the " +
					"requested camera does not exist");
		}
	}

	/** Notify the main thread that the camera is ready to be used */
	synchronized void notifyCameraOpened() {
		Message msg = new Message();
		msg.what = MainActivity.MESSAGE_CAMERA_READY;
		msg.obj = mCamera;
		msg.arg1 = mCameraId;
		mMainThreadHandler.sendMessage(msg);
		notify();
	}
}
