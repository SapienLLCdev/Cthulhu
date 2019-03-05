package funkatronics.code.tactilewavescthulhudemo;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbDeviceConnection;
import android.hardware.usb.UsbManager;
import android.widget.Toast;

import com.felhr.usbserial.UsbSerialDevice;
import com.felhr.usbserial.UsbSerialInterface;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

/**
 * This class manages communication between the app and a Cthulhu device connected via USB.
 *
 * <p>
 *     In order to provide Serial communication over USB, the UsbSerial library by felHR85 is used.
 *     The library can be found on GitHub <a href="https://github.com/felHR85/UsbSerial">here</a>.
 * </p>
 *
 * @author Funkatronics (Marco Martinez)
 *
 * @see UsbSerialDevice
 * @see UsbSerialInterface
 */
public class CthulhuUsbInterface {

	/** Static String with USB permission string */
	private static String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";

	/**
	 * This array represents a mapping to the electrodes on the Cthulhu Developer Shield.
	 *
	 * <p>
	 *     The LEDs on the Cthulhu are arranged as follows:
	 * </p>
	 *
	 * <table>
	 *     <tr>
	 *       <td>  X  1  2  X </td>
	 *     </tr>
	 *     <tr>
	 *       <td>  3  4  5  6 </td>
	 *     </tr>
	 *     <tr>
	 *       <td>  7  8  9 10 </td>
	 *     </tr>
	 *     <tr>
	 *       <td> 11 12 13 14 </td>
	 *     </tr>
	 *     <tr>
	 *       <td> 15 16 17 18 </td>
	 *     </tr>
	 * </table>
	 *
	 * <p>
	 *     For this example, we do not use the first 2 electrodes.
	 * </p>
	 */
	public static final byte[][] CTHULHU_MAP = {
			{ 3,  4,  5,  6},
			{ 7,  8,  9, 10},
			{11, 12, 13, 14},
			{15, 16, 17, 18}};

	/** Reference to Context of the calling activity */
	private Context mContext;

	/** Instance of Android's {@link UsbManager} class */
	private UsbManager mUsbManager;

	/** Instance of the {@link UsbSerialDevice} class that represents a connected USB device */
	private UsbSerialDevice mSerial;

	/**
	 * Constructs a {@code CthulhuUsbInterface} instance
	 *
	 * @param context the {@link Context} of the calling activity
	 */
	public CthulhuUsbInterface(Context context) {
		mContext = context;
	}

	/** Requests a connection to a USB device, if available */
	public void connectUsb() {
		mUsbManager = (UsbManager) mContext.getSystemService(Context.USB_SERVICE);
		if(mUsbManager != null) {
			// check if there's a connected usb device
			if(mUsbManager.getDeviceList().isEmpty()) {
				Toast.makeText(mContext, "No USB device connected!", Toast.LENGTH_LONG).show();
				return;
			}

			// get the first (only) connected device
			UsbDevice usbDevice = mUsbManager.getDeviceList().values().iterator().next();

			UsbReciever usbReciever = new UsbReciever();
			PendingIntent mPermissionIntent = PendingIntent.getBroadcast(
					mContext, 0, new Intent(ACTION_USB_PERMISSION), 0);
			IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
			mContext.registerReceiver(usbReciever, filter);

			mUsbManager.requestPermission(usbDevice, mPermissionIntent);
		}
	}

	/**
	 * Send a string of char's over USB (UTF-8 Encoding)
	 *
	 * @param send - String to send over USB
	 *
	 * @throws UnsupportedEncodingException if the bytes could not be encoded
	 */
	public void send(String send) throws UnsupportedEncodingException {
		write(send.getBytes("UTF-8"));
	}

	/**
	 * Write an array of bytes to the connected USB device
	 *
	 * @param buffer the array of bytes to be written
	 */
	public void write(byte[] buffer) {
		if(mSerial != null) {
			mSerial.write(buffer);
		}
	}

	/**
	 * This Callback is called whenever data is received over the USB serial connection. If the
	 * Cthulhu sends any data back to the app, it will be received here as an array of bytes
	 * called: {@code bytes}.
	 */
	private UsbSerialInterface.UsbReadCallback serialReadCallback = bytes -> {
		// Do something with received bytes (this example does nothing)
		// Example: sendBytesSomewhere(bytes);
	};

	/**
	 * This class extends the {@link BroadcastReceiver} class to receive a USB permission intent.
	 * If the user has granted permission to perform USB stuff, it will attempt to establish a
	 * serial connection to the connected USB device.
	 */
	class UsbReciever extends BroadcastReceiver {
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();
			if (ACTION_USB_PERMISSION.equals(action)) {
				UsbDevice usbDevice = (UsbDevice) intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);

				if (intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
					if(usbDevice != null) {
						// call method to set up device communication
						try {
							UsbDeviceConnection usbConnection = mUsbManager.openDevice(usbDevice);
							mSerial = UsbSerialDevice.createUsbSerialDevice(usbDevice, usbConnection);
							if(mSerial.open()) {
								mSerial.setBaudRate(9600);
								mSerial.setDataBits(UsbSerialInterface.DATA_BITS_8);
								mSerial.setStopBits(UsbSerialInterface.STOP_BITS_1);
								mSerial.setParity(UsbSerialInterface.PARITY_NONE);
								mSerial.setFlowControl(UsbSerialInterface.FLOW_CONTROL_OFF);

								// Set serial read callback
								mSerial.read(serialReadCallback);

								//mPreview.setSerialDevice(mSerial);
							} else {
								Toast.makeText(context, "Serial Port could not be opened", Toast.LENGTH_LONG).show();
							}
						} catch(Exception e) {
							Toast.makeText(context, e.getMessage(), Toast.LENGTH_LONG).show();
						}
					}
				}
			}
		}
	}
}
