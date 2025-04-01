

#ifndef FILE_FORMAT_H
#define FILE_FORMAT_H

#include "..\DataFile\src\DataFile.h"
#include <cstdint>

using SizeType = uint32_t;
using OffType = uint32_t;


enum class FileType : uint16_t {
    index = 1,
    data = 2
};

enum class RecType : uint16_t {
    ship = 1,
    ship_class = 2,
    weapon = 3,
    officer = 5
};


// File Header
struct FileHeader {
    uint64_t magic_number;      // Magic number to identify the file type (e.g., 0xCA7CAFE)
    FileType file_type;         // Enum for file type (Data, Index)
    RecType  record_type;       // Enum for record type (Ship, Weapon, etc.)
    uint16_t flags;             // Storage format flags (e.g., compressed, encrypted)
    uint16_t version;           // File version
    OffType  data_offset;       // Byte offset of first data record
    OffType  free_list_head;    // Byte offset of first free space
    SizeType free_list_size;    // Total size of free space
    SizeType fileSize;          // Total file size
    uint64_t created_timestamp; // Timestamp for file creation
    uint64_t modified_timestamp;// Timestamp for last modification
    uint64_t reserved;          // Reserved space for future expansion
};

// Record Header
struct RecordHeader {
    uint16_t flags;             // active, deleted
    uint16_t padding;           // padding to ensure proper alignment
    SizeType size;              // record size
    OffType  next_free;         // offset of next free record
    uint32_t reserved;          // Reserved space for future expansion
};


#endif

