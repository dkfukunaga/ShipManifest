#pragma once
#ifndef FILE_FORMAT_H
#define FILE_FORMAT_H

#include <cstdint>

enum class FileType : uint16_t {
    index = 1,
    data = 2,
};

enum class RecordType : uint16_t {
    ship = 1,
    ship_class = 2,
    module = 3,         // not yet implemented
    weapon = 4,
    officer = 10,
};

#pragma pack(push, 1)
// File Header
struct FileHeader {
    uint64_t        magic_number;       // Magic number to identify the file type (e.g., 0xCA7CAFE)
    FileType        file_type;          // Enum for file type (Data, Index)
    RecordType      record_type;        // Enum for record type
    uint16_t        flags;              // Storage format flags (e.g., compressed, encrypted)
    uint16_t        version;            // file version
    uint32_t        data_offset;        // Byte offset of first data record
    uint32_t        free_list_head;     // Byte offset of first free space
    uint32_t        free_list_size;     // Total size of free space
    uint32_t        fileSize;           // Total file size
    uint64_t        created;            // Date created in epoch time
    uint64_t        last_modified;      // Date last modified in epoch time
    uint64_t        reserved[2];        // Reserved space for future expansion
};

// Record Header
struct RecordHeader {
    uint16_t        flags;              // active, deleted
    uint16_t        padding;            // padding to ensure proper alignment
    uint32_t        size;               // record size
    uint32_t        next_free;          // offset of next free record
    uint32_t        reserved;           // Reserved space for future expansion
};
#pragma pack(pop)



#endif