#include "ShipClass.h"

size_t ShipClass::serialize(void* buf) const {
    char* ptr = static_cast<char*>(buf);
    size_t offset = 0;

    // class_id
    std::memcpy(ptr + offset, &class_id, sizeof(class_id));
    offset += sizeof(class_id);

    // class_name_len
    uint16_t class_name_len = class_name.length();
    std::memcpy(ptr + offset, &class_name_len, sizeof(class_name_len));
    offset += sizeof(class_name_len);

    // class_name
    std::memcpy(ptr + offset, class_name.c_str(), class_name_len);
    offset += class_name_len;

    // class_crew
    std::memcpy(ptr + offset, &class_crew, sizeof(class_crew));
    offset += sizeof(class_crew);

    // ship_type
    std::memcpy(ptr + offset, &class_type, sizeof(class_type));
    offset += sizeof(class_type);

    return offset;
}

size_t ShipClass::deserialize(const void* buf) {
    const char* ptr = static_cast<const char*>(buf);
    size_t offset = 0;

    // class_id
    std::memcpy(&class_id, ptr + offset, sizeof(class_id));
    offset += sizeof(class_id);

    // class_name_len
    uint16_t class_name_len;
    std::memcpy(&class_name_len, ptr + offset, sizeof(class_name_len));
    offset += sizeof(class_name_len);

    // class_name
    class_name.assign(ptr + offset, class_name_len);
    offset += class_name_len;

    // class_crew
    std::memcpy(&class_crew, ptr + offset, sizeof(class_crew));
    offset += sizeof(class_crew);

    // ship_type
    std::memcpy(&class_type, ptr + offset, sizeof(class_type));
    offset += sizeof(class_type);

    return offset;
}

size_t ShipClass::serialized_size() const {
    return sizeof(class_id) + sizeof(uint16_t) + class_name.length()
         + sizeof(class_crew) + sizeof(class_type);
}
