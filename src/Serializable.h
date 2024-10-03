

#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "DataFile.h"
#include "Headers.h"
#include <cstdint>

class Serializable {
public:
    virtual ~Serializable() = default;

    uint32_t            serialize(DataFile &file) const;
    uint32_t            serialize(DataFile &file, int64_t pos) const;
    void                deserialize(DataFile &file);
    void                deserialize(DataFile &file, int64_t pos);
private:
    virtual uint32_t    writeHeader(DataFile &file) const = 0;
    virtual uint32_t    serializeData(DataFile &file) const = 0;
    virtual void        readHeader(DataFile &file) = 0;
    virtual void        deserializeData(DataFile &file) = 0;
};

uint32_t Serializable::serialize(DataFile &file) const {
    if (!file.isOpen()) {
        return 0;
    }

    uint32_t size = 0;

    size += writeHeader(file);
    size += serializeData(file);

    return size;
}

uint32_t Serializable::serialize(DataFile &file, int64_t pos) const {
    if (!file.isOpen()) {
        return 0;
    }
    file.setWritePos(pos);

    return serialize(file);
}

void Serializable::deserialize(DataFile &file) {
    if (!file.isOpen()) {
        return;
    }

    readHeader(file);
    deserializeData(file);
}

void Serializable::deserialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return;
    }
    file.setReadPos(pos);

    deserialize(file);
}


#endif