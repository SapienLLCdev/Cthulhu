package funkatronics.code.cthulhucamerademo;

import android.Manifest;
import android.app.Activity;
import android.content.DialogInterface;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.hardware.Camera;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.support.design.widget.FloatingActionButton;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Surface;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;

import java.util.List;

/**
 * Main Activity of the app
 *
 * Because this is a very simple app, this is the only activity
 *
 * @author Funkatronics (Marco Martinez)
 */
public class MainActivity extends AppCompatActivity {

	/** Tag used for Logging */
	private static final String TAG = MainActivity.class.getSimpleName();

	/** Static boolean that turns on app logging - set to true for debugging/performance logging */
	public static final boolean LOG = false;

	/** Constant used as Permission Code */
	private final int MY_PERMISSIONS_REQUEST_CAMERA = 1;

	/** Constant used to identify camera ready message */
	public static final int MESSAGE_CAMERA_READY = 100;

	/** An */
	private CameraPreview mPreview;

	/**
	 * An instance of the {@link CthulhuUsbInterface} class used to communicate with a Cthulhu
	 * device
	 */
	private CthulhuUsbInterface mCthulhu;

	/**
	 * An instance of the {@link FrameDifferenceProcessor} class used to compute and display the
	 * difference between consecutive frames from the camera
	 */
	private FrameDifferenceProcessor mProcessor;

	/**
	 * An instance of the {@link CameraHandlerThread} class that maintains a dedicated thread for
	 * camera usage and processing
	 */
	private CameraHandlerThread mCameraThread;

	/** A {@link Handler} object to communicate with the camera thread */
	private Handler mCameraHandler;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
		setSupportActionBar(toolbar);

		FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
		fab.setOnClickListener(view -> {
			if(mCameraThread != null) mCameraThread.swapCamera();
		});

		mCthulhu = new CthulhuUsbInterface(this);

		mCameraHandler = new Handler(msg -> {
			if(msg.what == MESSAGE_CAMERA_READY) {
				if(LOG) Log.d(TAG, "Camera ready, performing setup...");
				setupCamera((Camera) msg.obj, msg.arg1);
			}
			return true;
		});

		if (this.getPackageManager().hasSystemFeature(PackageManager.FEATURE_CAMERA))
			requestCameraPermission();
	}

	/**
	 * Request permission to use the Camera
	 */
	public void requestCameraPermission(){
		// Do we have the permission?
		if (ContextCompat.checkSelfPermission(this,
				Manifest.permission.CAMERA)
				!= PackageManager.PERMISSION_GRANTED) {
			// We DO NOT have permission - need to request it
			// Should we show an explanation?
			if (ActivityCompat.shouldShowRequestPermissionRationale(this,
					Manifest.permission.CAMERA)) {
				// Show an explanation to the user *asynchronously* -- don't block
				// this thread waiting for the user's response! After the user
				// sees the explanation, try again to request the permission.
				AlertDialog.Builder builder = new AlertDialog.Builder(this);
				builder.setTitle("Use of the Camera is REQUIRED");
				builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();

						ActivityCompat.requestPermissions(MainActivity.this,
								new String[]{Manifest.permission.CAMERA},
								MY_PERMISSIONS_REQUEST_CAMERA);
					}
				});
				builder.show();
			} else {
				// No explanation needed, we can just request the permission.
				ActivityCompat.requestPermissions(this,
						new String[]{Manifest.permission.CAMERA},
						MY_PERMISSIONS_REQUEST_CAMERA);
			}
		} else {
			// We DO have the permission, so we can go ahead and request it.
			ActivityCompat.requestPermissions(this,
					new String[]{Manifest.permission.CAMERA},
					MY_PERMISSIONS_REQUEST_CAMERA);
		}
	}

	@Override
	public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] results) {
		switch (requestCode) {
			case MY_PERMISSIONS_REQUEST_CAMERA: {
				// If request is cancelled, the result arrays are empty.
				if (results.length > 0 && results[0] == PackageManager.PERMISSION_GRANTED) {
					// permission was granted, yay! Do the
					// camera-related task you need to do.
					//getCameraInstance();
					//startCameraThread();
					//getCameraInstance();
					if(mCameraThread == null) mCameraThread = new CameraHandlerThread(mCameraHandler);
					synchronized(mCameraThread) {
						mCameraThread.startCamera();
					}
				} else {
					// permission denied, boo! Disable the
					// functionality that depends on this permission.
				}
			}
			// other 'case' lines to check for other
			// permissions this app might request
		}
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.menu_main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();

		switch(id) {
			case R.id.action_screen_on:
				// Toggle flag to keep screen on
				if(item.isChecked()) getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				else getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				item.setChecked(!item.isChecked());
				return true;
			case R.id.action_connect_usb:
				mCthulhu.connectUsb();
				return true;
			case R.id.action_set_threshold:
				// Get custom layout for slider dialog
				View customLayout = View.inflate(this, R.layout.slider_dialog, null);
				TextView sliderVal = customLayout.findViewById(R.id.slider_val);
				SeekBar slider = customLayout.findViewById(R.id.slider);
				// Set the slider to the current threshold value
				slider.setProgress(mProcessor.getThreshold());
				// Listen for user input on the slider and update the threshold value accordingly
				slider.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
					@Override
					public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
						int val = (progress * (seekBar.getWidth() - 2 * seekBar.getThumbOffset())) / seekBar.getMax();
						sliderVal.setText(getString(R.string.format_number, progress));
						sliderVal.setX(seekBar.getX() + val + seekBar.getThumbOffset() / 2);
					}
					@Override
					public void onStartTrackingTouch(SeekBar seekBar) {}
					@Override
					public void onStopTrackingTouch(SeekBar seekBar) {
						mProcessor.setThreshold(seekBar.getProgress());
					}
				});
				// Show an alert dialog with the slider
				final AlertDialog dialog = new AlertDialog.Builder(this, R.style.DialogTheme)
						.setTitle("Select Threshold Value:")
						.setPositiveButton("OK", null)
						.create();
				dialog.setView(customLayout);

//				if(dialog.getWindow() != null)
//					dialog.getWindow().setBackgroundDrawableResource(R.drawable.dialog_background);

				dialog.show();
				return true;
		}

		return super.onOptionsItemSelected(item);
	}

	/**
	 * Setup a provided instance of the {@link Camera} class and setup UI to display the
	 * {@link CameraPreview}
	 *
	 * @param cam a valid instance of the {@link Camera} class
	 * @param camId the ID of the camera being used
	 */
	private void setupCamera(Camera cam, int camId) {
		// Update floating action button's icon
		FloatingActionButton fab = findViewById(R.id.fab);
		fab.setImageResource(camId == Camera.CameraInfo.CAMERA_FACING_FRONT ?
				R.drawable.ic_camera_rear : R.drawable.ic_camera_front);

		Camera.Size previewSize = cam.getParameters().getPreviewSize();

		// Create ImageView for motion (frame difference) overlay
		ImageView motionOverlay = new ImageView(this);
		motionOverlay.setScaleType(ImageView.ScaleType.FIT_XY);

		// Initialize frame difference processor
		mProcessor = new FrameDifferenceProcessor(previewSize.width, previewSize.height,
				camId == Camera.CameraInfo.CAMERA_FACING_BACK, mCthulhu);

		// Create Camera Preview and draw it in Frame Layout
		mPreview = new CameraPreview(this, cam, motionOverlay, mProcessor, mCameraHandler);
		FrameLayout display = (FrameLayout) findViewById(R.id.camera_preview);
		display.removeAllViews();
		display.addView(mPreview);

		// Add motion overlay to FrameLayout
		display.addView(motionOverlay);

		// Add grid overlay to FrameLayout
		ImageView gridOverlay = new ImageView(this);
		gridOverlay.setScaleType(ImageView.ScaleType.FIT_XY);
		gridOverlay.setImageBitmap(generateGridOverlay());
		display.addView(gridOverlay);
	}

	/**
	 * Generate a square {@link Bitmap} with an evenly spaced 4x4 grid and no background that can
	 * be used to overlay a grid on our {@link CameraPreview}.
	 *
	 * @return the generated {@link Bitmap}
	 */
	private Bitmap generateGridOverlay() {
		int size = 403; // Make the Bitmap square for ease, we can rescale it later
		Bitmap grid = Bitmap.createBitmap(size, size, Bitmap.Config.ARGB_8888);
		int color = 0x7F000000; // black with 50% opacity
		for(int i = 0 ; i < size; i++) {
			// Draw vertical lines
			grid.setPixel(size/4 + 1, i, color);
			grid.setPixel(size/2 + 1, i, color);
			grid.setPixel(3*size/4 + 1, i, color);
			// Draw horizontal lines
			grid.setPixel(i, size/4 + 1, color);
			grid.setPixel(i, size/2 + 1, color);
			grid.setPixel(i, 3*size/4 + 1, color);
		}
		return grid;
	}

}
