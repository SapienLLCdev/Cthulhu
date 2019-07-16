## Using the Cthulhu Shield and Arduino Leonardo as a Full-Function Computer Mouse!

# Introduction:

The Cthulhu Shield and electrode array can be used to sense whether or not your tongue is in contact with certain electrodes. Combined with the electrotactile ability of the Cthulhu Shield, this can be used to create 'virtual' tactile buttons that can be pressed with the tongue. With with the HID library function of the arduino Leonardo, you can use the Cthulhu to control your computer cursor or type with your tongue!

This example will show you how to upload the example 'Leonardo_tactile_cursor.ino' sketch to an Arduino Leonardo with mounted Cthulhu Shield to use your tongue to mouse movements to your computer. You can also use the onscreen keyboard to type and send emails with your tongue! 

This example is considerably easier to use than the 'tactile_cursor' example. But requires an Arduino Leonardo.

[An video of the device being used can be found here](https://youtu.be/Bt2chGSGTl8)


[Instructions on how to control the cursor can be found here](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/Leonardo_tactile_cursor/Tongue%20mouse%20instructions.pdf)

![Game_Control](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/bw_tongue_mouse.gif?raw=true)

# Required Materials:

* Cthulhu Shield

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/cthulhusmall.jpg?raw=true)
* Arduino Leonardo or compatible clone with Atmega32U4 microcontroller.

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/Leonardo.jpg?raw=true)
* USB A to B Cable

![USB A to micro B cable](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/microusbcablesmall.jpg?raw=true)

* One 18 Channel flexible electrode array from Sapien LLC

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/ribbonsmall.jpg?raw=true)

# Required Software:
* This library
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)


# Hardware Assembly:
Install Cthulhu Shield onto Arduino Leonardo and attach the USB cable and electrode array. 

# PC Setup:
For setup on Windows, follow the instructions below. If you have a Mac, please see the section entitled [Mac Setup](#mac-setup) further down the page. 

Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **Leonardo_tactile_cursor** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_leonardo_tactile_cursor%20_example.JPG?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Leonardo.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_brdselect_leonardo.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_leonardo_comselect.JPG?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_leonardo_upload.JPG?raw=true)



If you havent already, carefully lift the latch of the ZIF connector, insert the electrode array gold side down, and close the latch. 

* Use the tip of your tongue to press the tactile 'buttons' on the electrodes at the front, back , and both sides of the array. The LED's on the Cthulhu Shield will (very slightly) change brightness when your tongue is contacting them.
* To click, flatten your tongue against the array (and the roof of your mouth) with a slapping motion to contact all the electrodes, then pull your tongue off the array. Double clicking works similarly. Clicking will activate all LED's on the array at once to give you tactile and visual feedback.
* To right-click, flatten your tongue against all electrodes as described above, and hold your tongue against all electrodes for about 2 seconds, then release. The appropriate right-click menu should pop up when released. 
* To click-drag/click-and-hold (moving a window, or using a scrollbar, etc), Flatten your tongue against all electrodes to click, and hold your tongue against the array while sliding your tongue to the desired directional button.

You can enable the oncsreen keyboard in the windows control panel if you want to try typing with your tongue! 

![key1](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/without_mouse_keyboard_select.jpg?raw=true)

![key2](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/onscreenkeyboard.jpg?raw=true)



# Going Further:



# Acknowledgments: 



# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 
