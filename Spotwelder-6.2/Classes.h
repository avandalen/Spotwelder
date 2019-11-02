#ifndef _Classes_H_
#define _Classes_H_

#include <Arduino.h>

class UpDownValue
{ public:
    UpDownValue(int value, int step, int minValue, int maxValue);
    int up();
    int down();
    UpDownValue::operator int();
   
    int value, step, minValue, maxValue;
};

// ---------------------------------------------------------------------------

class MenuItem
{ public:
    MenuItem(String name, UpDownValue value);
        
    String name;
    UpDownValue upDownVal; 
};

// ---------------------------------------------------------------------------

class Menu
{ public:
    void control();
    void displayAll();
    void displayName(int itemNr, String &name);
    void displayValue(int itemNr, int value, bool focus, bool background);
    void displayDot(bool on);
    void drawColorTextLine(int line, int left, String str, uint16_t color=COLOR_WHITE, uint16_t backgroundColor=COLOR_BLACK);
  
  private:
    bool editValue=0;
    const int txtLeft = 17;
};

#endif
