#ifndef SHIP_MANIFEST_SHIP_CLASS_H
#define SHIP_MANIFEST_SHIP_CLASS_H

#include "Common.h"
#include <cstdint>
#include <string>
#include <cstring>

struct ShipClass {
    index_t         class_id;
    std::string     class_name;
    uint32_t        class_crew;
    ShipType        class_type;

    size_t          serialize(void* buf) const;
    size_t          deserialize(const void* buf);
    size_t          serialized_size() const;
};

#endif