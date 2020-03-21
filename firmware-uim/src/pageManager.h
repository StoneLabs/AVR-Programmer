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

public:
	PageManager(SSD1306Ascii* display);
	~PageManager();

	void left();
	void right();
	void confirm();
	void updatePage();

	void render();
	void changePage(Page* page);
};
