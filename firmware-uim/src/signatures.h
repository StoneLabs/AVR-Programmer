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

    // Atmega644 family
      { { 0x1E, 0x95, 0x08 }, "ATmega324P" },
      { { 0x1E, 0x94, 0x0A }, "ATmega164P" },
      { { 0x1E, 0x96, 0x0A }, "ATmega644P" },

    // Atmega2560 family
      { { 0x1E, 0x96, 0x08 }, "ATmega640"  },
      { { 0x1E, 0x97, 0x03 }, "ATmega1280" },
      { { 0x1E, 0x97, 0x04 }, "ATmega1281" },

    // AT90USB family
      { { 0x1E, 0x93, 0x82 }, "At90USB82"  },
      { { 0x1E, 0x94, 0x82 }, "At90USB162" },

    // Atmega32U2 family
      { { 0x1E, 0x93, 0x89 }, "ATmega8U2"  },
      { { 0x1E, 0x94, 0x89 }, "ATmega16U2" },
      { { 0x1E, 0x95, 0x8A }, "ATmega32U2" },

    // Atmega32U4 family
      { { 0x1E, 0x94, 0x88 }, "ATmega16U4" },
      { { 0x1E, 0x95, 0x87 }, "ATmega32U4" },

    // ATmega1284P family
      { { 0x1E, 0x97, 0x05 }, "ATmega1284P"},
      { { 0x1E, 0x97, 0x06 }, "ATmega1284" },
};