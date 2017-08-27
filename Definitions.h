#ifndef _Definitions_H_
#define _Definitions_H_

const byte BCDswitch0pin = 8;
const byte BCDswitch1pin = 7;
const byte BCDswitch2pin = 6;
const byte BCDswitch3pin = 5;
const byte weldPin = 2;
const byte weldButtonPin = 4; 
const byte upButtonPin = 7; 
const byte downButtonPin = 8; 
const byte selectButtonPin = 6; 
const byte ledPin = 12;
const byte zeroCrossPin = 3; 
const byte tftJumperOutPin = A5;
const byte tftJumperInPin = A4;

const byte TFT_RSTpin = 9;   
const byte TFT_RSpin = 10;  
const byte TFT_CSpin = 5; 
//const byte TFT_CLKpin = 13; // for SW SDI, doesn't work
//const byte TFT_SDIpin = 11; // for SW SDI, doesn't work

const int step_ms = 50;
const int sinusMax_us = 4583;

#define TXT_COLOR COLOR_YELLOW

#endif
