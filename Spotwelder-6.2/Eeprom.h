class Eeprom: public EEPROMClassEx
{ 
public:
  void init();
  void read();
  void write();
  bool initialized();
  
  unsigned storedInitValue_addr, preweld_ms_addr, pause_ms_addr, weld_ms_addr; // EEPROM addresses
};
