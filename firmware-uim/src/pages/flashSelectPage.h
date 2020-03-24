#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../page.h"
#include "../pageManager.h"
#include "mainInitPage.h"
#include "flashSelectInitPage.h"
#include "flashInitPage.h"

class FlashSelectPage : public TabPage
{
private:
	const char* back = "  Back";
	char* fileName;
	bool fileFound;

public:
	FlashSelectPage(PageManager* manager, char* fileName);
	~FlashSelectPage();

	void confirm() override;

	void initRender(SSD1306Ascii* display) override;
	void render(SSD1306Ascii* display) override;
};