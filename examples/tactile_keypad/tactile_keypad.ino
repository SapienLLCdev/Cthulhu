#include <Cthulhu.h>

/*
  Cthulhu Tactile Button Example - Example for activating certain electrodes and sensing whether the tongue is in contact with 
  each electrode.
  Created by Joel Moritz Jr Jan 2019
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


#define MOD_CONTROL_LEFT    (1<<0)
#define MOD_SHIFT_LEFT      (1<<1)
#define MOD_ALT_LEFT        (1<<2)
#define MOD_GUI_LEFT        (1<<3)
#define MOD_CONTROL_RIGHT   (1<<4)
#define MOD_SHIFT_RIGHT     (1<<5)
#define MOD_ALT_RIGHT       (1<<6)
#define MOD_GUI_RIGHT       (1<<7)

#define KEY_A       4
#define KEY_B       5
#define KEY_C       6
#define KEY_D       7
#define KEY_E       8
#define KEY_F       9
#define KEY_G       10
#define KEY_H       11
#define KEY_I       12
#define KEY_J       13
#define KEY_K       14
#define KEY_L       15
#define KEY_M       16
#define KEY_N       17
#define KEY_O       18
#define KEY_P       19
#define KEY_Q       20
#define KEY_R       21
#define KEY_S       22
#define KEY_T       23
#define KEY_U       24
#define KEY_V       25
#define KEY_W       26
#define KEY_X       27
#define KEY_Y       28
#define KEY_Z       29
#define KEY_1       30
#define KEY_2       31
#define KEY_3       32
#define KEY_4       33
#define KEY_5       34
#define KEY_6       35
#define KEY_7       36
#define KEY_8       37
#define KEY_9       38
#define KEY_0       39

#define KEY_ENTER   40
#define KEY_ESCAPE  41
#define KEY_BACKSPACE  42
#define KEY_TAB     43
#define KEY_SPACE   44
#define KEY_MINUS   45
#define KEY_EQUALS  46
#define KEY_LBRACKET 47
#define KEY_RBRACKET 48
#define KEY_BACKSLASH 49
#define KEY_NONUS_NUMBER 50
#define KEY_SEMICOLON 51
#define KEY_QUOTE   52
#define KEY_TILDE   53
#define KEY_COMMA   54
#define KEY_PERIOD  55
#define KEY_SLASH   56
#define KEY_CAPSLOCK 57

#define KEY_F1      58
#define KEY_F2      59
#define KEY_F3      60
#define KEY_F4      61
#define KEY_F5      62
#define KEY_F6      63
#define KEY_F7      64
#define KEY_F8      65
#define KEY_F9      66
#define KEY_F10     67
#define KEY_F11     68
#define KEY_F12     69

#define KEY_PRNTSCRN    70
#define KEY_SCROLLLOCK  71
#define KEY_PAUSE       72
#define KEY_INSERT      73
#define KEY_HOME        74
#define KEY_PAGEUP      75
#define KEY_DELETE      76
#define KEY_END         77
#define KEY_PAGEDOWN    78
#define KEY_RIGHT_ARROW 79
#define KEY_LEFT_ARROW  80
#define KEY_DOWN_ARROW  81
#define KEY_UP_ARROW    82

#define KEY_NUM_LOCK    83

#define KEY_NUM_DIV     84
#define KEY_NUM_MUL     85
#define KEY_NUM_SUB     86
#define KEY_NUM_ADD     87

#define KEY_NUM_ENTER   88
#define KEY_NUM_1       89
#define KEY_NUM_2       90
#define KEY_NUM_3       91
#define KEY_NUM_4       92
#define KEY_NUM_5       93
#define KEY_NUM_6       94
#define KEY_NUM_7       95
#define KEY_NUM_8       96
#define KEY_NUM_9       97
#define KEY_NUM_0       98
#define KEY_NUM_DOT     99




#define HighPeriod 100
#define LowPeriod 100
#define IntensityDelay 10 //adjust this to adjust intensity of tactile buttons. 


#define RightThresh 550
#define LeftThresh 550
#define TipThresh  550
#define BackThresh 550

uint8_t buf[8] = { 
  0 };   /* Keyboard report buffer */




Cthulhu mycthulhu; //creating and instance of 

          int tip;
          int back;
          int left;
          int right;
          

void setup() {
  mycthulhu.Begin();
  Serial.begin(9600); 
}

void loop() {


//

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
         left = analogRead(A4);
           right = analogRead(A5);
           delay(IntensityDelay);
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
delay(1);

  sendStrokes();
}



void sendStrokes()
{

if (tip > TipThresh && back > BackThresh && left > LeftThresh && right > RightThresh)
{
    buf[2] = 0x2c;    // Random character
    Serial.write(buf, 8); // Send keypress
}
else{


if (tip > TipThresh)
{
    buf[2] = 0x1a;    // Random character
    Serial.write(buf, 8); // Send keypress
}
if (back > BackThresh)
{
    buf[2] = 0x16;    // Random character
    Serial.write(buf, 8); // Send keypress
}
if (left > LeftThresh)
{
    buf[2] = 0x04;    // Random character
    Serial.write(buf, 8); // Send keypress
}
if (right > RightThresh)
{
    buf[2] = 0x07;    // Random character
    Serial.write(buf, 8); // Send keypress
}
}
if (tip < TipThresh && back < BackThresh && left < LeftThresh && right < RightThresh)
{
  releaseKey();
}
  
}






void releaseKey() 
{
  buf[0] = 0;
  buf[2] = 0;
  Serial.write(buf, 8); // Release key  
}

