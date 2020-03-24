#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../../I2CHelper.h"
#include "../pageManager.h"
#include "../displayUtils.h"
#include "loadingPage.h"
#include "mainPage.h"

class CriticalErrorPage : public Page
{
private:
	byte errorByte;

public:
	CriticalErrorPage(PageManager* manager, byte error);

	void initRender(SSD1306Ascii* display) override;
};