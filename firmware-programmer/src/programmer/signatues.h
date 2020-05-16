#pragma once

// structure to hold signature and other relevant data about each chip
typedef struct {
    byte sig[3];                // chip signature
    char desc[14];              // fixed array size keeps chip names in PROGMEM
    unsigned long flashSize;     // how big the flash is (bytes)
    unsigned int baseBootSize;   // base bootloader size (others are multiples of 2/4/8)
    unsigned long pageSize;      // flash programming page size (bytes)
    byte fuseWithBootloaderSize; // ie. one of: val_lowFuse, val_highFuse, val_extFuse
    bool timedWrites;            // true if pollUntilReady won't work by polling the chip
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
    // Currently only non timed writes are supported!

    //     signature        description     flash size    bootloader  flash   bootloader  timed    Safety      Safety
    //                                                       size     page     fuse       writes   Mask One    Mask Zero
    //                                                                size   
    // Atmega328 family
      { { 0x1E, 0x95, 0x0F }, "ATmega328P",   0x8000UL,   0x200U,    0x80UL, highFuse,   false,   0b11000000, 0b00100000},

    // Atmega644 family
      { { 0x1E, 0x95, 0x08 }, "ATmega324P",   0x8000UL,   0x200U,    0x80UL, highFuse,   false,   0b10000000, 0b01100000},
      { { 0x1E, 0x94, 0x0A }, "ATmega164P",   0x4000UL,   0x100U,    0x80UL, highFuse,   false,   0b10000000, 0b01100000},
      { { 0x1E, 0x96, 0x0A }, "ATmega644P",  0x10000UL,   0x400U,   0x100UL, highFuse,   false,   0b10000000, 0b01100000},

    // Atmega2560 family
      { { 0x1E, 0x96, 0x08 }, "ATmega640",   0x10000UL,   0x400U,   0x100UL, highFuse,   false,   0b10000000, 0b01100000},
      { { 0x1E, 0x97, 0x03 }, "ATmega1280",  0x20000UL,   0x400U,   0x100UL, highFuse,   false,   0b10000000, 0b01100000},
      { { 0x1E, 0x97, 0x04 }, "ATmega1281",  0x20000UL,   0x400U,   0x100UL, highFuse,   false,   0b10000000, 0b01100000},
      { { 0x1E, 0x98, 0x01 }, "ATmega2560",  0x40000UL,   0x400U,   0x100UL, highFuse,   false,   0b10000000, 0b01100000},
      { { 0x1E, 0x98, 0x02 }, "ATmega2561",  0x40000UL,   0x400U,   0x100UL, highFuse,   false,   0b10000000, 0b01100000},

    // AT90USB family
      { { 0x1E, 0x93, 0x82 }, "At90USB82",    0x2000UL,   0x200U,    0x80UL, highFuse,   false,   0b11000000, 0b00100000},
      { { 0x1E, 0x94, 0x82 }, "At90USB162",   0x4000UL,   0x200U,    0x80UL, highFuse,   false,   0b11000000, 0b00100000},

    // Atmega32U2 family
      { { 0x1E, 0x93, 0x89 }, "ATmega8U2",    0x2000UL,   0x200U,    0x80UL, highFuse,   false,   0b11000000, 0b00100000},
      { { 0x1E, 0x94, 0x89 }, "ATmega16U2",   0x4000UL,   0x200U,    0x80UL, highFuse,   false,   0b11000000, 0b00100000},
      { { 0x1E, 0x95, 0x8A }, "ATmega32U2",   0x8000UL,   0x200U,    0x80UL, highFuse,   false,   0b11000000, 0b00100000},

    // Atmega32U4 family -  (datasheet is wrong about flash page size being 128 words)
      { { 0x1E, 0x94, 0x88 }, "ATmega16U4",   0x4000UL,   0x200U,    0x80UL, highFuse,   false,   0b10000000, 0b01100000},
      { { 0x1E, 0x95, 0x87 }, "ATmega32U4",   0x8000UL,   0x200U,    0x80UL, highFuse,   false,   0b10000000, 0b01100000},

    // ATmega1284P family
      { { 0x1E, 0x97, 0x05 }, "ATmega1284P", 0x20000UL,   0x400U,   0x100UL, highFuse,   false,   0b10000000, 0b01100000},
      { { 0x1E, 0x97, 0x06 }, "ATmega1284",  0x20000UL,   0x400U,   0x100UL, highFuse,   false,   0b10000000, 0b01100000},
};