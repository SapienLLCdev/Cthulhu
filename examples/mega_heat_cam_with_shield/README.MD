## Using the Cthulhu Shield, Arduino Mega, and the SparkFun GRID-Eye Infrared Array (Qwicc) to Sense Warm Objects With Your Tongue!

# Introduction

This example illustrates the use of the Cthulhu as a sensory substitution device paired with the Quicc GRID-Eye Infrared Array to sense the warmth of objects. When a warm object is sensed by the Infrared Array, the LEDs on the Cthulhu will light up, and the corresponding electrodes on the removable flexible array will be stimulated.

# Required Materials:

* Cthulhu Shield

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/cthulhusmall.jpg?raw=true)

* Arduino Mega or compatible clone

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/megasmall.jpg?raw=true)

* SparkFun Grid-EYE Infrared Array Breakout - AMG8833 (Qwiic)

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/infraredsmall.jpg?raw=true)

* USB A to B Cable

![USB A to B Cable](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/usbsmall.jpg?raw=true)

* One 18 Channel flexible electrode array from Sapien LLC

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/ribbonsmall.jpg?raw=true)

# Required Software
* This library (Directions on how to install below)
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [GridEYE Library](https://github.com/sparkfun/SparkFun_GridEYE_Arduino_Library).

If you do not know how to install an Arduino library, refer to the "How to Use this Repository" section [in the README](https://github.com/SapienLLCdev/Cthulhu). 

# Hardware Assembly:
Install Cthulhu Shield onto Arduino Uno or Arduino Mega and attach the USB cable and electrode array. 

# Quicc GRID-Eye Infrared Array setup with mega and Cthulhu Shield 

On Qwicc GRID-Eye Infrared Array  |    On Cthulhu Shield/Arduino MEGA
----------------------------------|----------------------------------
GND	            |                GND
3.3V	           |                3.3V
SDA	            |            Pin 20 (SDA)
SCL	            |            Pin 21 (SCL)


![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/infrared_setup.JPG?raw=true)

# Example:
Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **mega_heat_cam_with_shield** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_mega_heat_cam_with_shield_example.JPG?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_brdselect_mega.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_portselect_mega.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_heatcam_upload.jpg?raw=true)

If everything has been setup correctly, when you wave a warm object (such as your hand) over the SparkFun GRID-Eye Infrared Array sensor, the LEDs on the Cthulhu Shield will respond by lighting up. If you wave a cold object over the sensor, then no LEDs will light up. If the 18 Channel flexible electrode array from Sapien LLC has been connected to the Cthulhu Shield, the electrodes on the flexible array will be stimulated in response to warm objects. 


# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 



