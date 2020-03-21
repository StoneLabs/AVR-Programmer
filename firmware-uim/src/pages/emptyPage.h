#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../page.h"
#include "../pageManager.h"

class EmptyPage : public Page
{
public:
	EmptyPage(PageManager* manager);
	void render(SSD1306Ascii* display) override;
};