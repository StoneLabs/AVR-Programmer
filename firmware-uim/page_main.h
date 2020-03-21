#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>

class MainPage
{
private:
	byte tabIndex = 0x00;
	const byte tabLength = 4; // 4 Entries

private:
	void write_entry_line(SSD1306Ascii* display, byte index, const char* text);

public:
	MainPage();

	void left();
	void right();
	void confirm();

	void render(SSD1306Ascii *display);
};