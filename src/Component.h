
#ifndef COMPONENT_H
#define COMPONENT_H



#include "..\DataFile\src\DataFile.h"
#include "DataRecord.h"
#include <string>
#include <cstdint>


struct Component : DataRecord {
    std::string         name            = "NONAME";
    uint8_t             tier            = 0;
    uint16_t            mass            = 0;
    uint16_t            durability      = 0;
    int32_t             power           = 0;

    Component() = delete;
    Component(RecordType new_type):
        DataRecord(new_type) { };
    Component(RecordType new_type, std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power):
        DataRecord(new_type),
        name(new_name),
        tier(new_tier),
        mass(new_mass),
        durability(new_dur),
        power(new_power) { };
    Component(const Component &) = default;             // default copy constructor
    Component(Component &&) noexcept = default;         // default move construtor
    virtual ~Component() = default;                     // default virtual destructor

    recsize_t           getSize() const;
protected:
    void                writeHeader(DataFile &file, index_t index, recsize_t size, offset_t offset) const;
    index_t             readHeader(DataFile &file);
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};



#endif