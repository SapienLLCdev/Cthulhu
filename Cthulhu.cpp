/*
  Cthulhu.h - Library for stimulating the tongue using electrotactile stimulation.
  Created by Joel Moritz Jr Jan 2019
  Released into the public domain.
*/


#include "Arduino.h"
#include "Cthulhu.h"




int Cthulhu::Begin()
{
  _channels = UNOSHIELD_CHANNELS;
 _refreshrate = UNOSHIELD_REFRESHRATE;
  _ICP = _refreshrate/_channels;
for(int i=0;i<18;i++) 
  {
    pinMode(_pins[i],OUTPUT); 
  }
return 0;
}

int Cthulhu::Begin_2uniformdelay()
{
  _channels = UNOSHIELD_CHANNELS;
 _refreshrate = UNOSHIELD_REFRESHRATE;
  _ICP = _refreshrate/_channels;
for(int i=0;i<18;i++) 
  {
    pinMode(_pins[i],OUTPUT); 
  }
return 0;
}


int Cthulhu::Stimulate()
{
 for (int k = 0; k <18; k++) { 
    if (_electrode[k] > 0) { //if a particular electrode is set to 'active = 1' stimulate the electrode with the appropraite parameters, otherwise, just turn the pin low


      _RCP = ((_ICP*1000)-(_OBN[k]*((_PP[k]*_IBN[k])+_IBP[k]))); // remaining channel period
      // this calculates the amount of time to pause
      // after OBN number of pulses have been made, in order to fill the 
      // whole channel period (which is necessary for consistent sensations)

  _Pminus = _PP[k] - _Pplus[k];

      // The following chunk of code creates IBN pulses in an inner burst, 
      //and OBN numbers of inner bursts within the outer burst
      for (int j = 0; j < _OBN[k]; j++) { // do the following OBN times and count,  increment by one each time
        for (int i = 0; i < _IBN[k]; i++) { // creat a positive and negative pulse IBN times, count, and increment by one each time
          digitalWrite(_pins[k], HIGH);                                                                                                  //write pin 3-12 pulses
          delayMicroseconds(_Pplus[k]); // postive pulse of length Pplus
          digitalWrite(_pins[k], LOW);
          delayMicroseconds(_Pminus); // negative pulse of length Pminus
        }
        int i = 0; // after three pulses reset IBN counter
        delayMicroseconds(_IBP[k]); // and pause for IBP microseconds
      }
      int j = 0; // after OBN groups of pulses, reset the OBN counter
      delayMicroseconds(_RCP); // pause for the remaining time left in the the channel period
    }
    else 
    {
      digitalWrite(_pins[k], LOW);
      delay(_ICP);//else make that pin[3-12] low
    }      
  }
}



int Cthulhu::Stimulate_2uniformdelay()
{
 for (int k = 0; k <18; k++) { 
    if (_electrode[k] > 0) { //if a particular electrode is set to 'active = 1' stimulate the electrode with the appropraite parameters, otherwise, just turn the pin low


      //_RCP = ((_ICP*1000)-(_OBN[k]*((_PP[k]*_IBN[k])+_IBP[k]))); // remaining channel period
      // this calculates the amount of time to pause
      // after OBN number of pulses have been made, in order to fill the 
      // whole channel period (which is necessary for consistent sensations)

  _Pminus = _PP[k] - _Pplus[k];

      // The following chunk of code creates IBN pulses in an inner burst, 
      //and OBN numbers of inner bursts within the outer burst
      for (int j = 0; j < _OBN[k]; j++) { // do the following OBN times and count,  increment by one each time
        for (int i = 0; i < _IBN[k]; i++) { // creat a positive and negative pulse IBN times, count, and increment by one each time
          digitalWrite(_pins[k], HIGH);                                                                                                  //write pin 3-12 pulses
          delayMicroseconds(_Pplus[k]); // postive pulse of length Pplus
          digitalWrite(_pins[k], LOW);
          delayMicroseconds(_Pminus); // negative pulse of length Pminus
        }
        int i = 0; // after three pulses reset IBN counter
        delayMicroseconds(_IBP[k]); // and pause for IBP microseconds
      }
      int j = 0; // after OBN groups of pulses, reset the OBN counter
      //delayMicroseconds(_RCP); // pause for the remaining time left in the the channel period
    }
    else 
    {
      digitalWrite(_pins[k], LOW);
      //delay(_ICP);//else make that pin[3-12] low
    }      
  }
}



int Cthulhu::StopStimulus()
{
  for (int k = 0; k <18; k++) 
  { 
  digitalWrite(_pins[k], LOW);
  }
  return 0;
}

int Cthulhu::CheckWaveform(int electrode[], int PP[], int Pplus[], int IBN[], int IBP[], int OBN[])
{

int error = 0;

for (int i = 0; i<18; i++)
{
if (Pplus[i] >= PP[i])
{
error = 1; // a value of '1' would indicate that Rule 1 is violated
} 
else if (PP[i]*IBN[i] >= IBP[i])
{
error = 2; // a value of '2' would indicate that Rule 2 is violated
} 
else if (IBP[i]*OBN[i] >= _ICP*1000)
{
error = 3; // a value of '3' would indicate that Rule 3 is violated
} 
}
return error;
}


int Cthulhu::CheckWaveform_2uniformdelay(int electrode[], int PP[], int Pplus[], int IBN[], int IBP[], int OBN[])
{

int error = 0;

for (int i = 0; i<18; i++)
{
if (Pplus[i] >= PP[i])
{
error = 1; // a value of '1' would indicate that Rule 1 is violated
} 
else if (PP[i]*IBN[i] >= IBP[i])
{
error = 2; // a value of '2' would indicate that Rule 2 is violated
} 
// else if (IBP[i]*OBN[i] >= _ICP*1000)
// {
// error = 3; // a value of '3' would indicate that Rule 3 is violated
// } 
}
return error;
}



int Cthulhu::UpdateStimuli(int electrode[], int PP[], int Pplus[], int IBN[], int IBP[], int OBN[])
{


  for (int i = 0; i<18; i++)
  {
      _electrode[i] = electrode[i];
      _PP[i] = PP[i];
      _Pplus[i] = Pplus[i];
      _IBN[i] = IBN[i];
      _IBP[i] = IBP[i];
      _OBN[i] = OBN[i];
  }
  return 0;
}

