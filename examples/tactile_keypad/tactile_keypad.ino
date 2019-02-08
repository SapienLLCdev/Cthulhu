#include <Cthulhu.h>

/*
  Cthulhu Tactile Button Example - Example for activating certain electrodes and sensing whether the tongue is in contact with 
  each electrode.
  Created by Joel Moritz Jr Jan 2019
  Released into the public domain.
*/

/*
  This example shows how to use the Cthulhu Shield and tri-state function of the the arduino analog pins (A0-A5) to create 
  a (somewhat intense) stimulus waveform on the tongue at 4 'button' locations, and to sense whether the tongue is in 
  contact with each button. If the LED is active, the LED's representing an electrode should noticiably brighten when 
  the tongue is in contact with the electrode. More comfortable stimulating pulses can be used. The long pulses
  used here were selected to maximize the change in brightness of the LED's during tongue contact. 
  The example will output an analog reading for each of the six buttons to the serial terminal.
*/

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */



//two arrays I used to generate geometric patterns 

//  int cElectrodeMap[5][4] = 
//  {
//    {0, 0, 1, 0},
//    {2, 3, 4, 5},
//    {6, 7, 8, 9},
//    {10,11,12,13},
//    {14,15,16,17}
//  };


//these are waveform parameter as described by Kurt Kaczmarek here https://www.sciencedirect.com/science/article/pii/S1026309811001702
//than can be changed to create a large range of sensations on the tongue.
int  PP[] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
int  Pp[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
int  ON[] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};

int  myarray[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

Cthulhu mycthulhu; //creating and instance of 

          int tip;
          int back;
          int left;
          int right;
          

void setup() {
  // put your setup code here, to run once:
  mycthulhu.Begin();
  Serial.begin(9600); 
  //Serial.println("Pattern Demonstration begin...");
      pinMode(A2,INPUT);
          mycthulhu.UpdateStimuli(myarray, PP, Pp, IN, IP, ON);
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
          delayMicroseconds(100); // postive pulse 
          pinMode(A0, INPUT);
          pinMode(A1, INPUT);
          pinMode(A2, INPUT);
          pinMode(A3, INPUT);
          pinMode(A4, INPUT);
          pinMode(A5, INPUT);
     tip = (analogRead(A1) + analogRead(A2))/2;
        back = (analogRead(A0) + analogRead(A3))/2;
         left = analogRead(A4);
           right = analogRead(A5);
           delay(10);
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
          delayMicroseconds(100); // negative pulse 
}
delay(1);

  sendStrokes();
}



void sendStrokes()
{

if (tip > 550 && back > 550 && left > 550 && right > 550)
{
    buf[2] = 0x2c;    // Random character
    Serial.write(buf, 8); // Send keypress
 // releaseKey();
}
else{


if (tip > 550)
{
    buf[2] = 0x1a;    // Random character
    Serial.write(buf, 8); // Send keypress
  //releaseKey();
}
if (back > 550)
{
    buf[2] = 0x16;    // Random character
    Serial.write(buf, 8); // Send keypress
  releaseKey();
}
if (left > 550)
{
    buf[2] = 0x04;    // Random character
    Serial.write(buf, 8); // Send keypress
  //releaseKey();
}
if (right > 550)
{
    buf[2] = 0x07;    // Random character
    Serial.write(buf, 8); // Send keypress
 // releaseKey();
}
}
if (tip < 550 && back < 550 && left < 550 && right < 550)
{
//    buf[2] = 0x2c;    // Random character
//    Serial.write(buf, 8); // Send keypress
  releaseKey();
}
  
}






void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
}

