#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>

// Forward decleration
class PageManager;

class Page
{
private:
	byte tabIndex = 0x00;
	const byte tabLength = 4; // 4 Entries

protected:
	PageManager* pageManager;

protected:
	void write_entry_line(SSD1306Ascii* display, byte index, const char* text);

public:
	Page(PageManager* manager);
	virtual ~Page();

	virtual void left();
	virtual void right();
	virtual void update();
	virtual void confirm();

	virtual bool needsRender();
	virtual void initRender(SSD1306Ascii* display);
	virtual void render(SSD1306Ascii* display) = 0;
};