## Cthulhu_Shield_Arduino

![Cthulhu Shield](https://ksr-ugc.imgix.net/assets/023/898/915/445716db19d7a5d34502a584e91812b8_original.gif?ixlib=rb-1.1.0&w=680&fit=max&v=1548532149&auto=format&gif-q=50&q=92&s=bc67d6bd83fecd3067255431a1aef305)

This is a library for using the Cthulhu Shield sensory substitution/augmentation development kit created by [Sapien LLC](http://sapienllc.com/). 

If you like what you see here, please consider backing us or donating on [Kickstarter!](https://www.kickstarter.com/projects/2007440405/cthulhu-shield?ref=user_menu)

The Cthulhu Shield is an open-source Arduino Uno and Arduino Mega compatible sensory substitution/sensory augmentation device. It uses an 18 electrode grid to tactiley display signals on the tongue. The electrodes on the array can be activated with patterns of electrical pulses to depolarize nerve membranes in the tongue to create different types of touch sensations. You can use these touch sensations to draw shapes or simple images on the tongue, feel different sound frequencies, or receive turn by turn directions with your tongue.

Additionally, the Cthulhu Shield can sense whether or not your tongue is in contact with different electrodes using capacitive sensing. You can use the Cthulhu Shield to send keystrokes to your computer, control the cursor, or even control a mobility device. 

In this repository, we have provided a number of example projects to get you started with your Cthulhu, but we encourage you to experiment and build your own senses!

There are some awesome uses of sensory substitution already out there. For more information on these uses, or sensory substitution or augmentation in general, take a look at the links below. 
* [Brainport](https://www.youtube.com/watch?v=OKd56D2mvN0)
* [Wikipedia](https://en.wikipedia.org/wiki/Sensory_substitution)
* [Hear with your tongue](https://source.colostate.edu/words-mouth-csu-device-lets-hear-tongue/)
* [TedTalk](https://www.ted.com/talks/david_eagleman_can_we_create_new_senses_for_humans?language=en)


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
The Cthulhu Shield is made to be powered by plugging it directly into an Arduino Uno or Mega, and connecting the arduino to a USB cable attached to a properly grounded computer, or a smartphone or external battery pack. Users should not power their Arduino/Cthulhu Shield system with an AC wall adaptor, as a small number of these adaptors are not properly grounded or are otherwise unsafe and can cause injury or death if used with any electronic device.

**Input:**
When used with an Arduino Uno, the Cthulhu Shield can receive information directly from the USB port connected to a computer or smartphone, or via broken out Serial pins (RX, TX) which can used to communicate with other Arduinos/microcontrollers, or embedded devices such as Bluetooth modules or sensors with serial outputs. With an Arduino Mega, the extra IO pins can be leveraged to receive Digital or Analog signals that can be used to change the tactile output of the Cthulhu Shield. 

**Output:**
When used with an Arduino Uno, the Cthulhu Shield can send information directly via USB port connected to a computer or smarptphone, or via broken out Serial pins (RX, TX) which can used to communicate with other Arduinos/microcontrollers, or embedded devices such as Bluetooth modules or sensors with serial outputs. With an Arduino Mega, the extra IO pins can be leveraged to send Digital or Analog signals to external devices. 

**Electrode Control:**
Different types of sensations can be created on different electrodes and tongue locations by changing the pattern of pulses generated on each electrode. This can be done with the Cthulhu.UpdateStimuli() function. A user changes values in six (6), eighteen (18) element arrays. The values in these arrays correspond to whether one of the 18 electrodes is on or off, and what type of pulse, and pattern of pulses, is created on each electrode. Changing these patterns changes the type and quality of the sensation perceived by the user. This library was adapted from [work by Kurt Kaczmarek](https://www.sciencedirect.com/science/article/pii/S1026309811001702) and altered for the needs of our early research at Sapien LLC.

**Tongue Position Sensing:**
During electrotactile stimulation with the Cthulhu Shield, the Arduino can quickly sense the electrical potential on a given electrode, which changes if the tongue is in contact with the electrode or not. Placing your tongue on certain electrodes but not others, or swiping your tongue across different electrodes, can be detected by the Arduino, which can then send serial information (or with minor hacking, keystrokes and HID signals) to a computer or smartphone via the USB port, or external Bluetooth modules. 

Currently, tongue-position-sensing is supported only on ADC enabled Arduino pins (A0-A5 on the Uno and Mega). Position sensing on digital only pins should be possible and may be implemented in the near future. 

# How to Use this Repository:

If you are new to Github, Sparkfun has created an [excellent Github tutorial](https://learn.sparkfun.com/tutorials/using-github/all). If you want to get up and running quickly, just take a look at the [Download ZIP](https://learn.sparkfun.com/tutorials/using-github/all#download-zip) section.

Similarly, if you are new to Arduino, Sparkfun once again has a great [guide to installing Arduino Libraries](https://learn.sparkfun.com/tutorials/installing-an-arduino-library). After downloading the .ZIP file of the library you want from Github, follow the instructions above to integrate it with the Arduino IDE.

Please see the README files in the examples linked above for more information on their specific implementations!
