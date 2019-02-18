## Using the Cthulhu Shield and Arduino Uno as a Tactile Button With Your Tongue

# Introduction:
This example shows how to use the Cthulhu Shield and tri-state function of the the arduino analog pins (A0-A5) to create a (somewhat intense) stimulus waveform on the tongue at 4 'button' locations, and to sense whether the tongue is in contact with each button. 

If the LED is active, the LED's representing an electrode should noticiably brighten when the tongue is in contact with the electrode. 

The long pulses used here were selected to maximize the change in brightness of the LED's during tongue contact. 

The example will output an analog reading for each of the six buttons to the serial terminal if desired.

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
Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **tactile_button_example** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_uno_tactile_button_example.JPG?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_brdselect_uno_button.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/tactile_button_port_select.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/tactile_button_upload.jpg?raw=true)

After uploading to the arduino, when you place the 18 Channel flexible electrode array on your tongue and press with your tongue on the top, bottom, left, or right, if the LED is active, an electrode should noticiably brighten with your tongue in contact with the electrode. This example will output an analog reading, so if you'd like to view this reading, press the "serial monitor" icon on the top right side of arduino screen and the serial monitor will display those readings. 

# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 
