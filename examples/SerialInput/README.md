## Activing Electrodes on the Cthulhu Shield Electrode Array Using Serial Input

# Introduction
This example shows how to activate electrodes on the Cthulhu Shield electrode array using serial input (from USB port, or an external device like a bluetooth module or another arduino).

Stimulation parameters are pre-set, and the serial input simply turns different electrodes on or off.

This eample works with the CthulhuCameraMotionDemo android app available on the android store: 
(https://play.google.com/store/apps/details?id=funkatronics.code.cthulhucamerademo) and the Cthulhu Tactile waves demo app soon to be available.

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
* [Coolterm-optional](http://freeware.the-meiers.org/)

# Hardware Assembly:
Install Cthulhu Shield onto Arduino Uno or Arduino Mega and attach the USB cable and electrode array. 

# Example:
Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **SerialInput** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_uno_SerialInput_example.JPG?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_brdselect_uno_SerialInput.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/SerialInput_port_select.JPG?raw=true)

The Serial Input example is ready to be uploaded.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/SerialInput_upload.JPG?raw=true)

Next, the app CoolTerm.exe can be used to activate individual electrodes on the Cthulhu. After opening CoolTerm, connect to the serial port.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/coolterm_port_connect.JPG?raw=true)

Open the **Send String** window by going to **connection**>**Send String**. The Send String window will now be displayed.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/coolterm_sendstring.JPG?raw=true)

In the Send String window, select **Hex**.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/coolterm_hex_select.JPG?raw=true)

You can now manually input with hexadecimal numbers which electrodes you'd like to active. There are electrodes 1-18.

Hexadecimal and Decimal Numbers
--------------------------------
    01 = 1     |      0a = 10
	02 = 2     |      0b = 11                
    03 = 3     |      0c = 12
    03 = 3     |      0d = 13
    04 = 4     |      0e = 14
    05 = 5     |      0f = 15
    06 = 6     |      10 = 16
    07 = 7     |      11 = 17
    08 = 8     |      12 = 18
    09 = 9

For example: If you type 01 02 03 0a 12 00 and press **Send**, it will turn on electrodes 0, 1, 2, 9, and 17 in the array. 
Always include 00 at the end of the string.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/coolterm_sendstring_hex.JPG?raw=true)

To deactive all electrodes type **00 00** and press send.

# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 
