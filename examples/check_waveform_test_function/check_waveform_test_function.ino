#include <Cthulhu.h>





//these are waveform parameter as described by Kurt Kaczmarek here https://www.sciencedirect.com/science/article/pii/S1026309811001702
//than can be changed to create a large range of sensations on the tongue.

int trodes[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int  PPP[] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
int  Pp[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
int  ON[] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};

Cthulhu mycthulhu; 

void setup() 
{
  mycthulhu.Begin();
  Serial.begin(9600); //setup serial port
  Serial.println("Check Waveform Test Program"); //print name of program

}


void loop() 
{

int myerror = mycthulhu.CheckWaveform (trodes, PPP, Pp, IN, IP, ON); //set myerror equal to the output of CheckWaveform with these input parameters


Serial.print("CheckWaveform Returns: ");Serial.println(myerror); //print the error

      delay(1000); //delay 1 second
}
