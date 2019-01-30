package funkatronics.code.cthulhucamerademo;

import android.graphics.Bitmap;
import android.util.Log;

import java.util.Arrays;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

/**
 * This class processes frames from the camera to detect the amount of change between consecutive
 * frames. This can be used as a basic motion detector.
 *
 * <p>
 *     Optionally, an instance of the {@link CthulhuUsbInterface} class can be supplied to turn on
 *     LEDs on a connected Cthulhu device based on motion detected in different areas of the frame.
 * </p>
 *
 * @author Funkatronics (Marco Martinez)
 *
 * @see CthulhuUsbInterface
 */
public class FrameDifferenceProcessor {

	/** Class name tag used for logging */
	private static final String TAG = FrameDifferenceProcessor.class.getSimpleName();

	/** Static values for Thread Pool execution */
	private static final int NUMBER_OF_CORES = Runtime.getRuntime().availableProcessors();
	private static final int THREAD_POOL_SIZE = NUMBER_OF_CORES > 1 ? NUMBER_OF_CORES/2 : 1;
	private static final int TIMEOUT_VALUE = 60;
	private static final TimeUnit TIMEOUT_UNIT = TimeUnit.MILLISECONDS;

	/** Storage for the last frame for frame differencing */
	private byte[] mLastFrame;

	/** A 4x4 grid to store motion information from different areas of the frame */
	private int[][] mGridVals;

	/**
	 * Threshold value used to detect motion in the frame. If average of all pixel differences in
	 * a region exceeds this value, the corresponding LED on the Cthulhu device will be activated.
	 */
	private int mThreshold = 50;

	/** Width of each frame, in pixels */
	private int mWidth;

	/** Height of each frame, in pixels */
	private int mHeight;

	/** Is the frame data mirrored horizontally? (true if using front camera) */
	private boolean mMirror;

	/** Bitmap where the frame difference is stored */
	private Bitmap mFrameDiff;

	/** {@link CthulhuUsbInterface} object to send processed data to */
	private CthulhuUsbInterface mCthulhu;

	/**
	 * Public Constructor for {@code FrameDifferenceProcessor}
	 *
	 * @param width width of each frame, in pixels
	 * @param height height of each frame, in pixels
	 * @param mirror is the incoming frame data mirrored horizontally? (should be true if using the
	 *               front camera)
	 */
	public FrameDifferenceProcessor(int width, int height, boolean mirror) {
		mWidth = width;
		mHeight = height;
		mMirror = mirror;
		mLastFrame = new byte[width*height];
		// Swap width and height here because app is oriented 90 degrees relative to camera sensors
		// noinspection SuspiciousNameCombination
		mFrameDiff = Bitmap.createBitmap(height, width, Bitmap.Config.ARGB_8888);
	}

	/**
	 * Public Constructor for {@code FrameDifferenceProcessor}
	 *
	 * @param width width of each frame, in pixels
	 * @param height height of each frame, in pixels
	 * @param mirror should the frame difference result be flipped horizontally (to compensate for
	 *               the front camera mirror effect)?
	 * @param cthulhu an instance of {@link CthulhuUsbInterface} to send data to
	 */
	public FrameDifferenceProcessor(int width, int height, boolean mirror,
									CthulhuUsbInterface cthulhu) {
		this(width, height, mirror);
		mCthulhu = cthulhu;
	}

	/** Get the current threshold value */
	public int getThreshold() {
		return mThreshold;
	}

	/** Set the threshold value */
	public void setThreshold(int threshold) {
		mThreshold = threshold;
	}

	/**
	 * Begin processing the pixel data contained in {@param data} to compute the difference between
	 * each pixel in this frame and the previous.
	 *
	 * <p>
	 *     This method uses a Thread Pool Executor to compute this calculation on a pool of threads.
	 *     The number of threads spawned is half of the number of CPU cores on the device. This
	 *     significantly reduces the computation time on multi-core CPUs.
	 * </p>
	 *
	 * @param data the image data to compute, must be NV21 encoded
	 *
	 * @return a {@link Bitmap} containing the frame difference
	 */
	public Bitmap process(byte[] data) {
		// Spawn a Thread Pool to multi-thread this process
		ExecutorService executorService = Executors.newFixedThreadPool(THREAD_POOL_SIZE);

		// Reset grid values
		mGridVals = new int[4][4];

		// Pass tasks to executor
		final int length = mHeight/THREAD_POOL_SIZE;
		for(int i = THREAD_POOL_SIZE-1; i >= 0; i--) {
			final int offset = i*length;
			executorService.execute(() -> computeFrameDifference(data, offset, length));
		}

		// Tell threads to finish off.
		executorService.shutdown();

		// Wait for everything to finish.
		try {
			while(!executorService.awaitTermination(TIMEOUT_VALUE, TIMEOUT_UNIT)) {
				if(MainActivity.LOG) Log.i(TAG, "Awaiting completion of threads.");
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		// If a CthulhuUsbInterface has been supplied, send data to turn on LEDs in response to
		// motion
		if(mCthulhu != null) {
			String send = "";
			for(int j = 0; j < 4; j++) {
				for(int i = 0; i < 4; i++) {
					mGridVals[j][i] /= 176*144/16;
					if(mGridVals[j][i] > mThreshold)
						send += (char) CthulhuUsbInterface.CTHULHU_MAP[j][i];
				}
			}
			send += "\0";

			if(MainActivity.LOG) Log.d(TAG, "Sent: " + Arrays.toString(send.getBytes()));

			mCthulhu.write(send.getBytes());
		}

		// Update the stored last frame
		mLastFrame = data;

		return mFrameDiff;
	}

	/**
	 * Computes the difference between each pixel in 2 frames assuming NV21 pixel encoding.
	 *
	 * Only computes the rows of pixels between {@param offset} and {@param length}
	 *
	 * @param data the image data to compute, must be NV21 encoded
	 * @param offset the row offset where computation beings
	 * @param length the number of rows to process
	 */
	private void computeFrameDifference(byte[] data, int offset, int length) {
		for(int j = offset; j < offset + length; j++) {
			for(int i = 0; i < mWidth; i++) {
				// Compute the absolute value of the difference between each pixel
				// store the result as the Alpha (opacity) of a colored pixel
				int pixel = 0x00fff9c4 | (Math.abs(data[mWidth*j + i] - mLastFrame[mWidth*j + i]) << 24);
				// Set the pixel in the bitmap for display
				if(mMirror) {
					mFrameDiff.setPixel(mHeight - j - 1, i, pixel);
					mGridVals[3 - 4*i/mWidth][3 - 4*j/mHeight] += (pixel >> 24) & 0xFF;
				} else {
					mFrameDiff.setPixel(mHeight - j - 1, mWidth - i - 1, pixel);
					mGridVals[4*i/mWidth][3 - 4*j/mHeight] += (pixel >> 24) & 0xFF;
				}
			}
		}
	}

}
