package funkatronics.code.tactilewavescthulhudemo;

import java.util.ArrayList;
import java.util.List;

import processing.core.PApplet;
import processing.core.PFont;

/**
 * PlotSketch is a custom animation class for visualizing audio data using
 * <a href"https://android.processing.org/">Processing for Android</a>.
 *
 * <p>
 *     This class draws a realtime plot of audio features that have been processed by the Tactile
 *     Waves audio engine. A time history of the incoming audio's formant frequencies and pitch is
 *     drawn horizontally with frequency drawn logarithmically on the vertical axis from 20Hz to
 *     20kHz.
 * </p>
 *
 * <p>
 *     Because the Tactile Waves audio thread runs asynchronously to the UI thread, a data "cache"
 *     is used to update the data in the plot. New audio data is placed in the cache using the
 *     {@code addPitchEntry} and {@code addFormantEntry} methods. When the animation redraws, the
 *     newest data is drawn and the oldest is discarded. This allows to plot to draw at its own
 *     speed, without waiting for new data to arrive.
 * </p>
 *
 * @author Funkatronics (Marco Martinez)
 */
public class PlotSketch extends PApplet {

	// Number of data points drawn on the screen at once
	private float mMaxData = 180;
	// number of cached data points
	private float mCache = 2;

	// Min and max frequency of the plot
	private float mMaxY = 20000.0f;
	private float mMinY = 20.0f;

	PFont font;

	// Data storage
	private List<Float> pitchData;
	private List<float[]> formantData;

	// Initialize the sketch
	PlotSketch(int width, int height) {
		this.width = width;
		this.height = height;
		pitchData = new ArrayList<>((int)(mMaxData + mCache));
		formantData = new ArrayList<>((int)(mMaxData + mCache));
	}

	// Apply settings
	public void settings() {
		size(width, height, P2D);
	}

	// Setup color, font, etc.
	public void setup() {
		background(color(37, 37, 37));
		frameRate(30);
		smooth(4);
		stroke(128);
		strokeWeight(1);
		font = createFont("Monospaced-Bold",48);
		textFont(font,32);
	}

	// Draw to the screen (method repeats at (hopefully) 30Hz)
	public void draw() {
		// clear the screen
		background(color(27, 27, 27));
		// draw a log scale grid for the y axis
		drawYGrid();
		// draw data in the data lists onto the plot
		drawFormants(formantData,24);
		drawPitch(pitchData, 20);
		// draw legend
		drawLegend();
		// draw frame rate in bottom left corner
		textSize(20);
		text(("FPS:" + (int)frameRate), 5, height - 10);
	}

	// Draw Helper methods
	private void drawYGrid() {
		for(int i = getPow10(mMinY); i <= getPow10(mMaxY); i += Math.pow(10, order(i))) {
			line(0, val2Yloc(i), width, val2Yloc(i));
		}
		textSize(32);
		fill(255, 250, 226);
		text("100", 5, val2Yloc(100) - 4);
		text("1k", 5, val2Yloc(1000) - 4);
		text("10k", 5, val2Yloc(10000) - 4);
	}

	private void drawLegend() {
		fill(120, 206, 16);
		ellipse(120, height - 20, 20, 20);

		fill(206, 178, 18);
		ellipse(280, height - 20, 24, 24);

		fill(244, 134, 66);
		ellipse(360, height - 20, 18, 18);

		fill(206, 65, 17);
		ellipse(440, height - 20, 12, 12);

		fill(255, 250, 226);
		text("Pitch", 135, height - 8);
		text("F1", 295, height - 8);
		text("F2", 370, height - 8);
		text("F3", 450, height - 8);
	}

	private void drawFormants(List data, int r) {
		int[] colors = {color(206, 178, 18),
						color(244, 134, 66),
						color(206, 65, 17)};
		int max = (int)min(data.size(), mMaxData);
		ellipseMode(CENTER);
		for(int i = 1; i < max; i++) {
			float[] formants = (float[]) data.get(i);
			for(int f = 0; f < min(formants.length, 3); f++) {
				fill(colors[f]);
				if(formants[f] >= mMinY && formants[f] <= mMaxY)
					ellipse(val2Xloc(i, max), val2Yloc(formants[f]), r, r);
			}
		}
	}

	private void drawPitch(List data, int r) {
		fill(color(120, 206, 16));
		int max = (int)min(data.size(), mMaxData);
		ellipseMode(CENTER);
		for(int i = 1; i < max; i++) {
			if((float)data.get(i) >= mMinY && (float)data.get(i) <= mMaxY)
				ellipse(val2Xloc(i, max), val2Yloc((float) data.get(i)), r, r);
		}
	}

	// Arithmetic helper methods
	private int order(int val) {
		int mag = 0;
		int num = abs(val);
		while(num > 0) {
			mag++;
			num /= 10;
		}
		return mag-1;
	}

	private int getPow10(float val) {
		int pow10 = (int)Math.pow(10, order((int)val));
		return ((int)val/pow10)*pow10;
	}

	// Methods to convert data point to pixel location
	private int val2Yloc(int val) {
		double min = Math.log10(mMinY);
		double max = Math.log10(mMaxY);
		return height - (int)(height*(Math.log10(val) - min)/(max - min));
	}

	private int val2Yloc(float val) {
		double min = Math.log10(mMinY);
		double max = Math.log10(mMaxY);
		return height - (int)(height*(Math.log10(val) - min)/(max - min));
	}

	private int val2Xloc(int val, int max) {
		return 10 + (int)((width-20)*((double)val/max));
	}

	/** Add a new pitch data point to the data cache */
	void addPitchEntry(float pitch) {
		pitchData.add(pitch);
		if(pitchData.size() > mMaxData + mCache)
			pitchData.remove(0);
	}

	/** Add a new formant data point to the cache */
	void addFormantEntry(float[] formants) {
		formantData.add(formants);
		if(formantData.size() > mMaxData + mCache)
			formantData.remove(0);
	}
}
