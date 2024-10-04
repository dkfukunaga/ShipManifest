

#ifndef DATAFILE_HEADERS_H
#define DATAFILE_HEADERS_H

#include <cstdint>


typedef uint16_t    index_t;        // data record index
typedef uint16_t    recsize_t;      // data record size in bytes
typedef uint16_t    count_t;        // data record count
typedef uint32_t    length_t;       // file or table size in bytes
typedef uint32_t    offset_t;       // data record offset from file start


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
constexpr FileSig FileSig::ship_registry = {0x0C, 0xA7, 0xCA, 0xFE, 'S', 'H', 'P', 'R', 'E', 'G'};

// 4 char file type id
struct FileType {
    uint8_t         type[4];

    static const FileType ships;
    static const FileType ship_classes;
    static const FileType ship_components;
    static const FileType game_characters;
};

// Ships database file "SHIP"
constexpr FileType FileType::ships              = {'S', 'H', 'I', 'P'};
// Ship Classes database file "SHLS"
constexpr FileType FileType::ship_classes       = {'S', 'C', 'L', 'S'};
// Ship Components database file "SCMP"
constexpr FileType FileType::ship_components    = {'S', 'C', 'M', 'P'};
// Game Characters database file "GCHR"
constexpr FileType FileType::game_characters    = {'G', 'C', 'H', 'R'};

// 4 char section type id
struct SectionType {
    uint8_t         type[4];
 
    static const SectionType data;
    static const SectionType index;
    static const SectionType eof;
};

// Data section ":DAT"
constexpr SectionType SectionType::data     = {':', 'D', 'A', 'T'};
// Index section ":IDX"
constexpr SectionType SectionType::index    = {':', 'I', 'D', 'X'};
// End Of File ":EOF"
constexpr SectionType SectionType::eof      = {':', 'E', 'O', 'F'};

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
constexpr DataType DataType::ship       = {'S', 'P'};
// ShipClass data "CL"
constexpr DataType DataType::ship_class = {'C', 'L'};
// Subsystem data "SB"
constexpr DataType DataType::subsystem  = {'S', 'B'};
// Weapon data "WP"
constexpr DataType DataType::weapon     = {'W', 'P'};
// Officer data "OF"
constexpr DataType DataType::officer    = {'O', 'F'};

// File Header
struct FileHeader {
    FileSig         sig = FileSig::ship_registry;   // file signature
    FileFlags       flags;          // file status flags
    uint8_t         version;        // file version
    FileType        type;           // file type
    length_t        length;         // file size in bytes
    offset_t        index_offset;   // offset of index section
};

// Section header
struct SectionHeader {
    length_t        length;         // size of section in bytes, excluding header
    SectionType     type;           // type of section
};

// Table header
struct TableHeader {
    length_t        length;         // size of table in bytes, excluding header
    DataType        type;           // type of data in table
    count_t         count;          // count of records in table
};

// header for Data record
struct DataRecordHeader {
    index_t         index;          // 0 indicates deleted record
    recsize_t       size;           // size of record in bytes, excluding header
    offset_t        redirect;       // 0 indicates no redirect
};

// Index record
struct IndexRecord {
    index_t         index;          // data record index
    offset_t        offset;         // data record offset
};


#endif