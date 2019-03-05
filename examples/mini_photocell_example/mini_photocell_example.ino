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

const int LIGHT_PIN = A7; // Pin connected to voltage divider output
//const int LED_PIN = 13; // Use built-in LED as dark indicator

// Measure the voltage at 5V and the actual resistance of your
// 47k resistor, and enter them below:
const float VCC = 4.98; // Measured voltage of Ardunio 5V line
const float R_DIV = 4660.0; // Measured resistance of 3.3k resistor

// Set this to the minimum resistance require to turn an LED on:
const float DARK_THRESHOLD = 10000.0;
Cthulhu mycthulhu; //creating and instance of Cthulhu

void setup() 
{
  Serial.begin(9600);
  pinMode(LIGHT_PIN, INPUT);
//  pinMode(LED_PIN, OUTPUT);
  mycthulhu.Begin();
}

void loop() 
{
  for(int j = 0; j <=18; j++){    //turn off all electrodes
      trodes[j] = 0;
  }
  
  // Read the ADC, and calculate voltage and resistance from it
  int lightADC = analogRead(LIGHT_PIN);
  if (lightADC > 0)
  {
    // Use the ADC reading to calculate voltage and resistance
    float lightV = lightADC * VCC / 1023.0;
    float lightR = R_DIV * (VCC / lightV - 1.0);
    Serial.println("Voltage: " + String(lightV) + " V");
    Serial.println("Resistance: " + String(lightR) + " ohms");

    // If resistance of photocell is greater than the dark
    // threshold setting, turn the LED on.
//    if (lightR >= DARK_THRESHOLD)
//      digitalWrite(LED_PIN, HIGH);
//    else
//      digitalWrite(LED_PIN, LOW);
 
 int intlight = int(lightV);               
                      
 
    trodes[2] = 1;     //turn on electrodes
    trodes[7] = 1;
    trodes[12] = 1;
    trodes[17] = 1;
    trodes[5] = 1;
    trodes[8] = 1;
    trodes[11] = 1;
    trodes[14] = 1;

   int lightintensity = map(intlight,0.01,3,1,50);

   Pp[2] = lightintensity+7;
   PP[2] = lightintensity+8;
   ON[2] = (lightintensity+10)/10;
   IP[2] = 100+lightintensity;

   Pp[7] = lightintensity+7;
   PP[7] = lightintensity+8;
   ON[7] = (lightintensity+10)/10;
   IP[7] = 100+lightintensity;
 
   Pp[12] = lightintensity+7;
   PP[12] = lightintensity+8;
   ON[12] = (lightintensity+10)/10;
   IP[12] = 100+lightintensity;

   Pp[17] = lightintensity+7;
   PP[17] = lightintensity+8;
   ON[17] = (lightintensity+10)/10;
   IP[17] = 100+lightintensity;

   Pp[5] = lightintensity+7;
   PP[5] = lightintensity+8;
   ON[5] = (lightintensity+10)/10;
   IP[5] = 100+lightintensity;

   Pp[8] = lightintensity+7;
   PP[8] = lightintensity+8;
   ON[8] = (lightintensity+10)/10;
   IP[8] = 100+lightintensity;

   Pp[11] = lightintensity+7;
   PP[11] = lightintensity+8;
   ON[11] = (lightintensity+10)/10;
   IP[11] = 100+lightintensity;

   Pp[14] = lightintensity+7;
   PP[14] = lightintensity+8;
   ON[15] = (lightintensity+10)/10;
   IP[14] = 100+lightintensity;
  
   
     
    Serial.println();

    
    Serial.println();
   mycthulhu.UpdateStimuli(trodes, PP, Pp, IN, IP, ON); //update waveform parameters
   mycthulhu.Stimulate(); //create the stimulation pulsetrain on the electrodes
    int delay_force = map(lightV, 0, 5000, 500, 50);
    delay(delay_force);
}
}
