## How to Use Sapien LLC's Cthulhu Shield to Electrotactiley Stimulate the Tongue

# Introduction
This example shows how to use Sapien LLC's Cthulhu Sheild to electrotactiley stimulate the tongue. In this example, one electrode is set active, and five stimulation parameters are set. The Cthulhu library is initialized, and serial output is enabled. 
  
The CheckWaveform function is used to verify that we have entered a valid waveform for all electrodes, if the paramters we entered are OK, then the stimulus waveform is updated (UpdateStimuli), and the pulsetrain is sent to the active electrodes (Stimulate) for one stimulation cycle (36ms). 

If the waveform is invalid, the error code is printed to the serial monitor and the stimulus is not updated or produced. 

This loops indefinitely.

# Required Materials:

* Cthulhu Shield

![Cthulhu_Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/cthulhusmall.jpg?raw=true)

* Arduino Uno or compatible clone

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/unosmall.jpg?raw=true)

* USB A to B Cable

![USB A to B Cable](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/usbsmall.jpg?raw=true)

* One 18 Channel flexible electrode array from Sapien LLC

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/ribbonsmall.jpg?raw=true)

# Required Software
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* This library (Directions on how to install below)

# Hardware Assembly:
Install Cthulhu Shield onto Arduino Uno or Arduino Mega and attach the USB cable and electrode array. 

# Example:
Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **BareMinimum** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/BareMinimum_example.JPG?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/BareMinimum_brdselect.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/BareMinimum_portselect.JPG?raw=true)

The Serial Input example is ready to be uploaded.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/BareMinimum_upload.JPG?raw=true)

After the example is uploaded, one electrode should be activated. 

# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 
