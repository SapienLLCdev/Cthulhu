#include <Cthulhu.h>

//a few variables used to accept serial commands
int discard;
int time;
int s;
String data = "";
int trodes[18];

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
int  PP[] = {50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50};
int  Pp[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
int  ON[] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};

const int FSR_PIN = A7; // Pin connected to FSR/resistor divider

// Measure the voltage at 5V and resistance of your 3.3k resistor, and enter
// their value's below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 3230.0; // Measured resistance of 3.3k resistor

Cthulhu mycthulhu; //creating and instance of Cthulhu

void setup() 
{
  Serial.begin(9600);
  pinMode(FSR_PIN, INPUT);
  mycthulhu.Begin();

}

void loop() 
{
  for(int j = 0; j <=18; j++){    //turn off all electrodes
      trodes[j] = 0;
  }
  
  int fsrADC = analogRead(FSR_PIN);                          
  // If the FSR has no pressure, the resistance will be
  // near infinite. So the voltage should be near 0.
  if (fsrADC != 0) // If the analog reading is non-zero
  {
    // Use ADC reading to calculate voltage:
    float fsrV = fsrADC * VCC / 1023.0;
    // Use voltage and static resistor value to 
    // calculate FSR resistance:
    float fsrR = R_DIV * (VCC / fsrV - 1.0);
    Serial.println("Resistance: " + String(fsrR) + " ohms");
    // Guesstimate force based on slopes in figure 3 of
    // FSR datasheet:
    float force;
    float fsrG = 1.0 / fsrR; // Calculate conductance
    // Break parabolic curve down into two linear slopes:
    if (fsrR <= 600) 
      force = (fsrG - 0.00075) / 0.00000032639;
    else
      force =  fsrG / 0.000000642857;

 int intforce = int(force);              
   

  if(intforce > 0)                       
  {
    trodes[2] = 1;     //turn on electrodes
    trodes[7] = 1;
    trodes[12] = 1;
    trodes[17] = 1;
    trodes[5] = 1;
    trodes[8] = 1;
    trodes[11] = 1;
    trodes[14] = 1;

   int forceintensity = map(intforce,0,5000,1,50);

   Pp[2] = forceintensity+7;
   PP[2] = forceintensity+8;
   ON[2] = (forceintensity+10)/10;
   IP[2] = 100+forceintensity;

   Pp[7] = forceintensity+7;
   PP[7] = forceintensity+8;
   ON[7] = (forceintensity+10)/10;
   IP[7] = 100+forceintensity;
 
   Pp[12] = forceintensity+7;
   PP[12] = forceintensity+8;
   ON[12] = (forceintensity+10)/10;
   IP[12] = 100+forceintensity;

   Pp[17] = forceintensity+7;
   PP[17] = forceintensity+8;
   ON[17] = (forceintensity+10)/10;
   IP[17] = 100+forceintensity;

   Pp[5] = forceintensity+7;
   PP[5] = forceintensity+8;
   ON[5] = (forceintensity+10)/10;
   IP[5] = 100+forceintensity;

   Pp[8] = forceintensity+7;
   PP[8] = forceintensity+8;
   ON[8] = (forceintensity+10)/10;
   IP[8] = 100+forceintensity;

   Pp[11] = forceintensity+7;
   PP[11] = forceintensity+8;
   ON[11] = (forceintensity+10)/10;
   IP[11] = 100+forceintensity;

   Pp[14] = forceintensity+7;
   PP[14] = forceintensity+8;
   ON[15] = (forceintensity+10)/10;
   IP[14] = 100+forceintensity;
  }
   
 Serial.println();
   mycthulhu.UpdateStimuli(trodes, PP, Pp, IN, IP, ON); //update waveform parameters
   mycthulhu.Stimulate(); //create the stimulation pulsetrain on the electrodes
    int delay_force = map(intforce, 0, 5000, 500, 100);
    delay(delay_force);
  }
  else
  {
    // No pressure detected
  }
}
