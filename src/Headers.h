

#ifndef HEADERS_H
#define HEADERS_H

#include <cstdint>

typedef uint32_t offset_t;
typedef uint16_t chunk_size_t;
typedef uint16_t index_t;

struct FileType {
    char            type[4];

    static const FileType empty;
    static const FileType ships;
    static const FileType ship_classes;
    static const FileType subsystems;
    static const FileType weapons;
    static const FileType officers;
};

const FileType FileType::empty  = {'0', '0', '0', '0'};
const FileType FileType::ships = {'S', 'H', 'I', 'P'};
const FileType FileType::ship_classes = {'S', 'C', 'L', 'S'};
const FileType FileType::subsystems = {'S', 'U', 'B', 'S'};
const FileType FileType::weapons = {'W', 'E', 'A', 'P'};
const FileType FileType::officers = {'O', 'F', 'C', 'R'};


enum class ChunkType : uint8_t {
    ship            = 0xA1,
    ship_class      = 0xA2,
    subsystem       = 0xB1,
    weapon          = 0xB2,
    officer         = 0xC1,
};

enum class FileFlags : uint8_t {
    uninitialized   = 0b00000000,
    good            = 0b00000001,
    modified        = 0b00000010,
    index           = 0b00000100,
    sort            = 0b00001000,
    open            = 0b00010000,
    bad             = 0b10000000,
};

enum class ChunkFlags : uint8_t {
    good            = 0b00000001,
    modified        = 0b00000010,
    incomplete      = 0b00000100,
    deleted         = 0b00001000,
    relocated       = 0b00010000,
    bad             = 0b10000000,
};


// 0E 0F
const uint8_t       file_eof[2] = {0x0E, 0x0F};

struct FileHeader {
    uint8_t         file_id[10] = {0x0C, 0xA7, 0xCA, 0xFE, 0x53, 0x48, 0x49, 0x50, 0x44, 0x42};
    FileFlags       file_flags = FileFlags::uninitialized;
    uint8_t         file_version = 1;
    FileType        file_type = FileType::empty;
    uint32_t        file_size = 32;
    offset_t        data_offset = 0;
    offset_t        index_offset = 0;
    uint8_t         padding[4] = {0};
};



#endif