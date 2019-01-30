package funkatronics.code.cthulhucamerademo;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.ImageFormat;
import android.hardware.Camera;
import android.os.Handler;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.ImageView;

import java.io.IOException;

/**
 * A custom {@code CameraPreview} class that supplies a live feed of the camera, and sends each
 * preview frame to a {@link FrameDifferenceProcessor} to be processed.
 *
 * @author Funkatronics (Marco Martinez)
 *
 * @see Camera
 * @see SurfaceView
 * @see SurfaceHolder
 */
public class CameraPreview extends SurfaceView implements SurfaceHolder.Callback {

	/** Tag used for Logging */
	private static final String TAG = CameraPreview.class.getSimpleName();

	/** {@link SurfaceHolder} Interface for the Camera Preview */
	private SurfaceHolder mHolder;

	/** Copy of reference to the {@link Camera} object */
	private Camera mCamera;

	/** {@link ImageView} where the processed frames are drawn */
	private ImageView mOverlay;

	/** First frame buffer used in the {@link Camera.PreviewCallback} */
	private byte[] mFrame0;

	/** Second frame buffer used in the {@link Camera.PreviewCallback} */
	private byte[] mFrame1;

	/** Instance of {@link FrameDifferenceProcessor} where frames are sent to be processed */
	private FrameDifferenceProcessor mProcessor;

	/** {@link Handler} to main thread so we can post UI updates with mOverlay */
	private Handler mHandler;

	/** Public Constructor
	 *
	 * @param context the context of the calling activity
	 * @param camera the {@link Camera} object that is being previewed
	 * @param overlay the {@link ImageView} where the frame difference should be drawn
	 * @param processor a {@link FrameDifferenceProcessor} used to process the frames
	 * @param handler a {@link Handler} to the main thread to post UI updates
	 */
	public CameraPreview(Context context, Camera camera, ImageView overlay,
						 FrameDifferenceProcessor processor, Handler handler) {
		super(context);
		mCamera = camera;
		mOverlay = overlay;
		mProcessor = processor;
		mHandler = handler;

		// Install a SurfaceHolder.Callback so we get notified when the
		// underlying surface is created and destroyed.
		mHolder = getHolder();
		mHolder.addCallback(this);
		// deprecated setting, but required on Android versions prior to 3.0
		mHolder.setType(SurfaceHolder.SURFACE_TYPE_PUSH_BUFFERS);
	}

	// Interface Method
	public void surfaceCreated(SurfaceHolder holder) {
		// The Surface has been created, now tell the camera where to draw the preview.
		try {
			mCamera.setPreviewDisplay(holder);
			// Setup frame buffers
			int bitsPerPixel = ImageFormat.getBitsPerPixel(mCamera.getParameters().getPreviewFormat());
			Camera.Size size = mCamera.getParameters().getPreviewSize();
			mFrame0 = new byte[bitsPerPixel*size.width*size.height/8];
			mFrame1 = new byte[bitsPerPixel*size.width*size.height/8];
			// Add callback and first callback buffer
			mCamera.setPreviewCallbackWithBuffer(new PreviewFrameCallback());
			mCamera.addCallbackBuffer(mFrame0);
			// Start the preview
			mCamera.startPreview();
		} catch (IOException e) {
			Log.d(TAG, "Error setting camera preview: " + e.getMessage());
		}
	}

	// Interface Method
	public void surfaceDestroyed(SurfaceHolder holder) {
		// empty. Take care of releasing the Camera preview in your activity.
	}

	// Interface Method
	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
		// If your preview can change or rotate, take care of those events here.
		// Make sure to stop the preview before resizing or reformatting it.

		if (mHolder.getSurface() == null){
			// preview surface does not exist
			return;
		}

		// stop preview before making changes
		try {
			mCamera.stopPreview();
		} catch (Exception e){
			// ignore: tried to stop a non-existent preview
		}

		// set preview size and make any resize, rotate or
		// reformatting changes here

		// start preview with new settings
		try {
			mCamera.setPreviewDisplay(mHolder);
			mCamera.setPreviewCallbackWithBuffer(new PreviewFrameCallback());
			mCamera.addCallbackBuffer(mFrame0);
			mCamera.startPreview();

		} catch (Exception e){
			Log.d(TAG, "Error starting camera preview: " + e.getMessage());
		}
	}

	/**
	 * Custom {@link Camera.PreviewCallback} that sends each preview frame to a
	 * {@link FrameDifferenceProcessor} to be processed and draws the processed frame in the
	 * {@link ImageView} stored in mOverlay. Also logs average FPS if the {@code MainActivty.LOG}
	 * constant is set to true.
	 */
	class PreviewFrameCallback implements Camera.PreviewCallback {
		private int whichBuff = 0;
		private long avgCount = 0;
		private float avgFps = 0;

		@Override
		public void onPreviewFrame(byte[] data, Camera camera) {
			// Save start time for FPS calculation
			long startTime;
			if(MainActivity.LOG) startTime = System.currentTimeMillis();

			// Swap between the 2 frame buffers for increased performance and efficiency
			// This helps because it allows the camera to prepare the next frame while we are
			// processing the current frame, and also reuses memory so we are not wasting time on
			// memory allocation on every new frame.

			if(whichBuff == 0) {
				whichBuff = 1;
				camera.addCallbackBuffer(mFrame1);
				Bitmap result = mProcessor.process(mFrame0);
				mHandler.post(() -> mOverlay.setImageBitmap(result));
			} else {
				whichBuff = 0;
				camera.addCallbackBuffer(mFrame0);
				Bitmap result = mProcessor.process(mFrame1);
				mHandler.post(() -> mOverlay.setImageBitmap(result));
			}

			// If Logging is enabled, log average FPS
			if(MainActivity.LOG) {
				long endTime = System.currentTimeMillis();
				float fps = 1000f/(endTime - startTime);
				avgFps = (avgFps*avgCount) + fps;
				avgCount++;
				avgFps /= avgCount;
				Log.i(TAG, "Average FPS = " + avgFps);
			}
		}
	}
}