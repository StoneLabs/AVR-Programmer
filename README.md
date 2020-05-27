![GitHub tag (latest by date)](https://img.shields.io/github/v/tag/StoneLabs/AVR-Programmer?label=Version&style=flat-square) ![GitHub issues](https://img.shields.io/github/issues-raw/StoneLabs/AVR-Programmer?style=flat-square) ![Maintenance](https://img.shields.io/maintenance/yes/2020?style=flat-square)

<img src="schematics/media/StoneLabs.png" align="right" width="200" />

# Stone Labs. AVR-Programmer
Schematics and firmware for a portable In-Service-Programmer. It is designed to be powered by a 9V battery and uses an OLED Display module for user interaction. INTEL HEX Files can be flashed to target chips via an ISP-6 port directly from an SD-Card.

# PCB

The Programmer is designed to sit on a portable ~9x11cm PCB. Eagle files for the PCB can be found in the `schematics` folder. Target chips can be programmed with the 6-pin Header located at the top of the PCB. There is also an 8Mhz clock pin available (TCLK) in case the target needs an external clock and none is available. BOM for the programmer can be found in `schematics/bom-grouped.csv`. All parts are available from DIGI-KEY. The price per assembled PCB should be around 10-30 bucks depending on the order quantity.


Aside from the programmer, there is target PCB design under `schematics-target`. The target can hold an ATmega328P like chip that can be programmed by connecting the target boards ISP Header to the programmer ISP-Port.

[Picture of PCB revision 1 (Release_V-1.0)](/pcb_v-1.0.png)

| PCB | Version | Status |
| - | - | - |
| Main PCB | Hardware_V-1.0 | Pull-Ups R1, R2 are connected incorrectly (to GND instead of +5V)! Assembled and tested. Works without R1, R2. |
| Main PCB | Hardware_V-1.1 | Fixed only R1, R2 and should work better than V-1.0. Untested! |
| Main PCB | Hardware_V-1.1+ | No functional hardware change. |
| Target PCB | Hardware_V-1.2 | Assembled and tested. Fully functional. |

# Supported chips

![#32CD32](https://via.placeholder.com/15/32CD32/000000?text=+) Supported and tested  
![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) Supported not tested  
![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) Not yet supported  

||Chip||Chip|
| - | - | - | - |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega1280    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega329A    |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega1281    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega329PA   |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega1284P   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega329P    |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega1284    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega329     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega128A    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega32A     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega128RFA1 |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega32C1    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega128     |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega32HVB   |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega162     |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega32M1    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega164A    |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega32U2    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega164PA   |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega32U4    |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega164P    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega32      |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega165A    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega48A     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega165PA   |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega48PA    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega165P    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega48P     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega168A    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega48      |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega168PA   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega640     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega168P    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega644A    |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega168V    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega644PA   |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega168     |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega644P    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega169A    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega644     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega169PA   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega6450A   |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega169P    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega6450P   |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega16A     |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega6450    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega16HVB   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega645A    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega16M1    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega645P    |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega16U2    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega645     |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega16U4    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega6490A   |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega16      |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega6490P   |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega2560    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega6490    |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega2561    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega649A    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega324A    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega649P    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega324PA   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega649     |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega324P    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega64A     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega3250A   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega64C1    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega3250PA  |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega64M1    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega3250P   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega64      |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega3250    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega8515    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega325A    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega8535    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega325PA   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega88A     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega325P    |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega88PA    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega325     |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega88P     |
|  ![#32CD32](https://via.placeholder.com/15/32CD32/000000?text=+) | ATmega328P    |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega88      |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega328PB   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega8A      |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega328     |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATmega8U2     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega3290A   |  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega8       |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega3290PA  |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | At90USB82     |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega3290P   |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | At90USB162    |
|  ![#f03c15](https://via.placeholder.com/15/f03c15/000000?text=+) | ATmega3290    |                                                                  |               |
| | | | |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATtiny24      |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATtiny25      |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATtiny44      |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATtiny45      |
|  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATtiny84      |  ![#FFA500](https://via.placeholder.com/15/FFA500/000000?text=+) | ATtiny85      |

# License

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>

### That being said, I'd really like to hear from you if you plan on using this project somewhere. And I for sure wouldn't mind some part if you use it commercially ;) (e.g. selling it etc.)
