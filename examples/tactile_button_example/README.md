# Tactile Button Example

This example shows how to use the Cthulhu Shield and tri-state function of the the arduino analog pins (A0-A5) to create a (somewhat intense) stimulus waveform on the tongue at 4 'button' locations, and to sense whether the tongue is in contact with each button. 

If the LED is active, the LED's representing an electrode should noticiably brighten when the tongue is in contact with the electrode. 

The long pulses used here were selected to maximize the change in brightness of the LED's during tongue contact. 

The example will output an analog reading for each of the six buttons to the serial terminal if desired.