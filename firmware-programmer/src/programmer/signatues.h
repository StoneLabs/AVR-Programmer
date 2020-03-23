#pragma once

// structure to hold signature and other relevant data about each chip
typedef struct {
    byte sig[3];                // chip signature
    char desc[14];              // fixed array size keeps chip names in PROGMEM
    unsigned long flashSize;     // how big the flash is (bytes)
    unsigned int baseBootSize;   // base bootloader size (others are multiples of 2/4/8)
    unsigned long pageSize;      // flash programming page size (bytes)
    byte fuseWithBootloaderSize; // ie. one of: lowFuse, highFuse, extFuse
    bool timedWrites;            // true if pollUntilReady won't work by polling the chip // NOT IMPLEMENTED
    byte safetyMaskOne;          // All bits in high that must be unprogrammed: one  (i.e. (val & safetyMaskOne ) != safetyMaskOne is forbidden)
    byte safetyMaskZero;         // All bits in high that must be   programmed: zero (i.e. (val & safetyMaskZero) != 0             is forbidden)
} Signature;

#define NO_FUSE (byte)0xFF

enum
{
    lowFuse = 0,
    highFuse = 1,
    extFuse = 2,
    lockFuse = 3,
    calibrationFuse = 4,
};

// see Atmega datasheets
const Signature signatures[] PROGMEM =
{
    // Currently only bootloader fuse = high is supported!

    //     signature        description   flash size   bootloader  flash   bootloader  timed    Safety      Safety
    //                                                     size    page     fuse       writes   Mask One    Mask Zero
    //                                                             size   
      { { 0x1E, 0x95, 0x0F }, "ATmega328P",  0x8000UL,   0x200U,   0x80UL, highFuse,   false,   0b11000000, 0b00100000},

};