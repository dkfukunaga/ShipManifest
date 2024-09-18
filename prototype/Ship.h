

#ifndef SHIP_H
#define SHIP_H

#include "DataFile.h"
#include <string.h>
#include <cstdint>
#include <fstream>

struct Ship {
    long long       registry;
    std::string     name;
    uint8_t         size_class;
    int             speed;
    index_t         file_index;

    uint16_t        serialize(DataFile *file, long long pos);
    uint16_t        deserialize(DataFile *file, long long pos);
};



#endif

