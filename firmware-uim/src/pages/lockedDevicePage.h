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

class LockedDevicePage : public Page
{
private:
	byte b1, b2, b3;

public:
	LockedDevicePage(PageManager* manager, byte s1, byte s2, byte s3);

	void confirm() override;
	void initRender(SSD1306Ascii* display) override;
};