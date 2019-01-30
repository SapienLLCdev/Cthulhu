## Cthulhu_Shield_Arduino

![Cthulhu Shield](https://ksr-ugc.imgix.net/assets/023/898/915/445716db19d7a5d34502a584e91812b8_original.gif?ixlib=rb-1.1.0&w=680&fit=max&v=1548532149&auto=format&gif-q=50&q=92&s=bc67d6bd83fecd3067255431a1aef305)

This is a library for using the Cthulhu Shield sensory substitution/augmentation development kit created by [Sapien LLC](http://sapienllc.com/). 

If you like what you see here, please consider donating to our [Kickstarter!](https://www.kickstarter.com/projects/2007440405/cthulhu-shield?ref=user_menu).

The Cthulhu Shield is an open-source Arduino Uno and Arduino Mega compatible sensory substitution/sensory augmentation device. It uses an 18 electrode grid to tactiley display signals on the tongue. In this repository, we have provided a number of example projects to get you started with your Cthulhu, but we encourage you to experiment and build your own senses!

# Repository Contents:

* [Cthulhu Camera Demo](https://github.com/SapienLLCdev/Cthulhu/tree/master/Android%20Examples/CthulhuCameraDemo)
* [Waveform Test](https://github.com/SapienLLCdev/Cthulhu/tree/master/examples/check_waveform_test_function)
* [Demonstration](https://github.com/SapienLLCdev/Cthulhu/tree/master/examples/demonstration_example)
* [GPS Directions](https://github.com/SapienLLCdev/Cthulhu/tree/master/examples/directions_example)
* [Thermal Camera](https://github.com/SapienLLCdev/Cthulhu/tree/master/examples/mega_heat_cam_with_shield)
* [Tactile Button](https://github.com/SapienLLCdev/Cthulhu/tree/master/examples/tactile_button_example)
* [Tactile Cursor](https://github.com/SapienLLCdev/Cthulhu/tree/master/examples/tactile_cursor)
* [Tactile Keypad](https://github.com/SapienLLCdev/Cthulhu/tree/master/examples/tactile_keypad)

# Cthulhu Shield Schematic:

![Cthulhu Shield Schematic](https://github.com/SapienLLCdev/Cthulhu/blob/master/Cthulhu_Shield_Rev2e.jpg).

# How to Use the Cthulhu Shield:

**Power:**
The Cthulhu Shield is made to be powered by either by plugging it directly into an Arduino Uno or Mega, or by connecting a battery directly to the shield via the broken out 5v and GND pins near the LEDs. 

**Input:**
When used with an Arduino Uno, the Cthulhu Shield can receive information directly via broken out Serial pins (RX, TX). With an Arduino Mega, the extra IO pins can be leveraged to send Digital or Analog signals to the Cthulhu Shield. 

**Electrode Control:**
Updates coming soon...

# How to Use this Repository:

If you are new to Github, Sparkfun has created an ![excellent Github tutorial](https://learn.sparkfun.com/tutorials/using-github/all). If you want to get up and running quickly, just take a look at the ![Download ZIP](https://learn.sparkfun.com/tutorials/using-github/all#download-zip) section.

Similarly, if you are new to Arduino, Sparkfun once again has a great ![guide to installing Arduino Libraries](https://learn.sparkfun.com/tutorials/installing-an-arduino-library). After downloading the .ZIP file of the library you want from Github, follow the instructions above to integrate it with the Arduino IDE.

Please see the README files in the examples linked above for more information on their specific implementations!
