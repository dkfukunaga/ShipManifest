#include "Ship.h"

size_t Ship::serialize(void* buf) const {
    char* ptr = static_cast<char*>(buf);
    size_t offset = 0;

    // ship_id
    std::memcpy(ptr + offset, &ship_id, sizeof(ship_id));
    offset += sizeof(ship_id);

    // ship_name_len
    // consider verifying length and throwing exception if too long
    uint16_t ship_name_len = ship_name.length();
    std::memcpy(ptr + offset, &ship_name_len, sizeof(ship_name_len));
    offset += sizeof(ship_name_len);

    // ship_name
    std::memcpy(ptr + offset, ship_name.c_str(), ship_name_len);
    offset += ship_name_len;

    // ship_class_id
    std::memcpy(ptr + offset, &ship_class_id, sizeof(ship_class_id));
    offset += sizeof(ship_class_id);

    return offset;
}

size_t Ship::deserialize(const void* buf) {
    const char* ptr = static_cast<const char*>(buf);
    size_t offset = 0;

    // ship_id
    std::memcpy(&ship_id, ptr + offset, sizeof(ship_id));
    offset += sizeof(ship_id);

    // ship_name_len
    uint16_t ship_name_len;
    std::memcpy(&ship_name_len, ptr + offset, sizeof(ship_name_len));
    offset += sizeof(ship_name_len);

    // ship_name
    ship_name.assign(ptr + offset, ship_name_len);
    offset += ship_name_len;

    // ship_class_id
    std::memcpy(&ship_class_id, ptr + offset, sizeof(ship_class_id));
    offset += sizeof(ship_class_id);

    return offset;
}

size_t Ship::serialized_size() const {
    return sizeof(ship_id) + sizeof(uint16_t) + ship_name.length() + sizeof(ship_class_id);
}
