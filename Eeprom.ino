const unsigned maxWrites = 100; 
const unsigned initValue = 12342; // take another value for new initialization

void Eeprom::init()
{ setMemPool(0, EEPROMSizeATmega328);
  setMaxAllowedWrites(maxWrites); 
  storedInitValue_addr = getAddress(sizeof(unsigned));
  preweld_ms_addr = getAddress(sizeof(unsigned));
  pause_ms_addr = getAddress(sizeof(unsigned));
  weld_ms_addr = getAddress(sizeof(unsigned)); 
  orientation_addr = getAddress(sizeof(unsigned)); 
  if(!initialized()) write(); // fill an empty EEPROM
}

void Eeprom::read()
{ menuItems[0].upDownVal.value = readInt(preweld_ms_addr);
  menuItems[1].upDownVal.value = readInt(pause_ms_addr);
  menuItems[2].upDownVal.value = readInt(weld_ms_addr);
  orientation = readInt(orientation_addr);// v6.2
}

void Eeprom::write()
{ writeInt(storedInitValue_addr, initValue); // todo with update()?
  writeInt(preweld_ms_addr, menuItems[0].upDownVal.value);
  writeInt(pause_ms_addr, menuItems[1].upDownVal.value);
  writeInt(weld_ms_addr, menuItems[2].upDownVal.value);
  writeInt(orientation_addr, orientation);// v6.2 
}

bool Eeprom::initialized()
{ return readInt(storedInitValue_addr) == initValue;
}

