#include <Cthulhu.h>
#include "Mouse.h"
#include "Keyboard.h"
#include <EEPROM.h>
#include <avr/wdt.h>
/*
  Cthulhu Leonardo cursor control example - Example for activating certain electrodes and sensing whether the tongue is in contact with
  each electrode, and using this to control a computor cursor cia arduino leonardo.
  Created by Joel Moritz Jr May 2019
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




//array to hold which electrodes should be on or off. In this example, one electrode is turned on.
int trodes[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//pulse period for each electrode, in microseconds. Can be manipulated with Pp and IN to change the intensity of the sensation.
int  PP[] = {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
//length of positive pulse for each electrode, in microseconds. Can be manipulated with PP and IN to change the intensity of the sensation.
int  Pp[] = {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9};
//inner burst number (how many pulses in each inner burst). Can be manipulated with PP and Pp to change the intensity of the sensation.
int  IN[] = {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
//inner burst period. In microseconds. Can change quality, or 'feel' of sensation.
int  IP[] = {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150};
//Outer burst number. Can change quality, or 'feel' of sensation.
int  ON[] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
//Requirements:
//Pp must be less than PP. CheckWaveform Error 1.
//(PP*IN) must be less than IP. CheckWaveform Error 2.
//IP*IN must be less than 2000 microseconds. CheckWaveform Error 3.
#define HighPeriod 1
#define LowPeriod 16000 //note,. this has greatest effect on percieved intensity 
#define IntensityDelay 100 //adjust this to adjust intensity of tactile buttons. 
#define InnerBurstPeriodDelay 1000
#define MidLeftThresh 200
#define MidRightThresh 200
#define RightThresh 150
#define LeftThresh 150
#define TipThresh 310
#define BackThresh 215
uint8_t buf[8] = {
  0
}; /* Keyboard report buffer */
Cthulhu mycthulhu; //creating and instance of
int tip;
int back;
int left;
int right;
int SupressSpeed = 0;
int range = 1; // output range of X or Y movement; affects movement speed
int responseDelay = 1; // response delay of the mouse, in ms
int upState;
int downState;
int rightState;
int leftState;
int leftclickState;
int rightclickState;
int slow;
int acceleration = 1;
int maxspeed = 10;
int count = 0;
int last_touched = 0; // last touched: up = 1, right = 2, down = 3, left = 4; nothing touch within last 1/10th second = 0
int scroll_state;
unsigned long timemicros;
unsigned long scrolltimethresh = 100000; // two tenth of second

int mode;


// a demonstration of geometric patterns (lines, sweeps, pulsing X's
void demonstration()
{

  //lines top to bottom 2x
for (int m = 0; m<2 ; m++)
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



  //lines left to right 2x
for (int m = 0; m<2 ; m++)
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

  //Pulsing X 2x
  if(mode ==1)
  {
//on = 
//  {
//    {0,0,1,0},
//    {0,1,1,0},
//    {0,0,1,0},
//    {0,0,1,0},
//    {0,1,1,1}
//  };
on[0][2] = 1;on[1][1] = 1;on[1][2] = 1;on[2][2] = 1;on[3][2] = 1;on[4][1] = 1;on[4][2] = 1;on[4][3] = 1;
  }
  if(mode ==2)
  {
//    on[5][4] = 
//  {
//    {0,1,1,0},
//    {1,0,0,1},
//    {0,0,1,0},
//    {0,1,0,0},
//    {1,1,1,1}
//  };
on[0][1] = 1;on[0][2] = 1;
on[1][0] = 1;on[1][3] = 1;
on[2][2] = 1;
on[3][1] = 1;
on[4][0] = 1;on[4][1] = 1;on[4][2] = 1;on[4][3] = 1;
  }
    if(mode ==3)
  {
//    on[5][4] = 
//  {
//    {1,1,1,0},
//    {0,0,0,1},
//    {0,1,1,1},
//    {0,0,0,1},
//    {1,1,1,0}
//  };
on[0][0] = 1;on[0][1] = 1;on[0][2] = 1;
on[1][3] = 1;
on[2][1] = 1;on[2][2] = 1;on[2][3] = 1;
on[3][3] = 1;
on[4][0] = 1;on[4][1] = 1;on[4][2] = 1;
  }
      if(mode ==4)
  {
//    on[5][4] = 
//  {
//    {1,0,0,1},
//    {1,0,0,1},
//    {1,1,1,1},
//    {0,0,0,1},
//    {0,0,0,1}
//  };
on[0][0] = 1;on[0][3] = 1;
on[1][0] = 1;on[1][3] = 1;
on[2][0] = 1;on[2][1] = 1;on[2][2] = 1;on[2][3] = 1;
on[3][3] = 1;
on[4][3] = 1;
  }
        if(mode ==5)
  {
//    on[5][4] = 
//  {
//    { ,1,1, },
//    {1,0,0,0},
//    {1,1,1,0},
//    {0,0,0,1},
//    {1,1,1,0}
//  };
on[0][1] = 1;on[0][2] = 1;
on[1][0] = 1;//on[1][3] = 1;
on[2][0] = 1;on[2][1] = 1;on[2][2] = 1;//on[2][3] = 1;
on[3][3] = 1;
on[4][0] = 1;on[4][1] = 1;on[4][2] = 1;
  }
    updatepattern();
for (int m = 0; m<2 ; m++)
{Serial.println("Pulsing 'X' with varying intensity.");
for (int i = 1;i<50;i++)
{
    for (int x = 0;x<9;x++)
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
    for (int x = 0;x<9;x++)
{
  Pp[x] = 9;
}
  on[1][0] = 0;on[2][1] = 0;on[3][2] = 0;on[4][3] = 0;
  on[4][0] = 0;on[3][1] = 0;on[2][2] = 0;on[1][3] = 0;
  updatepattern();
  mycthulhu.UpdateStimuli(array, PP, Pp, IN, IP, ON);
  

}

void reboot() {
  wdt_disable();
  wdt_enable(WDTO_15MS);
  while (1) {}
}

void sample2()
{
  for (int i = 0; i < 3; i++)
  {
    digitalWrite(A0, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, HIGH);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, HIGH);
    digitalWrite(A5, HIGH);
    digitalWrite(A7, HIGH);
    digitalWrite(A9, HIGH);
    //write pin 3-12 pulses
    delayMicroseconds(HighPeriod); // postive pulse
    pinMode(A0, INPUT);
    pinMode(A1, INPUT);
    pinMode(A2, INPUT);
    pinMode(A3, INPUT);
    pinMode(A4, INPUT);
    pinMode(A5, INPUT);
    pinMode(A7, INPUT);
    pinMode(A9, INPUT);
    tip = (analogRead(A1) + analogRead(A2)) / 2;
    back = (analogRead(A0) + analogRead(A3)) / 2;
    right = analogRead(A4);
    left = analogRead(A5);
    SupressSpeed = (analogRead(A7) + analogRead(A9)) / 2;
    delayMicroseconds(IntensityDelay);
    pinMode(A0, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);
    pinMode(A5, OUTPUT);
    pinMode(A7, OUTPUT);
    pinMode(A9, OUTPUT);
    digitalWrite(A0, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
    digitalWrite(A5, LOW);
    digitalWrite(A7, LOW);
    digitalWrite(A9, LOW);
    delayMicroseconds(LowPeriod); // negative pulse
  }
}

void setup() {
  Mouse.end();
Serial.begin(9600);
delay(100);
  mode = EEPROM.read(0);
  delay(1000);
    Serial.print("mode is ");
  Serial.println(mode);
  if (mode != 1 && mode != 2 && mode != 3 && mode != 4 && mode != 5)
  {
    mode = 1;
    
  }
  mycthulhu.Begin();
  demonstration();
  if(mode == 3)
  {
    Keyboard.begin();
  }
  if(mode == 4 || mode == 5)
  {
    //do not start mouse or keyboard
    if(mode == 5)
    {
      Serial1.begin(9600);
    }
  }
  else{
  Mouse.begin();
  }
}
void loop() {
  scroll_state = 0;
  if (micros() - timemicros > scrolltimethresh)
  {
    last_touched = 0;
  }
  if(mode == 1)
  {
      sample(); //made a function
  }
  if(mode == 2)
  {
  sample2();
  }
    if(mode == 3)
  {
  sample();
  }
      if(mode == 4)
  {
  sample();
  }
        if(mode == 5)
  {
  sample();
  }

  delayMicroseconds(InnerBurstPeriodDelay);

    if (tip <= TipThresh && back <= BackThresh && left <= LeftThresh && right <= RightThresh)
  {
    leftclickState = 0;
    rightclickState = 0;
  }
  if (tip > TipThresh && back > BackThresh && left > LeftThresh && right > RightThresh) //if held, made this stay in this loop and not execute more actions
  {
    while (tip > TipThresh && back > BackThresh && left > LeftThresh && right > RightThresh)
    {
      count = count + 1;
        if(mode == 1 || mode == 3 || mode == 4 || mode == 5)
  {
      sample(); //made a function
  }
  if(mode == 2)
  {
  sample2();
  }
    }
          if (count >= 25 && count < 250)
      {
        rightclickState = 1;
        count = 0;
        //break;
      }
           if (count >= 250)
      {
        count = 0;
            if(mode == 1)
    {
      mode = 2;
    }
    else
    {
    if(mode == 2 )
    {
      mode = 3;
    }
    else{
      if(mode ==3)
      {
        mode =4;
      }
          else{
      if(mode ==4)
      {
        mode =5;
      }
      else{
        if(mode ==5)
        {
          mode = 1;
        }
      }
    }
    }
    }
  EEPROM.write(0,mode);
  delay(100);
    mode = EEPROM.read(0);
    delay(100);
  Serial.print("mode is ");
  Serial.println(mode);
        reboot();
        //break;
      }
    
    if(rightclickState == 0)
    {
      count = 0;
      leftclickState = 1;
//      mycthulhu.UpdateStimuli(trodes, PP, Pp, IN, IP, ON); //update waveform parameters // light up all electrodes
//      mycthulhu.Stimulate(); //create the stimulation pulsetrain on the electrodes
    }
  }
  else
  {
    if (tip > TipThresh)
    {
   
      if (upState != 0)
      {
        upState = upState + acceleration;
        if (upState >= maxspeed)
        {
          upState = maxspeed;
        }
      }
      else {
        upState = 1;
      }
    }
    else
    {
      upState = 0;
    }
    if (back > BackThresh)
    {

      if (downState != 0)
      {
        downState = downState + acceleration;
        if (downState >= maxspeed)
        {
          downState = maxspeed;
        }
      }
      else {
        downState = 1;
      }
    }
    else
    {
      downState = 0;
    }
    if (left > LeftThresh)
    {
//      last_touched = 4;
//      timemicros = micros();
      if (leftState != 0)
      {
        leftState = leftState + acceleration;
        if (leftState >= maxspeed)
        {
          leftState = maxspeed;
        }
      }
      else {
        leftState = 1;
      }
    }
    else
    {
      leftState = 0;
    }
    if (right > RightThresh)
    {
//      last_touched = 2;
//      timemicros = micros();
      if (rightState != 0)
      {
        rightState = rightState + acceleration;
        if (rightState >= maxspeed)
        {
          rightState = maxspeed;
        }
      }
      else {
        rightState = 1;
      }
    }
    else
    {
      rightState = 0;
    }
    if (SupressSpeed > MidRightThresh)///////////////////////////////////
    {
      slow = 1;
    }
    else
    {
      slow = 0;
    }
  }

  int xDistance = (leftState - rightState) * range;
  int yDistance = (upState - downState) * range;
  
  if(mode == 2)
  {
  if (slow == 1)
  {
    xDistance = xDistance / 3;
    yDistance = yDistance / 3;
  }
  }
  
  if( rightclickState == 0 && leftclickState ==0)
  {
  if(yDistance > 0)
  {
    if(last_touched == 0)
    {
      last_touched = 3;
    }
        if (last_touched == 1)
      {
        scroll_state = -3;
      }
      
      timemicros = micros();
}
  if(yDistance < 0)
  {
    if( last_touched == 0)
    {
            last_touched = 1;
    }
   if (last_touched == 3)
      {
        scroll_state = 3;
      }

      timemicros = micros();
  }
  }
      if(mode != 3 && mode !=4 && mode != 5)
      {
  // if X or Y is non-zero, move:
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, scroll_state);
  }
  // if the mouse button is pressed:
  if (leftclickState == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }
  // if the mouse button is pressed:
  if (rightclickState == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.press(MOUSE_RIGHT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_RIGHT)) {
      Mouse.release(MOUSE_RIGHT);
    }
  }
  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
}
      if(mode == 3)
      {
  // if X or Y is non-zero, move:
  if ((xDistance > 0) ) {
    Keyboard.press('d');
  }
  else(Keyboard.release('d'));
    if ((xDistance < 0) ) {
    Keyboard.press('a');
  }
  else(Keyboard.release('a'));
    if ((yDistance > 0) ) {
    Keyboard.press('w');
  }
  else(Keyboard.release('w'));
    if ((yDistance < 0) ) {
    Keyboard.press('s');
  }
  else(Keyboard.release('s'));

  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
}
      if(mode == 4)
      {
  // if X or Y is non-zero, move:
  if ((xDistance > 0) ) {
    Serial.print('d');
  }

    if ((xDistance < 0) ) {
    Serial.print('a');
  }

    if ((yDistance > 0) ) {
    Serial.print('w');
  }

    if ((yDistance < 0) ) {
    Serial.print('s');
  }



  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
}

      if(mode == 5)
      {
//  // if X or Y is non-zero, move:
//  if( xDistance != 0 || yDistance != 0)
//  {
//      Serial1.print('0');Serial1.print(',');Serial1.print('0');Serial1.print(',');Serial1.print('0');Serial1.print(',');Serial1.print('0');Serial.print(',');
//  if ((xDistance > 0) ) {
//    Serial1.print('1');Serial1.print(',');
//  }
//
//    if ((xDistance < 0) ) {
//    Serial1.print('-');Serial1.print('1');Serial1.print(',');
//  }
//  
//  if(xDistance == 0){
//    Serial1.print('0');Serial1.println(',');
//  }
//
//    if ((yDistance > 0) ) {
//    Serial1.print('1');
//  }
//
//    if ((yDistance < 0) ) {
//    Serial1.print('-');Serial1.println('1');
//  }
//    if(yDistance == 0)
//  {
//    Serial1.println('0');
//  }
////Serial.println();
//  }
int grip = 50;

if (leftclickState == HIGH)
{
  grip = 255;
}
else
{
  grip = -255;
}
  
//if( xDistance == 0 && yDistance ==0)
//{
//  Serial1.print('0');Serial1.print(',');Serial1.print('0');Serial1.print(',');Serial1.print('0');Serial1.print(',');Serial1.print('0');Serial1.print(',');Serial1.print('0');Serial1.print(',');Serial1.println('0');
//}
//else{
  Serial1.print(grip);Serial1.print(',');Serial1.print('0');Serial1.print(',');Serial1.print('0');Serial1.print(',');Serial1.print(yDistance);Serial1.print(',');Serial1.print(xDistance);Serial1.print(',');Serial1.println(scroll_state);
//}


  // a delay so the mouse doesn't move too fast:
  delay(100);
}

}



void sample()
{
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
    tip = (analogRead(A1) + analogRead(A2))/2;
        back = (analogRead(A0) + analogRead(A3))/2;
         right = analogRead(A4);
           left = analogRead(A5);
           delayMicroseconds(IntensityDelay);
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
  }
