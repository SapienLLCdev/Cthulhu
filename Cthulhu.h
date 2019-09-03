/*
  Cthulhu.h - Library for stimulating the tongue using electrotactile stimulation.
  Created by Joel Moritz Jr Jan 2019
  Released into the public domain.
*/


#include "Arduino.h"

#ifndef Cthulhu_h
#define Cthulhu_h


#define UNOSHIELD_CHANNELS 18
#define UNOSHIELD_REFRESHRATE 36



class Cthulhu
{
public:
  int Begin();
  int Begin_2uniformdelay();
  int Stimulate();
  int stimulate_2uniformdelay();

  int UpdateStimuli(int electrode[], int PP[], int Pplus[], int IBN[], int IBP[], int OBN[]);
  int StopStimulus();
  int CheckWaveform(int electrode[], int PP[], int Pplus[], int IBN[], int IBP[], int OBN[]);


private:


  int _electrode[UNOSHIELD_CHANNELS] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  int _PP[UNOSHIELD_CHANNELS]= {10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};
  int _Pplus[UNOSHIELD_CHANNELS]= {9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}; // this unit in microseconds
  int _IBN[UNOSHIELD_CHANNELS]= {3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3};
  int _IBP[UNOSHIELD_CHANNELS]= {150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150}; // this unit in microseconds
  int _OBN[UNOSHIELD_CHANNELS]= {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};

  int _channels;
  int _refreshrate;

  int _ICP;

  int _Pminus;
  float _RCP;

  int _PinMap[5][4] = 
  {
    {0, A1,A2,0},
    {11,8, 7, 4},
    {A4,9, 6,A5},
    {12,10,5, 3},
    {13,A0,A3,2}
  };
  int _ElectrodeMap[5][4] = 
  {
    {0, 0, 1, 0},
    {2, 3, 4, 5},
    {6, 7, 8, 9},
    {10,11,12,13},
    {14,15,16,17}
  };
  
  int _pins[UNOSHIELD_CHANNELS] = {A1,A2,11,8,7,4,A4,9,6,A5,12,10,5,3,13,A0,A3,2};


};

#endif


//IBN, PP, IBP, OBN
