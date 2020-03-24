#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// Line format :
// 
// : nnaaaatt(data)ss
// 
// Where :
// : = a colon
// 
// (All of below in hex format)
// 
// nn = length of data part
// aaaa = address(eg.where to write data)
// tt = transaction type:
//  00 = data
//  01 = end of file
//  02 = extended segment address (data * 0x10 is added to all subsequent data entries)
//  03 = start segment address  (NOT SUPPORTED)
//  04 = linear address         (NOT SUPPORTED)
//  05 = start linear address   (NOT SUPPORTED)
// (data) = variable length data (most common are 16 and 32 bytes)
// ss = sumcheck
// 
//
// Line length for max 32 data bytes (64 chars):
#define HEX_LINE_LENGTH 76
#define HEX_MAX_DATALEN 32

#include <SPI.h>
#include <SdFat.h>

#include "src/debug.h"
#include "src/programmer/bbprogrammer.h"
#include "src/programmer/signatues.h"

// Helper functions
void printFuses(const programmer::BBProgrammer::Fuse& fuse);
void printSignature(const Signature* signature);
byte hexton(byte h);
byte twos_complement(byte val);
unsigned long readImagePage(SdFile* file, const unsigned long flashsize, const unsigned long pageaddr, const unsigned long pagesize, byte* pagebuffer);

void flashFile(SdFile* file, programmer::BBProgrammer* bbprogrammer);
