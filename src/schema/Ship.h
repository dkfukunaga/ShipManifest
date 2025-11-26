#ifndef SHIP_MANIFEST_SHIP_H
#define SHIP_MANIFEST_SHIP_H

#include "Common.h"
#include <cstdint>
#include <string>
#include <cstring>

struct Ship {
    index_t         ship_id;
    std::string     ship_name;
    index_t         ship_class_id;
    uint32_t        ship_crew;

    size_t          serialize(void* buf) const;
    size_t          deserialize(const void* buf);
    size_t          serialized_size() const;
};

#endif