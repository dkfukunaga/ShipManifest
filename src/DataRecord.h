

#ifndef DATA_FILE_RECORD_H
#define DATA_FILE_RECORD_H

#include "..\DataFile\src\DataFile.h"
#include "Headers.h"
#include <cstdint>

enum class RecordType {
    subsystem,
    weapon,
    officer,
};

struct DataRecord {
    RecordType          type;

    DataRecord() = default;
    explicit DataRecord(RecordType new_type):
        type(new_type) { };

    virtual             ~DataRecord() = default;
    virtual recsize_t   getSize() const = 0;

    offset_t            serialize(DataFile &file, index_t index, offset_t redirect) const;
    offset_t            serialize(DataFile &file, index_t index, offset_t redirect, int64_t pos) const;
    index_t             deserialize(DataFile &file);
    index_t             deserialize(DataFile &file, int64_t pos);
protected:
    virtual void        writeHeader(DataFile &file, index_t index, recsize_t size, offset_t redirect) const = 0;
    virtual void        serializeData(DataFile &file) const = 0;
    virtual index_t     readHeader(DataFile &file) = 0;
    virtual void        deserializeData(DataFile &file) = 0;
};


inline offset_t DataRecord::serialize(DataFile &file, index_t index, offset_t redirect) const {
    if (!file.isOpen()) {
        return 0;
    }

    offset_t record_offset = file.getWritePos();

    writeHeader(file, index, getSize(), redirect);
    serializeData(file);
    
    return record_offset;
}

inline offset_t DataRecord::serialize(DataFile &file, index_t index, offset_t redirect, int64_t pos) const {
    if (!file.isOpen()) {
        return 0;
    }
    file.setWritePos(pos);

    return serialize(file, index, redirect);
}

inline index_t DataRecord::deserialize(DataFile &file) {
    if (!file.isOpen()) {
        return 0;
    }

    index_t index = readHeader(file);
    deserializeData(file);

    return index;
}

inline index_t DataRecord::deserialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return 0;
    }
    file.setReadPos(pos);

    return deserialize(file);
}


#endif