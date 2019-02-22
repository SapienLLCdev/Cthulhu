#include <Cthulhu.h>
#include <SPI.h>
#include <ADXL362.h>

//a few variables used to accept serial commands
int discard;
int time;
int s;
String data = "";
int trodes[18];
int16_t XValue, YValue, ZValue, Temperature;
int16_t POSXThresh = 350;
int16_t NEGXThresh = -350;
int16_t POSYThresh = 350;
int16_t NEGYThresh = -350;
ADXL362 xl;

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


//these are waveform parameters as described by Kurt Kaczmarek here https://www.sciencedirect.com/science/article/pii/S1026309811001702
//these can be changed to create a large range of sensations on the tongue.
int  PP[] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
int  Pp[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
int  ON[] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};

int xaxisrecord[20];   // array to track the last 20 readings
int indextracker = 0;   // index to be used for xaxisrecord

Cthulhu mycthulhu; //creating an instance of Cthulhu

void setup() {
  
  Serial.begin(115200); 
  xl.begin(53);                   // Setup SPI protocol, Input is CS pin
  xl.beginMeasure();
  mycthulhu.Begin();

}

void loop() 
{
  for(int j = 0; j <=18; j++){    //turn off all electrodes
      trodes[j] = 0;
     }
  
  xl.readXYZTData(XValue, YValue, ZValue, Temperature); 
  Serial.print("\tXValue=");
  Serial.print(XValue);   

  Serial.print("\tYValue=");
  Serial.println(YValue);

//delay(100);

  if(XValue >= POSXThresh)
  {
    trodes[3] = 1;     //turn on electrodes 3 and 4 array[3] = 1;
    trodes[4] = 1;

   int Xintensity = map(XValue,350,1500,1,50);

   Pp[3] = Xintensity+7;
   PP[3] = Xintensity+8;
   ON[3] = (Xintensity+10)/10;
   IP[3] = 100+Xintensity;
 
   Pp[4] = Xintensity+7;
   PP[4] = Xintensity+8;
   ON[4] = (Xintensity+10)/10;
   IP[4] = 100+Xintensity;
  }
    
  if(XValue <= NEGXThresh)
  {
    trodes[15] = 1;   //turn on electrodes 15 and 16
    trodes[16] = 1;

   int Xintensity = map(XValue,-350,-1500,1,50);
   
   Pp[15] = Xintensity+7;
   PP[15] = Xintensity+8;
   ON[15] = (Xintensity+10)/10;
   IP[15] = 100+Xintensity;
 
   Pp[16] = Xintensity+7;
   PP[16] = Xintensity+8;
   ON[16] = (Xintensity+10)/10;
   IP[16] = 100+Xintensity;
  }

  if(YValue >= POSYThresh)
  {
    trodes[9] = 1;     //turn on electrodes 9 and 13
    trodes[13] = 1;

   int Yintensity = map(YValue,350,1500,1,50);
    
   Pp[9] = Yintensity+7;
   PP[9] = Yintensity+8;
   ON[9] = (Yintensity+10)/10;
   IP[9] = 100+Yintensity;
 
   Pp[13] = Yintensity+7;
   PP[13] = Yintensity+8;
   ON[13] = (Yintensity+10)/10;
   IP[13] = 100+Yintensity;
    
  }
  
  if(YValue <= NEGYThresh)
  {
    trodes[6] = 1;   //turn on electrodes 6 and 10
    trodes[10] = 1;

   int Yintensity = map(YValue,-350,-1500,1,50);
   
   Pp[6] = Yintensity+7;
   PP[6] = Yintensity+8;
   ON[6] = (Yintensity+10)/10;
   IP[6] = 100+Yintensity;
 
   Pp[10] = Yintensity+7;
   PP[10] = Yintensity+8;
   ON[10] = (Yintensity+10)/10;
   IP[10] = 100+Yintensity;

  }
  
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
