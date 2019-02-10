## Using the Cthulhu Shield and Arduino Uno to send Keystrokes

# Introduction:

The Cthulhu Shield and electrode array can be used to sense whether or not your tongue is in contact with certain electrodes. Combined with the electrotactile ability of the Cthulhu Shield, this can be used to create 'virtual' tactile buttons that can be pressed with the tongue. With some minor software hacking of the Arduino, we can get the Arduino-Cthulhu to tell the computer that it is a keyboard and send keystrokes to your computer with your tongue.

# Required Materials:

* Cthulhu Shield

![Cthulhu Shield](cthulhusmall.jpg)
* Arduino Uno or Mega or compatible clone with Atmega16U2 as USB to UART converter (it sounds like older boards using the Atmega8U2 may also work)

![Cthulhu Shield](unosmall.jpg)
* USB A to B Cable

![USB A to B Cable](usbsmall.jpg)

* One 18 Channel flexible electrode array from Sapien LLC

![Cthulhu Shield](ribbonsmall.jpg)

# Required Software:
* This library
* [Arduino IDE](https://www.arduino.cc/en/Main/Software)
* [Flip programmer](https://www.microchip.com/developmenttools/ProductDetails/flip)


# Hardware Assembly:
Install Cthulhu Shield onto Arduino Uno or Arduino Mega and attach the USB cable and electrode array. 

# Example:



# Going Further:


# Acknowledgments: 
Inspiration for this project and Firmware for Atmega16U2 come directly from coopermaa at https://github.com/coopermaa/USBKeyboard
