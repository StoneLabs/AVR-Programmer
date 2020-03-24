#include "errorPage.h"

ErrorPage::ErrorPage(PageManager* manager, byte error)
	: Page ( manager )
{
	this->errorByte = error;
}

void ErrorPage::confirm()
{
	this->pageManager->changePage(new MainPage(this->pageManager));
}

void ErrorPage::initRender(SSD1306Ascii* display)
{
	display->print(F("Error: "));
	DisplayUtils::printHex(display, this->errorByte);
	
	display->setCursor(0, 3);
	switch (errorByte)
	{
	case error_unknownCommand:
		display->println(F("Internal error."));
		break;
	case error_programmingMode:
		display->println(F("Coudn't enter pro-"));
		display->println(F("gramming mode."));
		break;
	case error_openFile:
		display->println(F("Coudn't open file."));
		break;
	case error_bootloaderSupport:
		display->println(F("Bootloader setting"));
		display->println(F("not supported for this"));
		display->println(F("chip."));
		break;
	case error_hexInvalid:
		display->println(F("Hex file invalid."));
		display->println(F("Line without ':'"));
		break;
	case error_hexLineTooLong:
		display->println(F("Hex line too long."));
		break;
	case error_hexUnsupportedEntry:
		display->println(F("Hex contains unknown"));
		display->println(F("entry type."));
		break;
	case error_hexCheckSum:
		display->println(F("Hex file invalid."));
		display->println(F("Checksum error!"));
		break;
	case error_hexFlashBounds:
		display->println(F("Hex file invalid."));
		display->println(F("Too big for flash!"));
		break;
	case error_hexCharSymbol:
		display->println(F("Hex file invalid."));
		display->println(F("Invalid characters."));
		break;
	case error_fuseCheckMismatch:
		display->println(F("Fuse transfer failed."));
		display->println(F("Please try again!"));
		break;
	case error_fuseWithoutSignature:
		display->println(F("Unknown Signature!"));
		display->println(F("Try erasing the chip?"));
		break;
	case error_refusedByProgrammer:
		display->println(F("Fuse change refused!"));
		display->println(F("Security measures are"));
		display->println(F("in place to prevent"));
		display->println(F("destructive actions!"));
		break;
	default:
		display->println(F("Unknown error."));
		break;
	}

	// Display back button in bottom right
	const char* back = "> OK";
	display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
	display->print(back);
}
