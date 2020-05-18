#pragma once

#include "fuseNames.h"

#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))

// structure to hold signature and other relevant data about each chip
typedef struct {
    byte sig[3];                        // chip signature
    char desc[14];                      // fixed array size keeps chip names in PROGMEM
    const char* lowFuseNames[8];        // 8 pointer to progmem char[] with fuse bit names for low fuse
    const char* highFuseNames[8];       // 8 pointer to progmem char[] with fuse bit names for high fuse
    const char* extFuseNames[8];        // 8 pointer to progmem char[] with fuse bit names for high fuse
} Signature;

// see Atmega datasheets
const Signature signatures[] PROGMEM =
{
    // Attiny84 family
      { { 0x1E, 0x91, 0x0B }, "ATtiny24"   , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_SELFPRGEN  }},

      { { 0x1E, 0x92, 0x07 }, "ATtiny44"   , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_SELFPRGEN  }},

      { { 0x1E, 0x93, 0x0C }, "ATtiny84"   , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_SELFPRGEN  }},

    // Attiny85 family
      { { 0x1E, 0x91, 0x08 }, "ATtiny25"   , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_SELFPRGEN  }},

      { { 0x1E, 0x92, 0x06 }, "ATtiny45"   , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_SELFPRGEN  }},

      { { 0x1E, 0x93, 0x0B }, "ATtiny85"   , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_SELFPRGEN  }},

    // Atmega328 family
      { { 0x1E, 0x92, 0x0A }, "ATmega48PA" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_SELFPRGEN  }},

      { { 0x1E, 0x93, 0x0F }, "ATmega88PA" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }},

      { { 0x1E, 0x94, 0x0B }, "ATmega168PA", { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }},

      { { 0x1E, 0x94, 0x06 }, "ATmega168V" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }},

      { { 0x1E, 0x95, 0x0F }, "ATmega328P" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},
      
      { { 0x1E, 0x95, 0x16 }, "ATmega328PB", { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

      { { 0x1E, 0x95, 0x14 }, "ATmega328"  , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_RSTDISBL   , FBIT_DWEN       , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

    // Atmega644 family
      { { 0x1E, 0x95, 0x08 }, "ATmega324P" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

      { { 0x1E, 0x94, 0x0A }, "ATmega164P" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

      { { 0x1E, 0x96, 0x0A }, "ATmega644P" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

    // Atmega2560 family
      { { 0x1E, 0x96, 0x08 }, "ATmega640"  , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

      { { 0x1E, 0x97, 0x03 }, "ATmega1280" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

      { { 0x1E, 0x97, 0x04 }, "ATmega1281" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

      { { 0x1E, 0x98, 0x01 }, "ATmega2560" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

      { { 0x1E, 0x98, 0x02 }, "ATmega2561" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

    // AT90USB family
      { { 0x1E, 0x93, 0x82 }, "At90USB82"  , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_DWEN       , FBIT_RSTDISBL   , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_HWBE       , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

      { { 0x1E, 0x94, 0x82 }, "At90USB162" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_DWEN       , FBIT_RSTDISBL   , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_HWBE       , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  }},

    // Atmega32U2 family
      { { 0x1E, 0x93, 0x89 }, "ATmega8U2"  , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_DWEN       , FBIT_RSTDISBL   , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_HWBE       , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  } },

      { { 0x1E, 0x94, 0x89 }, "ATmega16U2" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_DWEN       , FBIT_RSTDISBL   , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_HWBE       , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  } },

      { { 0x1E, 0x95, 0x8A }, "ATmega32U2" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_DWEN       , FBIT_RSTDISBL   , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_HWBE       , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  } },

    // Atmega32U4 family
      { { 0x1E, 0x94, 0x88 }, "ATmega16U4" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_HWBE       , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  } },

      { { 0x1E, 0x95, 0x87 }, "ATmega32U4" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_HWBE       , FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  } },

    // ATmega1284P family
      { { 0x1E, 0x97, 0x05 }, "ATmega1284P", { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  } },

      { { 0x1E, 0x97, 0x06 }, "ATmega1284" , { FBIT_CKDIV8     , FBIT_CKOUT      , FBIT_SUT1       , FBIT_SUT0       , FBIT_CKSEL3     , FBIT_CKSEL2     , FBIT_CKSEL1     , FBIT_CKSEL0     }
                                           , { FBIT_OCDEN      , FBIT_JTAGEN     , FBIT_SPIEN      , FBIT_WDTON      , FBIT_EESAVE     , FBIT_BOOTSZ1    , FBIT_BOOTSZ0    , FBIT_BOOTRST    }
                                           , { FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_NO_FUNCTION, FBIT_BODLEVEL2  , FBIT_BODLEVEL1  , FBIT_BODLEVEL0  } },
};