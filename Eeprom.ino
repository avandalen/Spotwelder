const unsigned maxWrites = 100; 
const unsigned initValue = 12342; // take another value for new initialization

void Eeprom::init()
{ setMemPool(0, EEPROMSizeATmega328);
  setMaxAllowedWrites(maxWrites); 
  storedInitValue = getAddress(sizeof(unsigned));
  preweld_ms = getAddress(sizeof(unsigned));
  pause_ms = getAddress(sizeof(unsigned));
  weld_ms = getAddress(sizeof(unsigned)); 
  orientation = getAddress(sizeof(unsigned)); 
  if(!initialized()) write(); // fill an empty EEPROM
}

void Eeprom::read()
{ menuItems[0].upDownVal.value = readInt(preweld_ms);
  menuItems[1].upDownVal.value = readInt(pause_ms);
  menuItems[2].upDownVal.value = readInt(weld_ms);
}

void Eeprom::write()
{ writeInt(storedInitValue, initValue); // todo with update()?
  writeInt(preweld_ms, menuItems[0].upDownVal.value);
  writeInt(pause_ms, menuItems[1].upDownVal.value);
  writeInt(weld_ms, menuItems[2].upDownVal.value);
  writeInt(orientation, 0);
}

bool Eeprom::initialized()
{ return readInt(storedInitValue) == initValue;
}

