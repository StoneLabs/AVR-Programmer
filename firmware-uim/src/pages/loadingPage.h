#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../pageManager.h"
#include "../page.h"

class LoadingPage : public Page
{
private:
	unsigned long initMillis = 0;

	const char* message;
	byte symbol = 0;
	byte symbolOffset = 0;

	byte manualRow = 0;
	bool manualPos = false;

protected:
	unsigned long getInitMillis();

public:
	LoadingPage(PageManager* manager, const char* message);
	LoadingPage(PageManager* manager, const char* message, byte manualColumn, byte manuelRow);

	void update() override = 0;
	bool needsRender() override;

	void initRender(SSD1306Ascii* display) override;
	void render(SSD1306Ascii* display) override;
};