#include <Cthulhu.h>

/*
 * This example shows how to activate electrodes on the Cthulhu Shield electrode array using 
 * Serial input (from USB port, or an external device like a bluetooth module or another arduino)
 * Stimulation parameters are pre-set, and the serial input simply turns different electrodes on or off.
 * 
 * This eample works with the CthulhuCameraMotionDemo android app available on the android store https://play.google.com/store/apps/details?id=funkatronics.code.cthulhucamerademo
 * and the Cthulhu Tactile waves demo app soon to be available.
*/

/*
  Cthulhu Tongue Stimulation Serial Input Example - Example for stimulating the tongue using electrotactile stimulation.
  Created by Joel Moritz Jr Feb 2019
  Contributions by Marco Martinez
  Released into the public domain.
*/



//a few variables used to accept serial commands
int discard;
int time;
int s;
String data = "";
int array[18];


//these are waveform parameter as described by Kurt Kaczmarek here https://www.sciencedirect.com/science/article/pii/S1026309811001702
//than can be changed to create a large range of sensations on the tongue.
int  PP[] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
int  Pp[] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
int  ON[] = {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2};

Cthulhu mycthulhu; //creating and instance of Cthulhu




void setup() 
{
  mycthulhu.Begin();
  Serial.begin(9600); 
}


void loop() 
{
  if(Serial.available()) //monitor the serial line, update stimulus parameters, and continuously stimulate.
  { // If the bluetooth sent any characters
    readPacket();
    
    for (int e = 0; e < 18; e++)
    {
      array[e] = 0;
    }

    // lengh should be 4x4=16
    for (int e = 0; e < data.length(); e++)
    {
      // set pixel treshold value to 10 [1,255]
      if((int)data[e]>10)
      {
        // skip electrodes 0 and 1
        array[e+2] = 1;  
      }

      //set pixel value close to 150 for IP
      IP[e+2]=((int)data[e]/10)*30; // floor the value and amplify by 3
    }
    
    mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
  }
  else 
  {
    mycthulhu.Stimulate();
  }
      
}


//read a packet in from the UART. Format is:
// 01 02 03 0a 12 00 will turn on electrodes 0,1, 2, 9, and 17 in the array above
// 00 00 will deactivate all electrodes.

void readPacket() 
{
  data = "";
  while(1) 
  {
    int current = Serial.read();
    if(current != 0) {
      data += (char)current;
    }
    else 
    {
      data += '\0';
      break;
    }
  }
}
