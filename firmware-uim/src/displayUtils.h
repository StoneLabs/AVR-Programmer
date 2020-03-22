#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>

class DisplayUtils
{
private:
	static void printHexDigit(SSD1306Ascii* display, byte data);

public:
	static void printHex(SSD1306Ascii* display, byte data);
};

