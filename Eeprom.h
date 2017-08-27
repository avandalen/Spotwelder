class Eeprom: public EEPROMClassEx
{ 
public:
  void init();
  void read();
  void write();
  bool initialized();
  
  unsigned storedInitValue, preweld_ms, pause_ms, weld_ms; // EEPROM addresses
};
