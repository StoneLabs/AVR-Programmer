#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

// Names of the fuse bits are stored below. They are mapped
// to signatures inside signatures.h. They can be retrieved via
// strcpy_P.

const byte FBIT_MAX_LENGTH = 12;

const char FBIT_NO_FUNCTION     [] PROGMEM = "NO FUNCTION";
const char FBIT_UNKNOWN			[] PROGMEM = "UNKNOWN";

const char FBIT_CKDIV8			[] PROGMEM = "CKDIV8";
const char FBIT_CKOUT			[] PROGMEM = "CKOUT";
const char FBIT_SUT1			[] PROGMEM = "SUT1";
const char FBIT_SUT0			[] PROGMEM = "SUT0";
const char FBIT_CKSEL3			[] PROGMEM = "CKSEL3";
const char FBIT_CKSEL2			[] PROGMEM = "CKSEL2";
const char FBIT_CKSEL1			[] PROGMEM = "CKSEL1";
const char FBIT_CKSEL0			[] PROGMEM = "CKSEL0";
const char FBIT_RSTDISBL		[] PROGMEM = "RSTDISBL";
const char FBIT_DWEN			[] PROGMEM = "DWEN";
const char FBIT_SPIEN			[] PROGMEM = "SPIEN";
const char FBIT_WDTON			[] PROGMEM = "WDTON";
const char FBIT_EESAVE			[] PROGMEM = "EESAVE";
const char FBIT_BOOTSZ1			[] PROGMEM = "BOOTSZ1";
const char FBIT_BOOTSZ0			[] PROGMEM = "BOOTSZ0";
const char FBIT_BOOTRST			[] PROGMEM = "BOOTRST";
const char FBIT_BODLEVEL2		[] PROGMEM = "BODLEVEL2";
const char FBIT_BODLEVEL1		[] PROGMEM = "BODLEVEL1";
const char FBIT_BODLEVEL0		[] PROGMEM = "BODLEVEL0";
const char FBIT_SELFPRGEN		[] PROGMEM = "SELFPRGEN";
const char FBIT_OCDEN			[] PROGMEM = "OCDEN";
const char FBIT_JTAGEN			[] PROGMEM = "JTAGEN";
const char FBIT_HWBE			[] PROGMEM = "HWBE";
