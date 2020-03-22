#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>

#define DISPLAY_COLUMNS 128
#define DISPLAY_ROWS 8

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
	byte getTabIndex() const;
	 
public:
	Page(PageManager* manager);
	virtual ~Page();

	virtual void init(); // Called when page gets active page.
	virtual void left();
	virtual void right();
	virtual void update();
	virtual void confirm();

	virtual bool needsRender();
	virtual void initRender(SSD1306Ascii* display) = 0;
	virtual void render(SSD1306Ascii* display);
};