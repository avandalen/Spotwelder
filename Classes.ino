#include "Classes.h"
#include <Arduino.h>

void Menu::drawColorTextLine(int line, int left, String str, uint16_t color=COLOR_WHITE, uint16_t backgroundColor) 
{ tft.fillRectangle(left, 20*line, 175, 20*line+19, backgroundColor); // line <= 10
  tft.setBackgroundColor(backgroundColor);
  tft.drawText(left, 20*line+2, str, color);  
}

void Menu::control() 
{ if(!editValue)
  { if(upButton.pushed()) 
    { menu.displayValue(upDownItemNr, menuItems[upDownItemNr].upDownVal, 0, editValue); // un-focus old item
      menu.displayValue(upDownItemNr, menuItems[upDownItemNr.down()].upDownVal, 1, editValue); // focus
      return;
    } 
    if(downButton.pushed()) 
    { menu.displayValue(upDownItemNr, menuItems[upDownItemNr].upDownVal, 0, editValue); // un-focus old item
      menu.displayValue(upDownItemNr, menuItems[upDownItemNr.up()].upDownVal, 1, editValue); // focus
      return;
    } 
    if(selectButton.pushed())
    { menu.displayValue(upDownItemNr, menuItems[upDownItemNr].upDownVal, 1, editValue=1); // add backgound
      return;
    }
  }     
  if(editValue)
  { if(upButton.pushed()) 
    { menu.displayValue(upDownItemNr, menuItems[upDownItemNr].upDownVal.up(), 1, editValue); 
      return;     
    }
    if(downButton.pushed()) 
    { menu.displayValue(upDownItemNr, menuItems[upDownItemNr].upDownVal.down(), 1, editValue); 
      return;    
    } 
    if(selectButton.pushed()) 
    { menu.displayValue(upDownItemNr, menuItems[upDownItemNr].upDownVal, 1, editValue=0); // delete backgound
      eeprom.write();
      return;
    }      
  }
}

void Menu::displayAll() 
{ if(!continuously)
  { for(int i=0; i<3; i++)
    { upDownItemNr.value=i;
      displayName(upDownItemNr, menuItems[upDownItemNr].name); 
      menu.displayValue(upDownItemNr, menuItems[upDownItemNr].upDownVal, 0, 0);
     } 
    upDownItemNr.value=0;
    menu.displayValue(upDownItemNr, menuItems[upDownItemNr].upDownVal, 1, 0); // item 0 has focus
    displayDot(0); 
    drawColorTextLine(10, 0, "-   +   sel   weld", COLOR_YELLOW, COLOR_BLUEVIOLET);
  }
  else 
  { drawColorTextLine(4, 0, "  Continuously", COLOR_WHITE, COLOR_RED);
    drawColorTextLine(5, 0, "        mode", COLOR_WHITE, COLOR_RED);
    drawColorTextLine(6, 0, "    Take care!", COLOR_WHITE, COLOR_RED);
  }
}

void Menu::displayDot(bool on)
{ tft.fillCircle(87, 170, 12, on? COLOR_WHITE : COLOR_DARKBLUE); 
}

void Menu::displayName(int upDownItemNr, String &name) 
{ drawColorTextLine(2*upDownItemNr, txtLeft, name, TXT_COLOR);
}

void Menu::displayValue(int upDownItemNr, int value, bool focus, bool background)
{ menu.drawColorTextLine(2*upDownItemNr+1, txtLeft, String("      ")); // clear line
  menu.drawColorTextLine(2*upDownItemNr+1, 0, focus? ">" : " ", TXT_COLOR);
  menu.drawColorTextLine(2*upDownItemNr+1, txtLeft, String(value), background? COLOR_BLACK : TXT_COLOR, background? COLOR_CYAN : COLOR_BLACK);
}

// ---------------------------------------------------------------------------

UpDownValue::UpDownValue(int value, int step, int minValue, int maxValue):
value(value), step(step), minValue(minValue), maxValue(maxValue)
{
}
int UpDownValue::up() 
{ value += step;       
  return value = min(max(value, minValue), maxValue);
}
int UpDownValue::down() 
{ value -= step;       
  return value = min(max(value, minValue), maxValue);
}

UpDownValue::operator int() // conversion operator, object returns value
{ return value; 
} 

// ---------------------------------------------------------------------------

MenuItem::MenuItem(String name, UpDownValue value):
name(name), upDownVal(value)
{  
}


