

#ifndef DATA_FILE_HEADERS_H
#define DATA_FILE_HEADERS_H

#include <cstdint>

/***** TYPEDEFS *****/

// absolute file offset
typedef uint32_t offset_t;

// file chunk index
typedef uint16_t index_t;

// file chunk size
typedef uint16_t chunk_size_t;

/**** ENUMS *****/

// bitmasks for FileFlags
//
// 0000 0001: good - file is good to go
// 0000 0010: modified - set if anything in the file was ever changed this session
// 0000 0100: rebuild_index - set if index needs to be rebuilt
// 0000 1000: rebuild_file - set if chunks needs to be resorted and file rebuilt
// 0001 0000: open - set if file is open and being accessed
// 1000 0000: bad - for any kind of error
enum class FileFlags : uint8_t {
    good            = 0b00000001,       // file is good to go
    modified        = 0b00000010,       // set if anything in the file was ever changed this session
    rebuild_index   = 0b00000100,       // set if index needs to be rebuilt
    rebuild_file    = 0b00001000,       // set if chunks needs to be resorted and file rebuilt
    open            = 0b00010000,       // set if file is open and being accessed
    bad             = 0b10000000,       // for any kind of error
};

// bitmasks for ChunkFlags
//
// 0000 0001: good - chunk is good to go
// 0000 0010: modified - set if Chunk has been modified
// 0000 0100: incomplete - set if Chunk is missing required data (incomplete record)
// 0000 1000: deleted - set if Chunk is marked for deletion
// 0001 0000: relocate - set if Chunk has been relocated to another offset
// 0010 0000: resort - set if Chunk is out of order and needs to be sorted
// 1000 0000: bad - for any kind of error
enum class ChunkFlags : uint8_t {
    good            = 0b00000001,       // chunk is good to go
    modified        = 0b00000010,       // set if Chunk has been modified
    incomplete      = 0b00000100,       // set if Chunk is missing required data (incomplete record)
    deleted         = 0b00001000,       // set if Chunk is marked for deletion
    relocate        = 0b00010000,       // set if Chunk has been relocated to another offset
    resort          = 0b00100000,       // set if Chunk is out of order and needs to be sorted
    bad             = 0b10000000,       // for any kind of error
};

struct FileType {
    char                type[4];

    FileType() {
        for (int i = 0; i < 4; ++i)
            type[i] = ' ';
    }
    FileType(std::string code) {
        for (int i = 0; i < 4; ++i)
            type[i] = code[i];
    }
    FileType(const char* code) {
        for (int i = 0; i < 4; ++i)
            type[i] = code[i];
    }
    FileType(const FileType &other) {
        for (int i = 0; i < 4; ++i)
            (*this)[i] = other[i];
    }
    // operator uint8_t() {return *type; }

    char& operator[](int idx) {
        return this->type[idx];
    }
    const char& operator[](int idx) const  {
        return this->type[idx];
    }
    FileType& operator=(const FileType &rhs) {
        for (int i = 0; i < 4; ++i)
            (*this)[i] = rhs[i];
        return *this;
    }
};

namespace FileCode {
    const FileType      uninitialized("    ");
    const FileType      ships("SHIP");          // Ship database     
    const FileType      ship_classes("SCLS");   // ShipClass database
    const FileType      subsystems("SSYS");     // Sybsystem database
    const FileType      weapons("WEAP");        // Weapon database   
    const FileType      officers("OFFR");       // Officer database  
};

struct ChunkType {
    char                type[3];

    ChunkType(std::string code) {
        for (int i = 0; i < 3; ++i)
            type[i] = code[i];
    }
    ChunkType(const char* code) {
        for (int i = 0; i < 3; ++i)
            type[i] = code[i];
    }
};

struct MagicBytes {
    uint8_t             bytes[8] = {0xCA, 0x70, 0xCA, 0xFE, 0x53, 0x48, 0x49, 0x50};
};

namespace ChunkCode {
    const ChunkType     ship("SHP");            // Ship record`     
    const ChunkType     ship_class("CLS");      // ShipClass reco`abase
    const ChunkType     subsystem("SYS");       // Subsystem reco`abase
    const ChunkType     weapon("WPN");          // Weapon record`se   
    const ChunkType     officer("OFF");         // Officer record`ase  
};



struct FileHeader {
    MagicBytes          magic_bites;
    FileType            file_type;
    char                file_version;
    FileFlags           file_flags;
    int32_t             file_size;
    offset_t            index_offset;
    offset_t            data_offset;
 	char                header_padding[6] = {0};

    FileHeader():
        magic_bites(MagicBytes()),
        file_type(FileCode::uninitialized),
        file_version(1),
        file_flags(FileFlags::good),
        file_size(sizeof(FileHeader) + sizeof(IndexHeader) + 2),
        index_offset(sizeof(FileHeader)),
        data_offset(sizeof(FileHeader) + sizeof(IndexHeader)) { };

    FileHeader(FileType type):
        magic_bites(MagicBytes()),
        file_type(type),
        file_version(1),
        file_flags(FileFlags::good),
        file_size(sizeof(FileHeader) + sizeof(IndexHeader) + 2),
        index_offset(sizeof(FileHeader)),
        data_offset(sizeof(FileHeader) + sizeof(IndexHeader)) { };

    FileHeader(FileType type, int32_t size, offset_t index_offs, offset_t data_offs):
        magic_bites(MagicBytes()),
        file_type(type),
        file_version(1),
        file_flags(FileFlags::good),
        file_size(size),
        index_offset(index_offs),
        data_offset(data_offs) { };
};

struct IndexHeader {
    chunk_size_t        index_size;
    uint16_t            index_count;
    uint16_t            record_size;
    char                head_padding[2] = {0};

    IndexHeader():
        index_size(sizeof(IndexHeader)),
        index_count(0),
        record_size(sizeof(IndexEntry)) { };

    IndexHeader(uint16_t count):
        index_size(sizeof(IndexHeader) + sizeof(IndexEntry) * count),
        index_count(count),
        record_size(sizeof(IndexEntry)) { };
};

struct IndexEntry {
    index_t             chunk_index;
    chunk_size_t        chunk_size;
    offset_t            chunk_offset;

    IndexEntry(index_t index, chunk_size_t size, offset_t offset):
        chunk_index(index),
        chunk_size(size),
        chunk_offset(offset) { };
};

struct ChunkHeader {
    ChunkType           chunk_type;
    ChunkFlags          chunk_flags;
    chunk_size_t        chunk_size;
    index_t             chunk_index;
    offset_t            chunk_redirect;
};



#endif