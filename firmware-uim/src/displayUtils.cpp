#include "displayUtils.h"

void DisplayUtils::printHexDigit(SSD1306Ascii* display, byte data)
{
    display->print("0123456789ABCDEF"[data & 0xF]);
}

void DisplayUtils::printBinDigit(SSD1306Ascii* display, byte data)
{
    display->print("01"[data & 0b1]);
}

void DisplayUtils::printHex(SSD1306Ascii* display, byte data)
{
    printHexDigit(display, (data & 0xF0) >> 4);
    printHexDigit(display, data);
}

void DisplayUtils::printBin(SSD1306Ascii* display, byte data)
{
    printBinDigit(display, (data & bit(7)) >> 7);
    printBinDigit(display, (data & bit(6)) >> 6);
    printBinDigit(display, (data & bit(5)) >> 5);
    printBinDigit(display, (data & bit(4)) >> 4);
    printBinDigit(display, (data & bit(3)) >> 3);
    printBinDigit(display, (data & bit(2)) >> 2);
    printBinDigit(display, (data & bit(1)) >> 1);
    printBinDigit(display, (data & bit(0)) >> 0);
}
