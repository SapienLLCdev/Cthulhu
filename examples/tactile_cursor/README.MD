## Using the Cthulhu Shield and Arduino Uno to Send Keystrokes With Your Tongue!

# Introduction:

The Cthulhu Shield and electrode array can be used to sense whether or not your tongue is in contact with certain electrodes. Combined with the electrotactile ability of the Cthulhu Shield, this can be used to create 'virtual' tactile buttons that can be pressed with the tongue. With some minor software hacking of the Arduino, and use of microsofts accessibility tools, you can use the Cthulhu to control your computer cursor with your tongue (and type with your tongue!).

This example will show you how to upload the example 'tactile_cursor.ino' sketch to an Arduino Uno with mounted Cthulhu Shield (and then hack the Arduino) to  use your tongue to send '8''4''2''6' and '5' keystrokes to your computer. These keys can be used to control your computer cursor if some of microsoft's accessibility functions are enabled. You can also use the onscreen keyboard to type and send emails with your tongue!

![Game_Control](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/bw_tongue_mouse.gif?raw=true)

# Required Materials:

* Cthulhu Shield

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/cthulhusmall.jpg?raw=true)
* Arduino Uno or Mega or compatible clone with Atmega16U2 as USB to UART converter (it sounds like older boards using the Atmega8U2 may also work)

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/unosmall.jpg?raw=true)
* USB A to B Cable

![USB A to B Cable](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/usbsmall.jpg?raw=true)

* One 18 Channel flexible electrode array from Sapien LLC

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/ribbonsmall.jpg?raw=true)

# Required Software:
* This library
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [Flip programmer](https://www.microchip.com/developmenttools/ProductDetails/flip)


# Hardware Assembly:
Install Cthulhu Shield onto Arduino Uno or Arduino Mega and attach the USB cable and electrode array. 

# Example:
Open Arduino IDE. Once you have installed the Cthulhu Shield library (see 'Install Library' at end) go to **file**>**examples**>**Cthulhu-master** and open the **tactile_cursor** example sketch.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/arduino_tactile_cursor_example.jpg?raw=true)

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/arduino_brdselect_uno.jpg?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/arduino_comselect.jpg?raw=true)

![example](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/arduino_upload.jpg?raw=true)



Once you have downloaded the [Flip programmer](https://www.microchip.com/developmenttools/ProductDetails/flip), open the progam and select the ATmega16U2 device by selecting the IC icon in the upper left of the window. 

![flipchipselect](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/flipchipselect.jpg?raw=true)

With the Arduino powered, momentarily short these two pins together with a screwdriver or something metallic to put the ATmega16U2 into a state that allows to reprogram it.

![Unohack](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/unokeyboardhack.jpg?raw=true)

Click the USB cable icon in the upper left and select the 'USB' option from the dropdown. 

![USB](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/select_USB.jpg?raw=true)

Previously 'greyed-out' features in the window should now be available (if you can't connect and get an error message see section below titled 'Troubleshooting-Update Driver')

Select the Load HEX file button at the top of the window and navigate to and select the 'Arduino-keyboard-0.3.hex' file on your computer (located in the '16u2_firmware' folder of this example)

![load hex](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/firmwareselect.jpg?raw=true)

Once the firmware is selected, hit run to upload the new firmware to the ATmega16U2 chip on the Arduino.

![run](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/uploadfirmware.jpg?raw=true)

**Now unplug your Arduino from your computer to remove power and plug it back in again. Your computer should now recognize the arduino as a standard keyboard.**

Click on your windows search bar and search for and open 'control panel'.
![controlpanel](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/control_panel.jpg?raw=true)

Select'Ease of Access', and click 'Ease of Access' again in the window that opens.

![ease1](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/control_panel2.jpg?raw=true)

![ease2](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/easeofaccess1.jpg?raw=true)

Click **Make the mouse easier to use** and click the box to enable **Turn on mouse keys**.

![mouse1](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/access_mouse_seledt.jpg?raw=true)

![mouse2](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/turnonmousekeys.jpg?raw=true)

We recommned adjusting the speed and acceleration of the mouse to higher settings. To do this, go back to the main **Make the mouse easier to use** menu and select **Set up mouse keys** (note, the box to enable mouse keys should already be enabled).

![mouse3](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/setupmousekeys.jpg?raw=true)

Adjust the sliders as desired. We recommend max speed and medium-high acceleration.


![mouse4](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/speedcontrol.jpg?raw=true)

If you havent already, carefully lift the latch of the ZIF connector, insert the electrode array gold side down, and close the latch. 

Use the tip of your tongue to press the tactile 'buttons' on the electrodes at the front, back , and both sides of the array. The LED's on the Cthulhu Shield will change brightness when your tongue is contacting them, so look at them and move your tongue around to train up and practice. 

Use these buttons like a directional pad to move your cursor around the screen. Flatten your tongue against the array to press all electrodes to click. (click-hold/drag has not yet been implemented).

When you feel like it, enable the onscreen keyboard in the ease of access settings and type and email or novel. The predicted words suggessted at the top of the keyboard actual make typing pretty fast in most situations!

![key1](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/without_mouse_keyboard_select.jpg?raw=true)

![key2](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_cursor/jpgs/onscreenkeyboard.jpg?raw=true)

**Note: If you want your Arduino to act like a regular Arduino again (so you can load different sketches on it) you must short the pins together and repeat this process, selecting 'Arduino-usbserial-uno.hex' or 'Arduino-subserial-mega.hex'to put the standard Arduino firmware back onto the ATmega16U2.**



# Going Further:



# Acknowledgments: 
Inspiration for this project and Firmware for Atmega16U2 came directly from coopermaa at https://github.com/coopermaa/USBKeyboard










# Troubleshooting-Update Driver:
If you get an error message when trying to connect to your device in Flip, you may need to update the driver in your device manager. 

Make sure you are running java Runtime Environment 32, then go to **device manager** on your computer, find the 16U2 device, 

![16U2device](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/driverupdate1.jpg?raw=true)

right click and select **properties** > **update drivers**, **browse my computer for driver software** and navigate to and select the **Flip folder** on your computer. 

![16U2device2](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/driverupdate2.jpg?raw=true)

![16U2device2](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/driverupdate3.jpg?raw=true)

![16U2device2](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/driverupdate4.jpg?raw=true)

Once the **Flip folder** has been selected, click **update drivers**.

![16U2device2](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/driverupdate5.jpg?raw=true)


# Install Library:

Right now, the easiest way to install the Cthulhu library is by downloading the Zip file from github, and manually adding it from the arduino 'sketch' dropdown menu.

Navigate to the Cthulhu repo main page and download the zip file.

![zip](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/download_zip.jpg?raw=true)

Open Arduino and select **Include Library** > **Add .ZIP Library** from the **Sketch** dropdown menu.

![add library](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/arduino_add_zip_library.jpg?raw=true)

Navigate to the zip file you downloaded and select it (probably your 'Downloads' folder). 

The library should now be installed. 
