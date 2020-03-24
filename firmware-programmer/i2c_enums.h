#pragma once

enum : byte
{
    //// Meta operations
    cmd_ping = 0x01,

    // Open next file (will cycle around)
    cmd_openNextFile = 0x02,

    // Rewinds to first file in directory
    cmd_rewindFile = 0x03,

    //// Read operations
    cmd_readSignature = 0x10,
    cmd_readFuses = 0x11,

    //// Write operations
    cmd_erase = 0x20,
    cmd_flashFile = 0x21,
    cmd_writeLowFuse = 0x22,
    cmd_writeHighFuse = 0x23,
    cmd_writeExtFuse = 0x24,
    cmd_writeLockFuse = 0x25,
};
enum : byte
{
    // Meta errors
    error_unknownCommand = 0x01,

    // General errors
    error_programmingMode = 0x10,
    error_openFile = 0x11,

    // Flashing specific errors
    error_bootloaderSupport = 0x20,

    // Hex file specific error
    error_hexInvalid = 0x30,
    error_hexLineTooLong = 0x31,
    error_hexUnsupportedEntry = 0x32,
    error_hexCheckSum = 0x33,
    error_hexFlashBounds = 0x34,
    error_hexCharSymbol = 0x35,

    // Fuse writing specific errors
    error_fuseCheckMismatch = 0x40,
    error_fuseWithoutSignature = 0x41,
    error_refusedByProgrammer = 0x42,
};