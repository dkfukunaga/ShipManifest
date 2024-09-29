

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "DataFile.h"
#include "Headers.h"
#include <cstdint>

class Serializable {
public:
    uint32_t            serialize() const;
    void                setFile(DataFile &file);
protected:
    DataFile&           data_file_;
private:
    virtual uint32_t    serializeHeader() const = 0;
    virtual uint32_t    serializeData() const = 0;
};

uint32_t Serializable::serialize() const {
    uint32_t size = 0;

    size += serializeHeader();
    size += serializeData();

    return size;
}

void Serializable::setFile(DataFile &file) { data_file_ = file; }


#endif