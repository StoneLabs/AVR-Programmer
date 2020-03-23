#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../page.h"
#include "../pageManager.h"
#include "../signatures.h"
#include "../displayUtils.h"
#include "mainInitPage.h"
#include "lockedDevicePage.h"

class ReadFusesPage : public Page
{
private:
	byte lowFuse, highFuse, extFuse, lockFuse, calibration;

public:
	ReadFusesPage(PageManager* manager, byte lowFuse, byte highFuse, byte extFuse, byte lockFuse, byte calibration);
	
	void confirm() override;
	void initRender(SSD1306Ascii* display) override;
};