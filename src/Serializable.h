
#pragma once
#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "..\DataFile\src\DataFile.h"
#include "FileFormat.h"
#include <cstdint>

class Serializable {
public:
    virtual             ~Serializable() = default;
    virtual uint32_t    getSize() const = 0;

    virtual uint32_t    serialize(DataFile &file) const = 0;
    virtual bool        deserialize(DataFile &file) = 0;
};



#endif