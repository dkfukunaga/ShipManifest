#pragma once
#ifndef FILE_FORMAT_H
#define FILE_FORMAT_H

#include <cstdint>

enum class FileType : uint16_t {
    index = 1,
    data = 2,
};

enum class EntityType : uint16_t {
    ship = 1,
    ship_class = 2,
    module = 50,         // not yet implemented
    weapon = 51,
    officer = 100,
};

#pragma pack(push, 1)
// File Header
struct FileHeader {
    uint64_t        magic_number;       // 0x0CA7CAFE
    uint16_t        version;            // file version
    FileType        file_type;          // Enum for file type (Data, Index)
    EntityType      entity_type;        // Enum for record type
    uint16_t        flags;              // Storage format flags (e.g., compressed, encrypted)
    uint32_t        data_offset;        // Byte offset of first data record
    uint32_t        free_list_head;     // Byte offset of first free space
    uint32_t        free_list_size;     // Total size of free space
    uint32_t        file_size;          // Total file size
    uint64_t        time_created;       // Date created in epoch time
    uint64_t        last_modified;      // Date last modified in epoch time
    uint64_t        reserved[2];        // Reserved space for future expansion
};

// Entity Header
struct EntityHeader {
    uint16_t        flags;              // active, deleted
    uint16_t        subtype;            // reserved for subtype
    uint32_t        size;               // record size
    uint32_t        next_free;          // offset of next free record
    uint32_t        reserved;           // Reserved space for future expansion
};
#pragma pack(pop)



#endif