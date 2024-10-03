
#include "Subsystem.h"


recsize_t   Subsystem::getSize() const {
    return 2 + name.length() + sizeof(tier) + sizeof(mass) + sizeof(durability) + sizeof(power);
}

void        Subsystem::writeHeader(DataFile &file, index_t index, recsize_t size, offset_t offset) const {
    file.write(&index);
    file.write(&size);
    file.write(&offset);
}

index_t     Subsystem::readHeader(DataFile &file) {
    DataRecordHeader tempHeader;

    while (true) {
        file.read(&tempHeader.index);
        file.read(&tempHeader.size);
        file.read(&tempHeader.redirect);
        if (tempHeader.redirect == 0 || tempHeader.redirect == file.getReadPos())
            break;
        else
            file.setWritePos(tempHeader.redirect);
    }

    return tempHeader.index;
}

void     Subsystem::serializeData(DataFile &file) const {
    file.write(name);
    file.write(&tier);
    file.write(&mass);
    file.write(&durability);
    file.write(&power);
}

void     Subsystem::deserializeData(DataFile &file) {
    file.read(name);
    file.read(&tier);
    file.read(&mass);
    file.read(&durability);
    file.read(&power);
}


recsize_t   Reactor::getSize() const {
    return Subsystem::getSize() + sizeof(fuel_use);
}

void        Reactor::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);
    file.write(&fuel_use);
}

void        Reactor::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);
    file.read(&fuel_use);
}



recsize_t   Thrusters::getSize() const {
    return Subsystem::getSize() + sizeof(speed) + sizeof(maneuver);
}

void        Thrusters::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);
    file.write(&speed);
    file.write(&maneuver);
}

void        Thrusters::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);
    file.read(&speed);
    file.read(&maneuver);
}



recsize_t   FTLdrive::getSize() const {
    return Subsystem::getSize() + sizeof(ftl_rating);
}

void        FTLdrive::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);
    file.write(&ftl_rating);
}

void        FTLdrive::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);
    file.read(&ftl_rating);
}




recsize_t   Computer::getSize() const {
    return Subsystem::getSize() + sizeof(processing_power) + sizeof(memory);
}

void        Computer::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);
    file.write(&processing_power);
    file.write(&memory);
}

void        Computer::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);
    file.read(&processing_power);
    file.read(&memory);
}



recsize_t   Armor::getSize() const {
    return Subsystem::getSize() + sizeof(armor_rating) + sizeof(hardness);
}

void        Armor::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);
    file.write(&armor_rating);
    file.write(&hardness);
}

void        Armor::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);
    file.read(&armor_rating);
    file.read(&hardness);
}



recsize_t   Shields::getSize() const {
    return Subsystem::getSize() + sizeof(damage_reduction) + sizeof(max_strength) + sizeof(recharge_rate);
}

void        Shields::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);
    file.write(&damage_reduction);
    file.write(&max_strength);
    file.write(&recharge_rate);
}

void        Shields::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);
    file.read(&damage_reduction);
    file.read(&max_strength);
    file.read(&recharge_rate);
}



