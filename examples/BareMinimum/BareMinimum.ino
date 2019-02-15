#include <Cthulhu.h>

/*
  This example shows how to use Sapien LLC's Cthulhu Sheild to electrotactiley stimulate the tongue.
  In this example, one electrode is set active, and five stimulation parameters are set. 
  The Cthulhu library is initialized, and serial output is enabled. 
  The CheckWaveform function is used to verify that we have entered a valid waveform for all electrodes,
  if the paramters we entered are OK, then the stimulus waveform is updated (UpdateStimuli), and the pulsetrain is sent to the 
  active electrodes (Stimulate) for one stimulation cycle (36ms). 
  If the waveform is invalid, the error code is printed to the serial monitor and the stimulus is not updated or produced. 
  This loops indefinitely.
*/

/*
  Cthulhu Tongue Stimulation BareMinimum Example - Example for stimulating the tongue using electrotactile stimulation.
  Created by Joel Moritz Jr Feb 2019
  Released into the public domain.
*/




Cthulhu mycthulhu; //creating and instance of Cthulhu

//array to hold which electrodes should be on or off. In this example, one electrode is turned on.
int trodes[] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

//pulse period for each electrode, in microseconds. Can be manipulated with Pp and IN to change the intensity of the sensation.
int  PP[] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10}; 

//length of positive pulse for each electrode, in microseconds. Can be manipulated with PP and IN to change the intensity of the sensation.
int  Pp[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};

//inner burst number (how many pulses in each inner burst). Can be manipulated with PP and Pp to change the intensity of the sensation.
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};

//inner burst period.  In microseconds. Can change quality, or 'feel' of sensation.
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150}; 

//Outer burst number. Can change quality, or 'feel' of sensation.
int  ON[] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}; 


//Requirements:
//Pp must be less than PP.                    CheckWaveform Error 1.
//(PP*IN) must be less than IP.               CheckWaveform Error 2.
//IP*IN must be less than 2000 microseconds.  CheckWaveform Error 3.



void setup() {
  mycthulhu.Begin(); //Initialize Cthulhu library
  Serial.begin(9600); //Set serial output datarate
}

void loop() {
  
  //check our waveform parameters and verify that they meet requirements
  int myerror = mycthulhu.CheckWaveform(trodes, PP, Pp, IN, IP, ON);

  if(myerror == 0) //if our waveform parameters are ok, update the stimulation parameters and perform one 36ms stimulation cycle.
  {
    mycthulhu.UpdateStimuli(trodes, PP, Pp, IN, IP, ON); //update waveform parameters
    mycthulhu.Stimulate(); //create the stimulation pulsetrain on the electrodes
  }
  else
  {
    //if we entered an invalid waveform, tell us which rule we violated so we can fix it
    Serial.print("Error in waveform parameters. CheckWaveform Error: ");Serial.println(myerror); 
  }

}
