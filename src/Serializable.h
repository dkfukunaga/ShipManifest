

#ifndef SERIALIZABLE_DATA_H
#define SERIALIZABLE_DATA_H

#include "DataFile.h"
#include "Headers.h"
#include <cstdint>

class Serializable {
public:
    virtual             ~Serializable() = default;
    virtual recsize_t   getSize() const = 0;

    void                serialize(DataFile &file, index_t index, offset_t offset) const;
    void                serialize(DataFile &file, index_t index, offset_t offset, int64_t pos) const;
    index_t             deserialize(DataFile &file);
    index_t             deserialize(DataFile &file, int64_t pos);
protected:
    virtual void        writeHeader(DataFile &file, index_t index, recsize_t size, offset_t offset) const = 0;
    virtual void        serializeData(DataFile &file) const = 0;
    virtual index_t     readHeader(DataFile &file) = 0;
    virtual void        deserializeData(DataFile &file) = 0;
};


inline void Serializable::serialize(DataFile &file, index_t index, offset_t offset) const {
    if (!file.isOpen()) {
        return;
    }

    writeHeader(file, index, getSize(), offset);
    serializeData(file);
}

inline void Serializable::serialize(DataFile &file, index_t index, offset_t offset, int64_t pos) const {
    if (!file.isOpen()) {
        return;
    }
    file.setWritePos(pos);

    serialize(file, index, offset);
}

inline index_t Serializable::deserialize(DataFile &file) {
    if (!file.isOpen()) {
        return 0;
    }

    index_t index = readHeader(file);
    deserializeData(file);

    return index;
}

inline index_t Serializable::deserialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return 0;
    }
    file.setReadPos(pos);

    return deserialize(file);
}


#endif