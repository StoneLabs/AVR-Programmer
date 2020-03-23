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

class SignaturePage : public Page
{
private:
	byte b1, b2, b3;
	Signature signature = Signature();
	bool signatureKnown = false;

public:
	SignaturePage(PageManager* manager, byte s1, byte s2, byte s3);

	void init() override;

	void confirm() override;
	void initRender(SSD1306Ascii* display) override;
};