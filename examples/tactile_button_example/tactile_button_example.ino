#include <Cthulhu.h>

/*
  Cthulhu Tactile Button Example - Example for activating certain electrodes and sensing whether the tongue is in contact with 
  each electrode.
  Created by Joel Moritz Jr Jan 2019
  Released into the public domain.
*/

/*
  This example shows how to use the Cthulhu Shield and tri-state function of the the arduino analog pins (A0-A5) to create 
  a stimulus waveform on the tongue at 4 'button' locations, and to sense whether the tongue is in 
  contact with each button. If the LED is active, the LED's representing an electrode should noticiably brighten when 
  the tongue is in contact with the electrode. More comfortable stimulating pulses can be used. The long pulses
  used here were selected to maximize the change in brightness of the LED's during tongue contact. 
  The example will output an analog reading for each of the six buttons to the serial terminal.
*/

#define HighPeriod 100
#define LowPeriod 100



Cthulhu mycthulhu; //creating and instance of 



void setup() {
  mycthulhu.Begin();
  Serial.begin(9600); 

}

void loop() {


//

for(int i = 0; i<3;i++)
{
          digitalWrite(A0, HIGH);               
          digitalWrite(A1, HIGH);   
          digitalWrite(A2, HIGH);   
          digitalWrite(A3, HIGH);   
          digitalWrite(A4, HIGH);   
          digitalWrite(A5, HIGH);   
          //write pin 3-12 pulses
          delayMicroseconds(HighPeriod); // postive pulse 
          pinMode(A0, INPUT);
          pinMode(A1, INPUT);
          pinMode(A2, INPUT);
          pinMode(A3, INPUT);
          pinMode(A4, INPUT);
          pinMode(A5, INPUT);
          Serial.print(analogRead(A0));Serial.print(",");Serial.print(analogRead(A1));Serial.print(",");
          Serial.print(analogRead(A2));Serial.print(",");Serial.print(analogRead(A3));Serial.print(",");
          Serial.print(analogRead(A4));Serial.print(",");Serial.println(analogRead(A5));
          pinMode(A0,OUTPUT);
          pinMode(A1,OUTPUT);
          pinMode(A2,OUTPUT);
          pinMode(A3,OUTPUT);
          pinMode(A4,OUTPUT);
          pinMode(A5,OUTPUT);
          digitalWrite(A0, LOW);
          digitalWrite(A1, LOW);
          digitalWrite(A2, LOW);
          digitalWrite(A3, LOW);
          digitalWrite(A4, LOW);
          digitalWrite(A5, LOW);
          delayMicroseconds(LowPeriod); // negative pulse 
}
delay(1);
 
  
}



