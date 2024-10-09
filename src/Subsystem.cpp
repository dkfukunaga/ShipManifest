
#include "Subsystem.h"


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



