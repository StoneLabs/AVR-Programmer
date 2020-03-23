#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <SSD1306Ascii.h>
#include "page.h"

class TabPage : public Page
{
private:
	byte tabIndex = 0x00;
	const byte tabLength = 4; // 4 Entries
	
protected:
	byte getTabIndex() const;

public:
	TabPage(PageManager* manager, byte tabLength);

	virtual void left() override;
	virtual void right() override;
};