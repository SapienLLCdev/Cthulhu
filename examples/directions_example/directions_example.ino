#include <Cthulhu.h>


/*
  Cthulhu Tongue Stimulation Example - Example for stimulating the tongue using electrotactile stimulation.
  Created by Joel Moritz Jr Jan 2019
  Contributions by Marco Martinez
  Released into the public domain.
*/

/*
  This example shows how to display tactile patterns on the tongue using Sapien LLC's Cthulhu Sheild, an arduino Mega, the Komoot
  app, and BLE to UART module (an esp32 with custom firmware in our example), to peform hands/eyes/and ears free navigation.
  Applications include motorcycling, and other operational environments where you might need directions, but do not 
  want to distract your hands/eyes/ears from what they are already doing. 

*/



int array[18];


byte directionvalue;
uint32_t meters;

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
int  Pp[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
int  ON[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};

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

void left()
{
  on[1][0] = 1;on[2][0] = 1;on[3][0] = 1;on[4][0] = 1;
  on[1][1] = 1;on[2][1] = 1;on[3][1] = 1;on[4][1] = 1;
    updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
}
void right()
{
    on[1][3] = 1;on[2][3] = 1;on[3][3] = 1;on[4][3] = 1;
    on[1][2] = 1;on[2][2] = 1;on[3][2] = 1;on[4][2] = 1;
    updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
}

void uturn()
{
  on[4][0] = 1;on[4][1] = 1;on[4][2] = 1;on[4][3] = 1;
  on[3][0] = 1;on[3][1] = 1;on[3][2] = 1;on[3][3] = 1;
    updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
}


//on[i][0] = 0;on[i][1] = 0;on[i][2] = 0;on[i][3] = 0;
//  updatepattern();
//  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);




//45 miles per hour is 20meters/second, 
//City block is about 274 Meters
//want 10x per second flash within one block, round to 300m
//Want solid within 40m
//want steadily increase up to 5x per second if left or right within 2km (roughly 2 minutes out)
//if direction is greater than or equal to 4 and less than or equal to 12, and distance is less than 2000, but greater 
//than 274 meters flash for one second with flash per second equal to flashpersec= 6-distance(5/2000)

void Direct()
{
  simplifydirections();
      if(directionvalue>3 && directionvalue<13 && meters<=40)
  {
    mycthulhu.Stimulate();
  }
      else if(directionvalue>3 && directionvalue<13 && meters<274)
  {
    flash(10);
  }
   else if(directionvalue>3 && directionvalue<13 && meters<2000 && meters>274)
  {
    int flashpersec = 6 - meters*(5/2000);
    flash(flashpersec);
  }


}

void simplifydirections()
{
  if (directionvalue == 4 || directionvalue == 5 || directionvalue == 6 || directionvalue == 11 || directionvalue == 15 || directionvalue == 20 || directionvalue == 22 || directionvalue == 24 ||directionvalue == 25)
  {
    left();
    Serial.println("left");
  }
  if (directionvalue == 7 || directionvalue == 8 || directionvalue == 9 || directionvalue == 10 || directionvalue == 16 || directionvalue == 18 || directionvalue == 19 || directionvalue == 26 || directionvalue == 28)
  {
    right();
    Serial.println("right");
  }

  if (directionvalue == 12)
  {
    uturn();
    Serial.println("uturn");
  }
}

void flash( int freqhz)
{
    int periodms = 1000/freqhz;
    Serial.print("periodms = "); Serial.println(periodms);
  for (int i = 0;i<freqhz;i++)
  {
    for(int  j = 0 ; j<((periodms/2)/UNOSHIELD_REFRESHRATE);j++)
    {
       mycthulhu.Stimulate(); //will last 36 ms which is UNOSHIELD_REFRESHRATE
    }

    mycthulhu.StopStimulus();
    delay(periodms/2);    
  }
}


void updatedirections()
{
  int buff[50];
  int i = 0;
while (Serial1.available())
{
  
  buff[i] = Serial1.read();
  //Serial.print(buff[i]);
  i= i +1;
}
directionvalue = buff[4];
Serial.print("direction is : ");Serial.println(directionvalue);
meters = buff[5] + (buff[6]<<8) + (buff[7]<<16) + (buff[8]<<24);
Serial.print("distance is : ");Serial.println(meters);
}


void clear_elecs()
{
  for (int m = 0; m<5 ; m++)
{
for (int i = 0;i<4;i++)
{
  on[m][i] = 0;
}
}
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
}

void setup() 
{
  mycthulhu.Begin();
  Serial.begin(115200); 
    Serial1.begin(115200); 
}


void loop() 
{
  if(Serial1.available()>=20) //monitor the serial line, update stimulus parameters, and continuously stimulate.
  { // If the bluetooth sent any characters
    delay(50);
    updatedirections();
  }
  clear_elecs();
Direct();      
}









