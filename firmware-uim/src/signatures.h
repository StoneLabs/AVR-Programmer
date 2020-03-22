#pragma once

#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

// structure to hold signature and other relevant data about each chip
typedef struct {
    byte sig[3];                // chip signature
    char desc[14];              // fixed array size keeps chip names in PROGMEM
} Signature;

// see Atmega datasheets
const Signature signatures[] PROGMEM =
{
    { { 0x1E, 0x95, 0x0F }, "ATmega328P" },
};