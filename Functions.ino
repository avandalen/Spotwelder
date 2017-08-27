void weldControlNoTFT()
{ if(continuously && BCDswitch()==0) weld(weldButton.on()); // continuous welding
  else
  if(weldButton.pushed()) weldCyclus(BCDswitch() * step_ms); 
}

void weldControlTFT()
{ //if(continuously && BCDswitch()==0) weld(weldButton.on()); 
  if(continuously) weld(weldButton.on()); 
  else
  if(weldButton.pushed()) weldCyclus(menuItems[2].upDownVal); 
}
  
void weldCyclus(int weldTime_ms)
{ if(!sinMaxDisabled) sinusMax();
  if(TFTused) menu.displayDot(1); // just once per weld cyclus
  pulseWeld(menuItems[0].upDownVal);
  delay(menuItems[1].upDownVal);
  if(!sinMaxDisabled) sinusMax();
  pulseWeld(weldTime_ms);
  if(TFTused) menu.displayDot(0); // just once per weld cyclus
}

int BCDswitch()
{ int bcd;
  bitWrite(bcd, 0, !digitalRead(BCDswitch0pin));
  bitWrite(bcd, 1, !digitalRead(BCDswitch1pin));
  bitWrite(bcd, 2, !digitalRead(BCDswitch2pin));
  bitWrite(bcd, 3, !digitalRead(BCDswitch3pin));
  return bcd;
}

void pulseWeld(int ms)
{ weld(1);
  delay(ms); 
  weld(0);
  if(printValuesToSerial) Serial << ms << endl;  
}

void weld(bool b) 
{ digitalWrite(weldPin, b);
  digitalWrite(ledPin, !b);
}

void sinusMax()
{ while(digitalRead(zeroCrossPin));
  while(!digitalRead(zeroCrossPin));
  delayMicroseconds(sinusMax_us); // to prevent inrush current, turn-on at the sinus max 
}

void blinkLed(int n)
{ pinMode(ledPin, OUTPUT); 
  for(byte i=0; i<n; i++)
  { digitalWrite(ledPin, HIGH);   
    delay(200);                 
    digitalWrite(ledPin, LOW);   
    delay(200);
  }
}

void setpinModes()
{ pinMode(BCDswitch0pin, INPUT_PULLUP);
  pinMode(BCDswitch1pin, INPUT_PULLUP);
  pinMode(BCDswitch2pin, INPUT_PULLUP);
  pinMode(BCDswitch3pin, INPUT_PULLUP); 
  pinMode(weldButtonPin, INPUT_PULLUP);   
  pinMode(weldPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(zeroCrossPin, INPUT);
}

void pollAll()
{ weldButton.poll();
  upButton.poll();
  downButton.poll();
  selectButton.poll();
}

void selectContinuously()
{ const unsigned long switchStable_ms = 200; // min = 50
  const unsigned long weldButtonPressTime = 500; // push weldButton during 500ms at power up
  unsigned long start_ms = millis();
  pollAll();
  delay(switchStable_ms);
  int bcdswitch = BCDswitch();  
  
  while(weldButton.on())
  { pollAll();     
    if(!weldButton.on()) break;
  }
  if(millis()-start_ms > weldButtonPressTime) continuously = 1;
  if(!TFTused) continuously &= bcdswitch==0; // bcdswitch has to be at position 0 too
}

void TFTinit()
{ tft.begin();
  tft.setOrientation(eeprom.readInt(orientation)); 
  tft.setFont(Terminal12x16);
}

bool TFTusedJumper()  
{ pinMode(tftJumperOutPin, OUTPUT);
  pinMode(tftJumperInPin, INPUT_PULLUP); // default 1
  digitalWrite(tftJumperOutPin, 0);
  return !digitalRead(tftJumperInPin); // no jumper = 1 (compatible with old software)
}

void printValuesToSerial()
{  Serial << "\npreweld " << menuItems[0].upDownVal << "ms, pause " << menuItems[1].upDownVal << "ms, weldTime " 
   << menuItems[2].upDownVal << "ms, continuously " << continuously << endl;
}

void setOrientation()
{ pollAll(); // works without too
  if(upButton.on() && downButton.on()) 
  { if(eeprom.readInt(orientation)==0) eeprom.writeInt(orientation, 2); 
    else eeprom.writeInt(orientation, 0); 
  }
}


