package funkatronics.code.tactilewavescthulhudemo;

import android.Manifest;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v4.app.ActivityCompat;
import android.support.v4.app.FragmentActivity;
import android.support.v4.content.ContextCompat;
import android.support.v7.app.AlertDialog;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.WindowManager;
import android.widget.FrameLayout;

import funkatronics.code.tactilewaves.com.Bluetooth;
import funkatronics.code.tactilewaves.com.BluetoothEventListener;
import funkatronics.code.tactilewaves.com.android.BluetoothAndroid;
import funkatronics.code.tactilewaves.dsp.FormantExtractor;
import funkatronics.code.tactilewaves.dsp.PitchProcessor;
import funkatronics.code.tactilewaves.dsp.WaveManager;
import funkatronics.code.tactilewaves.io.WaveInputStream;
import funkatronics.code.tactilewaves.io.android.AndroidWaveInputStream;

import java.io.IOException;

import processing.android.PFragment;

/**
 * Main Activity of the app
 *
 * <p>
 *     Because this is a very simple app, this is the only activity.
 * </p>
 *
 * <p>
 *     This app relies on several libraries:
 *     <li>
 *         UsbSerial by felHR85, found <a href="https://github.com/felHR85/UsbSerial">here</a>
 *     </li>
 *     <li>
 *         Processing for Android, by the Processing Foundation, found
 *         <a href="https://github.com/processing/processing-android">here</a>
 *     </li>
 *     <li>
 *         TactileWaves by Funkatronics, found
 *         <a href="https://github.com/Funkatronics/TactileWaves">here</a>. NOTE: TactileWaves
 *         Version 1.1.0 or greater is required for this activity.
 *     </li>
 * </p>
 *
 * @author Funkatronics (Marco Martinez)
 */
public class MainActivity extends AppCompatActivity {

	/** Constants used as Permission Codes */
    private final int MY_PERMISSIONS_REQUEST_RECORD_AUDIO = 1;
    private final int MY_PERMISSIONS_REQUEST_WRITE_EXTERNAL_STORAGE = 2;
    private static String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";

	/**
	 * Instance of the TactileWaves {@link WaveManager} class. This object manages and processes an
	 * audio thread for us.
	 */
	private WaveManager mWaveManager;

	/**
	 * Instance of the TactileWaves {@link BluetoothAndroid} class. This object initiates and
	 * manages a bluetooth connection to a remote device.
	 */
	private BluetoothAndroid mBluetooth;

	/**
	 * An instance of the {@link CthulhuUsbInterface} class used to communicate with a Cthulhu
	 * device.
	 */
    private CthulhuUsbInterface mCthulhu;

	/**
	 * Instance of a custom Processing PApplet used to draw a data visualization animation to the
	 * screen. See https://android.processing.org/ for more info
	 */
	private PlotSketch mPlot;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        // setup the plotting sketch
        final FrameLayout frame = findViewById(R.id.plot_container);
        final FragmentActivity main = this;
        frame.post(() -> {
			mPlot = new PlotSketch(frame.getWidth(), frame.getHeight());
			//mPlot.background(R.color.bg);
			PFragment fragment = new PFragment(mPlot);
			fragment.setView(frame, main);
		});

        // setup the floating action button (Start/Stop button)
        final FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.start);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(mWaveManager.isRunning()) {
                    mWaveManager.stop();
                    fab.setImageDrawable(ContextCompat.getDrawable(view.getContext(), android.R.drawable.ic_media_play));
                    fab.setScaleX(1);
                    fab.setScaleY(1);
                } else if(!mWaveManager.isRunning()) {
                    mWaveManager.start();
                    fab.setImageDrawable(ContextCompat.getDrawable(view.getContext(), android.R.drawable.ic_media_pause));
                    fab.setScaleX(0.75f);
                    fab.setScaleY(0.75f);
                }
            }
        });

        // Initialize bluetooth and setup Bluetooth event listener
        mBluetooth = new BluetoothAndroid(new BluetoothEventListener() {

            int lastState;

            String received = "";

            @Override
            public void bluetoothNotAvailable(int state) {
                if(state == Bluetooth.STATE_NONE)
                    Snackbar.make(findViewById(R.id.main), "No Bluetooth", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                if(state == Bluetooth.STATE_OK)
                    Snackbar.make(findViewById(R.id.main), "Bluetooth is not enabled", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                else if(state == Bluetooth.STATE_CONNECTING)
                    Snackbar.make(findViewById(R.id.main), "Bluetooth is currently attempting a connection", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                else if(state == Bluetooth.STATE_CONNECTED)
                    Snackbar.make(findViewById(R.id.main), "Bluetooth is already connected", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
            }

            @Override
            public void bluetoothStateChanged(Bluetooth bluetooth, int state) {
                if(state == Bluetooth.STATE_CONNECTED) {
                    Snackbar.make(findViewById(R.id.main), "Bluetooth Connected", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                    invalidateOptionsMenu();
                } else if(state == Bluetooth.STATE_READY) {
                    if(lastState == Bluetooth.STATE_CONNECTING)
                        Snackbar.make(findViewById(R.id.main), "Connection Attempt Failed", Snackbar.LENGTH_LONG)
                                .setAction("Action", null).show();
                    else if(lastState == Bluetooth.STATE_CONNECTED)
                        Snackbar.make(findViewById(R.id.main), "Bluetooth Disconnected", Snackbar.LENGTH_LONG)
                                .setAction("Action", null).show();
                    else
                        Snackbar.make(findViewById(R.id.main), "Bluetooth Ready", Snackbar.LENGTH_LONG)
                                .setAction("Action", null).show();
                } else if(state == Bluetooth.STATE_CONNECTING) {
                    Snackbar.make(findViewById(R.id.main), "Attempting Connection...", Snackbar.LENGTH_LONG)
                            .setAction("Action", null).show();
                }
                lastState = state;
            }

            @Override
            public void bluetoothDataAvailable(Bluetooth bluetooth, byte[] data) {
                for(byte b : data) {
                    if(b == '\n') {
                        Snackbar.make(findViewById(R.id.main), received, Snackbar.LENGTH_LONG)
                                .setAction("Action", null).show();
                        received = "";
                        break;
                    }
                    received += (char)b;
                }
            }
        });

        // Initialize the CthulhuUsbInterface instance
		mCthulhu = new CthulhuUsbInterface(this);

        // Request microphone permissions
        requestMicPermission();
    }

    /** Request permission to record audio from the device hardware (required) */
    public void requestMicPermission(){
        // Do I have the permission?
        if (ContextCompat.checkSelfPermission(this,
                Manifest.permission.RECORD_AUDIO)
                != PackageManager.PERMISSION_GRANTED) {
            // I DO NOT have permission - need to request it
            // Should we show an explanation?
            if (ActivityCompat.shouldShowRequestPermissionRationale(this,
                    Manifest.permission.RECORD_AUDIO)) {

                // Show an explanation to the user *asynchronously* -- don't block
                // this thread waiting for the user's response! After the user
                // sees the explanation, try again to request the permission.
                AlertDialog.Builder builder = new AlertDialog.Builder(this);
                builder.setTitle("Audio Permissions are REQUIRED");
                builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.dismiss();

                        ActivityCompat.requestPermissions(MainActivity.this,
                                new String[]{Manifest.permission.RECORD_AUDIO},
                                MY_PERMISSIONS_REQUEST_RECORD_AUDIO);
                    }
                });
                builder.show();

            } else {
                // No explanation needed, we can just request the permission.
                ActivityCompat.requestPermissions(this,
                        new String[]{Manifest.permission.RECORD_AUDIO},
                        MY_PERMISSIONS_REQUEST_RECORD_AUDIO);
            }
        } else {
            // I DO have the permission, so I can go ahead and request it.
            ActivityCompat.requestPermissions(this,
                    new String[]{Manifest.permission.RECORD_AUDIO},
                    MY_PERMISSIONS_REQUEST_RECORD_AUDIO);
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] results) {
        if (mPlot != null) {
            mPlot.onRequestPermissionsResult(
                    requestCode, permissions, results);
        }
        switch (requestCode) {
            case MY_PERMISSIONS_REQUEST_RECORD_AUDIO: {
                // If request is cancelled, the result arrays are empty.
                if (results.length > 0
                        && results[0] == PackageManager.PERMISSION_GRANTED) {
                    // permission was granted, yay! Do the
                    // audio-related task you need to do.
                    WaveInputStream stream;
                    try {
                    	// Initialize audio input stream from default capture device (phone mic)
                        stream = new AndroidWaveInputStream(2048);
                        // Initialize WaveManager object to manage the audio stream
                        mWaveManager = new WaveManager(stream, 2048, 1024);
                        // Add pitch processor and formant extractor to audio processing chain
                        mWaveManager.addEffectToChain(new PitchProcessor());
                        mWaveManager.addEffectToChain(new FormantExtractor(5));
                        // Add custom listener that listens for processed audio data
						mWaveManager.addListener(new MainListener(mPlot, mBluetooth, mCthulhu));
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                } else {
                    // permission denied, boo! Disable the
                    // functionality that depends on this permission.
                }
                return;
            }case MY_PERMISSIONS_REQUEST_WRITE_EXTERNAL_STORAGE: {
                // If request is cancelled, the result arrays are empty.
                if (results.length > 0
                        && results[0] == PackageManager.PERMISSION_GRANTED) {
                    // permission was granted, yay! Do the
                    // write-external-storage-related task you need to do.

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
    public void onNewIntent(Intent intent) {
        if (mPlot != null) {
            mPlot.onNewIntent(intent);
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);

        if(mBluetooth.getState() == Bluetooth.STATE_CONNECTED)
            menu.findItem(R.id.action_connect).setTitle("Disconnect");
        if((getWindow().getAttributes().flags & WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON) != 0)
            menu.findItem(R.id.action_screen_on).setChecked(true);

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
				if(item.isChecked()) getWindow().clearFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				else getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
				item.setChecked(!item.isChecked());
				break;
			case R.id.action_connect:
				if(mBluetooth.getState() == Bluetooth.STATE_CONNECTED) {
					try {
						mBluetooth.terminateConnection();
						item.setTitle(R.string.connect_bt);
					} catch (IOException e) {
						e.printStackTrace();
					}
				} else {
					mBluetooth.chooseDeviceAndConnect(this);
					if(mBluetooth.getState() == Bluetooth.STATE_CONNECTED)
						item.setTitle(R.string.disconnect);
				}
				break;
			case R.id.action_connect_usb:
				mCthulhu.connectUsb();
				break;
		}

        return super.onOptionsItemSelected(item);
    }
}
