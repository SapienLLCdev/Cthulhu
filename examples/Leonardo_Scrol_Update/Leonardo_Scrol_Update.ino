#include <Cthulhu.h>
#include "Mouse.h"
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
//array to hold which electrodes should be on or off. In this example, one electrode is turned on.
int trodes[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
//pulse period for each electrode, in microseconds. Can be manipulated with Pp and IN to change the intensity of the sensation.
int PP[] = {20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20};
//length of positive pulse for each electrode, in microseconds. Can be manipulated with PP and IN to change the intensity of the sensation.
int Pp[] = {19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19};
//inner burst number (how many pulses in each inner burst). Can be manipulated with PP and Pp to change the intensity of the sensation.
int IN[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
//inner burst period. In microseconds. Can change quality, or 'feel' of sensation.
int IP[] = {150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150};
//Outer burst number. Can change quality, or 'feel' of sensation.
int ON[] = {5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
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
void setup() {
  mycthulhu.Begin();
  //Serial.begin(9600);
  Mouse.begin();
}
void loop() {
  scroll_state = 0;
  if (micros() - timemicros > scrolltimethresh)
  {
    last_touched = 0;
  }
  sample(); //made a function
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
      if (count >= 25)
      {
        rightclickState = 1;
        count = 0;
        break;
      }
      sample();
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
  if (slow == 1)
  {
    xDistance = xDistance / 3;
    yDistance = yDistance / 3;
  }

  if( rightclickState == 0 && leftclickState ==0){
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



void sample()
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
