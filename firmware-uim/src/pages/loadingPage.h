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

class LoadingPage : public Page
{
private:
	unsigned long initMillis = 0;
	Page* targetPage;

	const char* message = "Loading... ";
	byte symbol = 0;
	byte symbolOffset = 0;

protected:
	unsigned long getInitMillis();

public:
	LoadingPage(PageManager* manager, Page* targetPage);

	void update() override;
	bool needsRender() override;
	virtual bool changePage() = 0; // Implemented by subclass

	void initRender(SSD1306Ascii* display) override;
	void render(SSD1306Ascii* display) override;
};