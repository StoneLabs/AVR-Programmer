#include "displayUtils.h"

void DisplayUtils::printHexDigit(SSD1306Ascii* display, byte data)
{
    display->print("0123456789ABCDEF"[data & 0xF]);
}

void DisplayUtils::printHex(SSD1306Ascii* display, byte data)
{
    printHexDigit(display, (data & 0xF0) >> 4);
    printHexDigit(display, data);
}
