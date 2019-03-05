package funkatronics.code.tactilewavescthulhudemo;

import funkatronics.code.tactilewaves.com.Bluetooth;
import funkatronics.code.tactilewaves.dsp.WaveFrame;
import funkatronics.code.tactilewaves.dsp.WaveFrameListener;

import java.io.IOException;

/**
 * MainListener implements the {@link WaveFrameListener} interface from the TactileWaves library.
 *
 * <p>
 *     This object listens for newly processed audio frames from the {@code WaveManager} object in
 *     the main activity. Upon receiving a processed audio frame, the extracted features (pitch and
 *     formants, in this case) are sent over bluetooth/USB, and the data visualization plot is
 *     updated.
 * </p>
 *
 * @author Funkatronics (Marco Martinez)
 */
public class MainListener implements WaveFrameListener {

	private PlotSketch mPlot;

	private Bluetooth mBluetooth;

	private CthulhuUsbInterface mCthulhu;

	/** Initialize the listener with references to Plot, Bluetooth and USB objects */
	MainListener(PlotSketch plot, Bluetooth bluetooth, CthulhuUsbInterface cthulhu) {
		mPlot = plot;
		mBluetooth = bluetooth;
		mCthulhu = cthulhu;
	}

	/** Called by the WaveManager whenever a frame of audio has been processed */
    public void newFrameAvailable(WaveFrame frame) {
    	// Get the features from the frame
        Object feat = frame.getFeature("Pitch");
        float pitch = -1;
        if (feat instanceof Float)
			pitch = (float) frame.getFeature("Pitch");

        feat = frame.getFeature("Formants");
        float[] formants = new float[3];
        if (feat instanceof float[]) {
			if (((float[]) feat).length > 3) formants = new float[((float[]) feat).length];
			System.arraycopy(feat, 0, formants, 0, ((float[]) feat).length);
		}

        ///////////////////////////////////////////////////////////////////////////////////////////
		// Cthulhu Tactile Formant Communication
		///////////////////////////////////////////////////////////////////////////////////////////
		// Convert Formants (Hz) to Cthulhu electrode groups
		int lastBand = 1;
		int[] formantInts = new int[formants.length];
		float bandLimits[] = {177.0f, 355.0f, 710.0f, 1420.0f, 2840.0f, 5680.0f, 11360.0f};
		byte[][] elecMapB = {{1,2}, {3,4,5,6}, {7,8,9,10}, {11,12,13,14}, {16,17}, {15,18}};
		for(int i = 0; i < formantInts.length; i++){
			float current = formants[i];
			for(int b = lastBand; b < bandLimits.length; b++) {
				if(current < bandLimits[b]) {
					formantInts[i] = b;
					lastBand = b;
					break;
				}
			}
			if(current < bandLimits[0] || current > bandLimits[bandLimits.length-1]) formantInts[i] = 0;
		}

		// Pack electrode numbers into string
		StringBuilder formantString = new StringBuilder();
		for(int j = 0; j < 3; j++){
			if(formantInts[j] == 0) break;
			formantString.append(new String(elecMapB[(int) formantInts[j] - 1]));
		}
		formantString.append("\0");

		// Send string to devices connected via USB and/or Bluetooth
		// If Bluetooth or USB is not connected, they simply wont send data
		try {
			mBluetooth.send(formantString.toString());
			mCthulhu.send(formantString.toString());
		} catch (IOException e) {
			e.printStackTrace();
		}

		// Send features to the plot for visualization
		mPlot.addPitchEntry(pitch);
		mPlot.addFormantEntry(formants);
    }
}
