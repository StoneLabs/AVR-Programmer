#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../pageManager.h"
#include "../page.h"
#include "mainPage.h"

class DelayPage : public Page
{
private:
	unsigned long initMillis = 0UL;
	unsigned long lastRender = 0UL;
	unsigned long delayMillis = 0UL;
	Page* targetPage;

	const char* message = "Loading... ";
	byte symbol = 0;
	byte symbolOffset = 0;

public:
	DelayPage(PageManager* manager, unsigned long timeout, Page* targetPage);

	void update() override;
	bool needsRender() override;

	void initRender(SSD1306Ascii* display) override;
	void render(SSD1306Ascii* display) override;
};