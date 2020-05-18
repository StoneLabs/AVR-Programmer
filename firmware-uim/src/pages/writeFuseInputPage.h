#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "../tabPage.h"
#include "../pageManager.h"
#include "mainPage.h"
#include "writeFuseInitPage.h"

class WriteFuseInputPage : public TabPage
{
private:
	const char* back = "  Back";
	const char* ok = "  Confirm";
	
	byte sig1, sig2, sig3;
	Signature signature = Signature();
	bool signatureKnown = false;

	byte fuse;
	byte fuseValue;

public:
	WriteFuseInputPage(PageManager* manager, byte sig1, byte sig2, byte sig3, byte fuse, byte initValue);

	void confirm() override;
	void init() override;

	void initRender(SSD1306Ascii* display) override;
	void render(SSD1306Ascii* display) override;
};