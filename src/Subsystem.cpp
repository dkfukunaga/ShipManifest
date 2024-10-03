
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

}

void        Reactor::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);

}



recsize_t   Thrusters::getSize() const {
    return Subsystem::getSize() + sizeof(speed) + sizeof(maneuver);
}

void        Thrusters::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);

}

void        Thrusters::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);

}



recsize_t   FTLdrive::getSize() const {
    return Subsystem::getSize() + sizeof(ftl_rating);
}

void        FTLdrive::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);

}

void        FTLdrive::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);

}




recsize_t   Computer::getSize() const {
    return Subsystem::getSize() + sizeof(processing_power) + sizeof(memory);
}

void        Computer::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);

}

void        Computer::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);

}



recsize_t   Armor::getSize() const {
    return Subsystem::getSize() + sizeof(armor_rating) + sizeof(hardness);
}

void        Armor::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);

}

void        Armor::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);

}



recsize_t   Shields::getSize() const {
    return Subsystem::getSize() + sizeof(damage_reduction) + sizeof(max_strength) + sizeof(recharge_rate);
}

void        Shields::serializeData(DataFile &file) const {
    Subsystem::serializeData(file);

}

void        Shields::deserializeData(DataFile &file) {
    Subsystem::deserializeData(file);

}



