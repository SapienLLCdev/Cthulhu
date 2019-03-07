## Using the Cthulhu Shield, Arduino Mega, and the SparkFun Force Sensitive Resistor to Feel Changes in Force with your Tongue!

# Introduction

This example illustrates the use of the Cthulhu as a sensory substitution device paired with the SparkFun Force Sensitive Resistor to feel changes in force intensity. The greater amount of force placed on the Force Sensitive Resistor, the more intense the stimulation experience will be.

# Required Materials:

* Cthulhu Shield

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/cthulhusmall.jpg?raw=true)

* Arduino Mega or compatible clone

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/megasmall.jpg?raw=true)

* SparkFun Force Sensitive Resistor 0.5"

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/force_sensitive_resistor.jpg?raw=true)

* 3.3kΩ Resistor

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/3_3kOhm.jpg?raw=true)

* Breadboard

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/breadboard.jpg?raw=true)

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

# Force Sensitive Resistor Setup with Mega and Cthulhu Shield 

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/force_sensitive_resistor_setup.JPG?raw=true)

For this example, a 3.3kΩ resistor was used. Refer to the SparkFun Force Sensitive Resistor hookup guide [here](https://learn.sparkfun.com/tutorials/force-sensitive-resistor-hookup-guide?_ga=2.62589669.834921711.1551994825-586526424.1528213955) if more reference is needed.

# Example:
Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **force_sensitive_resistor_example** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/force_sensitive_resistor_example.JPG?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/force_sensitive_resistor_brd_select.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/force_sensitive_resistor_port.jpg?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/force_sensitive_resistor_upload.jpg?raw=true)

If everything has been setup correctly, when the example is uploaded, no electrodes should be stimuluated initially. Once a force is applied to the Force Sensitive Resistor, by squeezing it with your fingers for example, the electrodes will be stimulated. The greater amount of force applied (the harder you squeeze) the greater intensity of the stimulus. Once the force applied is reduced, the intensity of the stimuluation will decrease. 
 
# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 



