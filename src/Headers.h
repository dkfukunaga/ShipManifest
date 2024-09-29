

#ifndef HEADERS_H
#define HEADERS_H

#include <cstdint>

typedef uint32_t    offset_t;
typedef uint16_t    index_t;


// File status flags
enum class FileFlags : uint8_t {
    good            = 0b00000001,   // no errors
    modified        = 0b00000010,   // file has been modifed
    rebuild_index   = 0b00000100,   // index needs rebuild
    sort            = 0b00001000,   // data needs resort
    open            = 0b00010000,   // file is open
    bad             = 0b10000000,   // unspecified error
};

// 10 byte file signature
struct FileSig {
    uint8_t         sig[10];

    static const FileSig ship_registry;
};

// Ship Registry file signature
// 0C A7 CA FE 53 48 50 52 45 47 (....SHPREG)
const FileSig FileSig::ship_registry = {0x0C, 0xA7, 0xCA, 0xFE, 'S', 'H', 'P', 'R', 'E', 'G'};

// 4 char file type id
struct FileType {
    uint8_t         type[4];

    static const FileType ships;
    static const FileType ship_classes;
    static const FileType ship_components;
    static const FileType game_characters;
};

// Ships database file "SHIP"
const FileType FileType::ships              = {'S', 'H', 'I', 'P'};
// Ship Classes database file "SHLS"
const FileType FileType::ship_classes       = {'S', 'C', 'L', 'S'};
// Ship Components database file "SCMP"
const FileType FileType::ship_components    = {'S', 'C', 'M', 'P'};
// Game Characters database file "GCHR"
const FileType FileType::game_characters    = {'G', 'C', 'H', 'R'};

// 4 char section type id
struct SectionType {
    uint8_t         type[4];

    static const SectionType data;
    static const SectionType index;
    static const SectionType eof;
};

// Data section ":DAT"
const SectionType SectionType::data     = {':', 'D', 'A', 'T'};
// Index section ":IDX"
const SectionType SectionType::index    = {':', 'I', 'D', 'X'};
// End Of File ":EOF"
const SectionType SectionType::eof      = {':', 'E', 'O', 'F'};

// 2 byte data type id
struct DataType {
    uint8_t         type[2];

    static const DataType ship;
    static const DataType ship_class;
    static const DataType subsystem;
    static const DataType weapon;
    static const DataType officer;
};

// Ship data "SP"
const DataType DataType::ship       = {'S', 'P'};
// ShipClass data "CL"
const DataType DataType::ship_class = {'C', 'L'};
// Subsystem data "SB"
const DataType DataType::subsystem  = {'S', 'B'};
// Weapon data "WP"
const DataType DataType::weapon     = {'W', 'P'};
// Officer data "OF"
const DataType DataType::officer    = {'O', 'F'};

// File Header
struct FileHeader {
    FileSig         sig = FileSig::ship_registry;   // file signature
    FileFlags       flags;          // file status flags
    uint8_t         version;        // file version
    FileType        type;           // file type
    uint32_t        size;           // file size in bytes
    offset_t        index_offset;   // offset of index section
};

// Section header
struct SectionHeader {
    uint32_t        size;           // size of section in bytes, excluding header
    SectionType     type;           // type of section
};

// Table header
struct TableHeader {
    uint32_t        size;           // size of table in bytes, excluding header
    DataType        type;           // type of data in table
    uint16_t        count;          // count of records in table
};

// header for Data record
struct DataRecordHeader {
    index_t         index;          // 0 indicates deleted record
    uint16_t        size;           // size of record in bytes, excluding header
    offset_t        redirect;       // 0 indicates no redirect
};

// Index record
struct IndexRecord {
    index_t         index;          // data record index
    offset_t        offset;         // data record offset
};


#endif