

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "DataFile.h"
#include "Headers.h"
#include <cstdint>

class Serializable {
public:
    virtual ~Serializable() = default;

    uint32_t            serialize(DataFile &file) const;
private:
    virtual uint32_t    serializeHeader(DataFile &file) const = 0;
    virtual uint32_t    serializeData(DataFile &file) const = 0;
};

uint32_t Serializable::serialize(DataFile &file) const {
    if (!file.isOpen()) {
        return 0;
    }

    uint32_t size = 0;

    size += serializeHeader(file);
    size += serializeData(file);

    return size;
}


#endif