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
    // Attiny84 family
      { { 0x1E, 0x91, 0x0B }, "ATtiny24"   },
      { { 0x1E, 0x92, 0x07 }, "ATtiny44"   },
      { { 0x1E, 0x93, 0x0C }, "ATtiny84"   },

    // Attiny85 family
      { { 0x1E, 0x91, 0x08 }, "ATtiny25"   },
      { { 0x1E, 0x92, 0x06 }, "ATtiny45"   },
      { { 0x1E, 0x93, 0x0B }, "ATtiny85"   },

    // Atmega328 family
      { { 0x1E, 0x92, 0x0A }, "ATmega48PA" },
      { { 0x1E, 0x93, 0x0F }, "ATmega88PA" },
      { { 0x1E, 0x94, 0x0B }, "ATmega168PA"},
      { { 0x1E, 0x94, 0x06 }, "ATmega168V" },
      { { 0x1E, 0x95, 0x0F }, "ATmega328P" },
      { { 0x1E, 0x95, 0x16 }, "ATmega328PB"},
      { { 0x1E, 0x95, 0x14 }, "ATmega328"  },

    // Atmega644 family
      { { 0x1E, 0x95, 0x08 }, "ATmega324P" },
      { { 0x1E, 0x94, 0x0A }, "ATmega164P" },
      { { 0x1E, 0x96, 0x0A }, "ATmega644P" },

    // Atmega2560 family
      { { 0x1E, 0x96, 0x08 }, "ATmega640"  },
      { { 0x1E, 0x97, 0x03 }, "ATmega1280" },
      { { 0x1E, 0x97, 0x04 }, "ATmega1281" },
      { { 0x1E, 0x98, 0x01 }, "ATmega2560" },
      { { 0x1E, 0x98, 0x02 }, "ATmega2561" },

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