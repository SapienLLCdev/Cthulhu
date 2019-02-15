#include <Cthulhu.h>


/*
  This example shows how to display tactile patterns on the tongue using Sapien LLC's Cthulhu Sheild using the UpdateStimulus, 
  and Stimulate commands in the Cthulhu library. The program demonstrates some types of patterns 
  that can be presented on the tongue. 
  Every time the arduino is reset, the demonstration patterbs will execute once. 
*/

/*
  Cthulhu Tongue Stimulation Example - Example for stimulating the tongue using electrotactile stimulation.
  Created by Joel Moritz Jr Jan 2019
  Contributions by Marco Martinez
  Released into the public domain.
*/




int array[18];


//two arrays I used to generate geometric patterns 

  int cElectrodeMap[5][4] = 
  {
    {0, 0, 1, 0},
    {2, 3, 4, 5},
    {6, 7, 8, 9},
    {10,11,12,13},
    {14,15,16,17}
  };

    int on[5][4] = 
  {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  };


//these are waveform parameter as described by Kurt Kaczmarek here https://www.sciencedirect.com/science/article/pii/S1026309811001702
//than can be changed to create a large range of sensations on the tongue.
int  PP[] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
int  Pp[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
int  ON[] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};

Cthulhu mycthulhu; //creating and instance of Cthulhu

//a function to update geometric patterns in the demo at the beginning of the program
void updatepattern()
{
  //Take care of the first two elements outside the main square
    array[cElectrodeMap[0][1]] = on[0][1];
   // Serial.print("array ");Serial.print(cElectrodeMap[i][j]);Serial.print("  is ");Serial.print("  is ");
    array[cElectrodeMap[0][2]] = on[0][2];
//if the On array is ative, set the corresponding electrode active.
for (int j = 0; j<4;j++)
{
for (int i = 1; i<5;i++)
{
    array[cElectrodeMap[i][j]] = on[i][j];
}
}
}

// a demonstration of geometric patterns (lines, sweeps, pulsing X's
void demonstration()
{

  //lines top to bottom 5x
for (int m = 0; m<5 ; m++)
{ Serial.println("Sweeping lines top to bottom.");
for (int i = 0;i<5;i++)
{
  on[i][0] = 1;on[i][1] = 1;on[i][2] = 1;on[i][3] = 1;
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
  for (int k = 0 ; k<3 ; k++)
  {
  mycthulhu.Stimulate();
  }
on[i][0] = 0;on[i][1] = 0;on[i][2] = 0;on[i][3] = 0;
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
}
}



  //lines left to right 5x
for (int m = 0; m<5 ; m++)
{Serial.println("Sweeping lines left to right.");
for (int i = 0;i<4;i++)
{
  on[0][i] = 1;on[1][i] = 1;on[2][i] = 1;on[3][i] = 1;on[4][i] = 1;
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
  for (int k = 0 ; k<3 ; k++)
  {
  mycthulhu.Stimulate();
  }
  on[0][i] = 0;on[1][i] = 0;on[2][i] = 0;on[3][i] = 0;on[4][i] = 0;
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
}
}

  //diagonal point 5x
    for (int i = 0;i<18;i++)
{Serial.println("Sweeping points diagonally top left to bottom right.");
  ON[i] = 10;
}
for (int m = 0; m<5 ; m++)
{
for (int i = 0;i<4;i++)
{
  on[i+1][i] = 1;
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
  for (int k = 0 ; k<3 ; k++)
  {
  mycthulhu.Stimulate();
  }
  on[i+1][i] = 0;
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
}
}
  for (int i = 0;i<18;i++)
{
  ON[i] = 5;
}


  //Pulsing X 5x
  on[1][0] = 1;on[2][1] = 1;on[3][2] = 1;on[4][3] = 1;
  on[4][0] = 1;on[3][1] = 1;on[2][2] = 1;on[1][3] = 1;
    updatepattern();
for (int m = 0; m<5 ; m++)
{Serial.println("Pulsing 'X' with varying intensity.");
for (int i = 1;i<50;i++)
{
    for (int x = 0;x<18;x++)
{
 Pp[x] = i+7;
 PP[x] = i+8;
 ON[x] = (i+10)/10;
 IP[x] = 100+i;
}
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
  for (int k = 0 ; k<1 ; k++)
  {
  mycthulhu.Stimulate();
  }
}
}
    for (int x = 0;x<18;x++)
{
  Pp[x] = 9;
}
  on[1][0] = 0;on[2][1] = 0;on[3][2] = 0;on[4][3] = 0;
  on[4][0] = 0;on[3][1] = 0;on[2][2] = 0;on[1][3] = 0;
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
}




void setup() 
{
  mycthulhu.Begin();
  Serial.begin(9600); 
  Serial.println("Pattern Demonstration begin...");
  demonstration(); //run through demonstration once
}


void loop() 
{
  //do nothing
}








