#include "Weapon.h"


recsize_t   Weapon::getSize() const {
    return Subsystem::getSize() + sizeof(size_class) + sizeof(damage_type) + sizeof(damage) + sizeof(range);
}

void        Weapon::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);
    file.write(&size_class);
    file.write(&damage_type);
    file.write(&damage);
    file.write(&range);
}

void        Weapon::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);
    file.read(&size_class);
    file.read(&damage_type);
    file.read(&damage);
    file.read(&range);
}





recsize_t   MassDriver::getSize() const {
    return Weapon::getSize() + sizeof(velocity) + sizeof(ammo_capacity);
}

void        MassDriver::serializeData(DataFile &file) const {
    Weapon::serializeData(file);
    file.write(&velocity);
    file.write(&ammo_capacity);
}

void        MassDriver::deserializeData(DataFile &file) {
    Weapon::deserializeData(file);
    file.read(&velocity);
    file.read(&ammo_capacity);
}


recsize_t   Beam::getSize() const {
    return Weapon::getSize() + sizeof(shield_penetration) + sizeof(range_penalty) + sizeof(capacitor_charge);
}

void        Beam::serializeData(DataFile &file) const {
    Weapon::serializeData(file);
    file.write(&shield_penetration);
    file.write(&range_penalty);
    file.write(&capacitor_charge);
}

void        Beam::deserializeData(DataFile &file) {
    Weapon::deserializeData(file);
    file.read(&shield_penetration);
    file.read(&range_penalty);
    file.read(&capacitor_charge);
}


recsize_t   Missile::getSize() const {
    return Weapon::getSize() + sizeof(velocity) + sizeof(evasion) + sizeof(tracking);
}

void        Missile::serializeData(DataFile &file) const {
    Weapon::serializeData(file);
    file.write(&velocity);
    file.write(&evasion);
    file.write(&tracking);
}

void        Missile::deserializeData(DataFile &file) {
    Weapon::deserializeData(file);
    file.read(&velocity);
    file.read(&evasion);
    file.read(&tracking);
}