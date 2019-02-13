## Using the Cthulhu Shield and Arduino Uno to send Keystrokes

# Introduction:

The Cthulhu Shield and electrode array can be used to sense whether or not your tongue is in contact with certain electrodes. Combined with the electrotactile ability of the Cthulhu Shield, this can be used to create 'virtual' tactile buttons that can be pressed with the tongue. With some minor software hacking of the Arduino, we can get the Arduino-Cthulhu to tell the computer that it is a keyboard and send keystrokes to your computer with your tongue.

# Required Materials:

* Cthulhu Shield

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/cthulhusmall.jpg?raw=true)
* Arduino Uno or Mega or compatible clone with Atmega16U2 as USB to UART converter (it sounds like older boards using the Atmega8U2 may also work)

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/unosmall.jpg?raw=true)
* USB A to B Cable

![USB A to B Cable](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/usbsmall.jpg?raw=true)

* One 18 Channel flexible electrode array from Sapien LLC

![Cthulhu Shield](https://github.com/SapienLLCdev/Cthulhu/blob/master/examples/tactile_keypad/jpgs/ribbonsmall.jpg?raw=true)

# Required Software:
* This library
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [Flip programmer](https://www.microchip.com/developmenttools/ProductDetails/flip)


# Hardware Assembly:
Install Cthulhu Shield onto Arduino Uno or Arduino Mega and attach the USB cable and electrode array. 

# Example:
Once you have installed the Cthulhu Shield library go to **file**>**examples**>**Cthulhu-master** and open the **tactile_keypad** example sketch.

Set your board and serial port from the **tools** dropdown menu and upload the sketch to your Arduino Uno or Mega.

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



**Note: If you want your Arduino to act like a regular Arduino again (so you can load different sketches on it) you must short the pins together and repeat this process, selecting 'Arduino-usbserial-uno.hex' or 'Arduino-subserial-mega.hex'to put the standard Arduino firmware back onto the ATmega16U2. **



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

