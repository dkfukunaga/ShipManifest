

#ifndef DATA_FILE_H
#define DATA_FILE_H

#include "DataFileHeaders.h"
#include <fstream>
#include <string>
#include <string.h>

class DataFile {
public:
    DataFile();
    DataFile(std::string file_name);
    ~DataFile();

    std::string         getFileName() const;
    void                setFileName(std::string file_name);
    bool                isOpen() const;
    bool                isInitialized() const;

    bool                open(std::string file_name);
    void                close();

    void                read(void *data, int size, long long pos);
    void                read(void *data, int size);
    void                read(std::string &str, long long pos);
    void                read(std::string &str);
    
    void                write(void *data, int size, long long pos);
    void                write(void *data, int size);
    void                write(std::string &str, long long pos);
    void                write(std::string &str);

    void                moveReadPointer(long long pos);
    void                moveWritePointer(long long pos);
private:
    std::fstream*       data_file_;
    std::string         file_name_;
    bool                is_initialized_;
};

#endif


// should probably implement wrappers for good(), fail(), bad(), clear(), set()
// maybe implement move constructor and overload operator=
// maybe implement swap()