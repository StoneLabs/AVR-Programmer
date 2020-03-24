#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>

#define DISPLAY_COLUMNS 128
#define DISPLAY_ROWS 8
#define DISPLAY_COLUMNS_FONT 5

// Forward decleration
class PageManager;

class Page
{
protected:
	PageManager* pageManager;
	 
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