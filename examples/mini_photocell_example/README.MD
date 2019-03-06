## Using the Cthulhu Shield, Arduino Mega, and the SparkFun Mini Photocell to Feel Light with your Tongue!

# Introduction

This example illustrates the use of the Cthulhu as a sensory substitution device paired with the SparkFun Mini Photocell to feel changes in light intesnsity. The more intense the light on the Mini Photocell, the more intense the stimulation experience will be.

# Required Materials:

* Cthulhu Shield

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/cthulhusmall.jpg?raw=true)

* Arduino Mega or compatible clone

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/megasmall.jpg?raw=true)

* SparkFun Mini Photocell

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/mini_photocell.jpg?raw=true)

* Breadboard

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/breadboard.jpg?raw=true)

* 1kΩ Resistor
![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/1KOhm.jpg?raw=true)

* USB A to B Cable

![USB A to B Cable](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/usbsmall.jpg?raw=true)

* One 18 Channel flexible electrode array from Sapien LLC

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/ribbonsmall.jpg?raw=true)

# Required Software
* This library (Directions on how to install below)
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)

If you do not know how to install an Arduino library, refer to the "How to Use this Repository" section [in the README](https://github.com/SapienLLCdev/Cthulhu). 

# Hardware Assembly:
Install Cthulhu Shield onto Arduino Uno or Arduino Mega and attach the USB cable and electrode array. 

# Mini Photocell setup with Mega and Cthulhu Shield 

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/mini_photocell_setup.JPG?raw=true)

For this example, a 1kΩ resistor was used. Refer to the SparkFun Mini Photocell setup guide [here](https://learn.sparkfun.com/tutorials/photocell-hookup-guide/all) if more reference is needed.

# Example:
Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **mini_photocell_example** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/mini_photocell_example.JPG?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/mini_photocell_brd_select.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/mini_photocell_port.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/mini_photocell_upload.JPG?raw=true)

If everything has been setup correctly, when the example is uploaded, the electrodes should be stimulated in an "x" pattern. If the light intensity is increased on the photocell by shining a flashlight on it, for example, the intensity of the stimulus will increase. If the light intesnity is decreased by turning off the lights or putting a solid object over the photocell, for example, the intensity of the stimulus will decrease.

For this example a 1kΩ resistor was used, but a 1kΩ up to a 10kΩ resistor can be used with the photocell. Just know that changing the resistance will change the amount of voltage experienced by the photocell.
 
# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 



