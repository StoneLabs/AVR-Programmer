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
	display->print("Error: ");
	DisplayUtils::printHex(display, this->errorByte);
	
	display->setCursor(0, 3);
	switch (errorByte)
	{
	case error_unknownCommand:
		display->println("Internal error.");
		break;
	case error_programmingMode:
		display->println("Coudn't enter pro-");
		display->println("gramming mode.");
		break;
	case error_openFile:
		display->println("Coudn't open file.");
		break;
	case error_bootloaderSupport:
		display->println("Bootloader setting");
		display->println("not supported for this");
		display->println("chip.");
		break;
	case error_hexInvalid:
		display->println("Hex file invalid.");
		display->println("Line without ':'");
		break;
	case error_hexLineTooLong:
		display->println("Hex line too long.");
		break;
	case error_hexUnsupportedEntry:
		display->println("Hex contains unknown");
		display->println("entry type.");
		break;
	case error_hexCheckSum:
		display->println("Hex file invalid.");
		display->println("Checksum error!");
		break;
	case error_hexFlashBounds:
		display->println("Hex file invalid.");
		display->println("Too big for flash!");
		break;
	case error_hexCharSymbol:
		display->println("Hex file invalid.");
		display->println("Invalid characters.");
		break;
	default:
		display->println("Unknown error.");
		break;
	}

	// Display back button in bottom right
	const char* back = "> OK";
	display->setCursor(DISPLAY_COLUMNS - display->strWidth(back), DISPLAY_ROWS - 1);
	display->print(back);
}
