


#ifndef DATABASE_H
#define DATABASE_H

#include "DataFileHeaders.h"
#include "DataFile.h"
#include "Ship.h"
#include <fstream>
#include <cstdint>




class Database {
public:
    Database();
    Database(std::string);
    ~Database();
private:
    static std::string  default_file_name_;
    static MagicBytes      default_magic_bytes_;
    static char         default_file_version_;
    static FileFlags    initial_file_flags_;
    static FileHeader   file_header_template_;
    static IndexHeader  empty_index_header_;
    static uint8_t      default_eof_[2];

    std::fstream*       database_;
    std::string         file_name_;
    long long           eof_offset;
    bool                openFile(std::string);
    bool                atEOF(int);
    void                moveWritePointer(long long);
    void                moveReadPointer(long long);
    void                write(void *, int, long long);
    void                write(void *, int);
    void                read(void *, int, long long);
    void                read(void *, int);
    void                initFile();
};




#endif