#pragma once

#define DEBUG_NONE 0		// No debug output
#define DEBUG_ERROR 1		// Only errors that stop the program
#define DEBUG_WARN 2		// And Warnings
#define DEBUG_INFO 3		// And general information
#define DEBUG_DEBUG 4		// And debug output
#define DEBUG_VERBOSE 5		// And verbose output (more detailed Debug output)
#define DEBUG_ALL 6			// Even more debug output on lowlevel events

// Change debug level here
#define DEBUG DEBUG_INFO

// 
// HELPER
//
#define Debug( level, ... ) do { if ( DEBUG >= level) Serial.print( __VA_ARGS__ ); } while (0)
#define Debugln( level, ... ) do { if (DEBUG >= level) Serial.println(__VA_ARGS__); } while (0)
#define HaltError( X ) do { Debugln(DEBUG_ERROR, X); while (true) {}; } while (0)
// Tested: The while and if will be striped by the compiler. No flash overhead is produced.