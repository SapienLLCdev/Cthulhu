## Using the Cthulhu Shield, Arduino Mega, and the SparkFun Triple Axis Accelerometer to Feel Movement With Your Tongue!

# Introduction

This example illustrates the use of the Cthulhu Shield as a sensory substitution device paired with the SparkFun Triple Axis Accelerometer to feel movement on the positive and negative X and Y axes. When the accelerometer is moved in the positive or negative direction of the axes, the corresponding electrodes on the removable flexible array will be stimulated.

# Required Materials:

* Cthulhu Shield

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/cthulhusmall.jpg?raw=true)

* Arduino Mega or compatible clone

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/megasmall.jpg?raw=true)

* SparkFun Triple Axis Accelerometer Breakout - ADXL362

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/accelerometer.jpg?raw=true)

* USB A to B Cable

![USB A to B Cable](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/usbsmall.jpg?raw=true)

* One 18 Channel flexible electrode array from Sapien LLC

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/ribbonsmall.jpg?raw=true)

# Required Software
* This library (Directions on how to install below)
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [ADXL362](https://github.com/annem/ADXL362)

If you do not know how to install an Arduino library, refer to the "How to Use this Repository" section [in the README](https://github.com/SapienLLCdev/Cthulhu). 

# Hardware Assembly:
Install Cthulhu Shield onto Arduino Uno or Arduino Mega and attach the USB cable and electrode array. 

# Triple Axis Accelerometer setup with mega and Cthulhu Shield 

On Triple Axis Acceleromter  |    On Cthulhu Shield/Arduino MEGA
-----------------------------|----------------------------------
GND	            			 |              GND
V+	           				 |             3.3V
SCK	           				 |            Pin 52
MOSI	      				 |            Pin 51
MISO						 |			Pin 50
CS              			 |				Pin 53


* Labeled Pins on Triple Axis Accelerometer

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/accelerometer_labeled.JPG?raw=true)

* Full Setup

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/accelerometer_setup.JPG?raw=true)

# Example:
Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **accelerometer_Cthulhu_example** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/accelerometer_Cthulhu_example.JPG?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/accelerometer_brd_select.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/accelerometer_port_select.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/accelerometer_upload.JPG?raw=true)

If everything has been setup correctly, when the example is uploaded, if the accelerometer is tilted up towards the user (+X), down away from the user (-X), down to the right (+Y), and down toward the left (-Y), the corresponding elecrodes will be stimulated. This allows for the user to feel the movement in the different directions with their tongue. The further in the direction the accelerometer is tilted, the more intense feeling the stimulation will be. 

Tilted Axis  |  Stimulated Electrodes
-----------------------------|----------------------------------
+X	            			 |                3, 4
-X	           				 |               15, 16
+Y	           				 |              9, 13
-Y	      				 |              6, 10

* Electrode Numbers on the Cthulhu Shield
<pre>
	{   0, 1   },
	{2, 3, 4, 5},
	{6, 7, 8, 9},
	{10,11,12,13},
	{14,15,16,17}
</pre>
			
	



# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 



