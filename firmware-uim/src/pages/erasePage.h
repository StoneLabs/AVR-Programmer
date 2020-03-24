#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../page.h"
#include "../pageManager.h"
#include "mainPage.h"

class ErasePage : public Page
{
public:
	ErasePage(PageManager* manager);

	void confirm() override;
	void initRender(SSD1306Ascii* display) override;
};