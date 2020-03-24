#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "pages/emptyPage.h"
#include "page.h"

class PageManager
{
private:
	Page* currentPage = nullptr;
	SSD1306Ascii* display;
	bool cancelInit = false;

public:
	PageManager(SSD1306Ascii* display);
	~PageManager();

	void left();
	void right();
	void confirm();
	void updatePage();
	void cancelPage();

	void render();

	// After calling changePage from a class
	// the calling function must return without
	// using any member variables as it will be 
	// deleted during the page change. Accessing
	// local variables after a call to changePage
	// will result in unpredictable behavior.
	void changePage(Page* page);
};
