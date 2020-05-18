#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../tabPage.h"
#include "../pageManager.h"
#include "writeFuseInputPage.h"
#include "mainPage.h"

class WriteFuseSelectPage : public TabPage
{
private:
	byte sig1, sig2, sig3;
	byte val_lowFuse, val_highFuse, val_extFuse, val_lockFuse, val_calibration;
	const char* back = "  Back";

public:
	WriteFuseSelectPage(PageManager* manager, byte sig1, byte sig2, byte sig3, byte lowFuse, byte highFuse, byte extFuse, byte lockFuse, byte calibration);
	void confirm() override;

	void initRender(SSD1306Ascii* display) override;
	void render(SSD1306Ascii* display) override;
};