

#ifndef HEADERS_H
#define HEADERS_H

#include <cstdint>

typedef uint32_t offset_t;
typedef uint16_t index_t;




enum class FileFlags : uint8_t {
    good            = 0b00000001,
    modified        = 0b00000010,
    rebuild_index   = 0b00000100,
    sort            = 0b00001000,
    open            = 0b00010000,
    bad             = 0b10000000,
};

enum class DataFlags : uint8_t {
    good            = 0b00000001,
    modified        = 0b00000010,
    incomplete      = 0b00000100,
    deleted         = 0b00001000,
    relocated       = 0b00010000,
    bad             = 0b10000000,
};

struct FileID {
    uint8_t         magic_bytes[10];

    static const FileID ship_db;
};

const FileID FileID::ship_db = {0x0C, 0xA7, 0xCA, 0xFE, 'S', 'H', 'I', 'P', 'D', 'B'};

struct FileType {
    char            type[4];

    static const FileType ships;
    static const FileType ship_classes;
    static const FileType subsystems;
    static const FileType weapons;
    static const FileType officers;
};

const FileType FileType::ships          = {'S', 'H', 'I', 'P'};
const FileType FileType::ship_classes   = {'S', 'C', 'L', 'S'};
const FileType FileType::subsystems     = {'S', 'S', 'Y', 'S'};
const FileType FileType::weapons        = {'W', 'E', 'A', 'P'};
const FileType FileType::officers       = {'O', 'F', 'C', 'R'};

struct ChunkType {
    char            type[4];

    static const ChunkType ship;
    static const ChunkType ship_class;
    static const ChunkType subsystem;
    static const ChunkType weapon;
    static const ChunkType officer;
    static const ChunkType index;
    static const ChunkType eof;
};

const ChunkType ChunkType::ship         = {0xFF, 0xFF, 'S', 'P'};
const ChunkType ChunkType::ship_class   = {0xFF, 0xFF, 'C', 'L'};
const ChunkType ChunkType::subsystem    = {0xFF, 0xFF, 'S', 'B'};
const ChunkType ChunkType::weapon       = {0xFF, 0xFF, 'W', 'P'};
const ChunkType ChunkType::officer      = {0xFF, 0xFF, 'O', 'F'};
const ChunkType ChunkType::index        = {0xFF, 0xFF, 'I', 'N'};
const ChunkType ChunkType::eof          = {0xFF, 0xFF, 0X99, 0X3A};



struct FileHeader {
    FileID          id = FileID::ship_db;
    FileFlags       flags;
    uint8_t         version = 1;
    FileType        type;
    uint32_t        size;
    offset_t        data_offset = 0;
    offset_t        index_offset = 0;
    uint8_t         padding[4] = {0};
};

struct  ChunkHeader {
    ChunkType       type;
    uint16_t        size = 0;
};

struct DataEntry {
    DataFlags       flags;
    index_t         index;
    uint32_t        redirect = 0;
};

struct IndexTable {
    uint16_t        count;
    uint16_t        entry_size;
};

struct IndexEntry {
    index_t         index;
    offset_t        offset;
};


#endif