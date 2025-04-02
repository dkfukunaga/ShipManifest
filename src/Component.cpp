
#include "Component.h"

recsize_t   Component::getSize() const {
    return 2 + name.length() + sizeof(tier) + sizeof(mass) + sizeof(durability) + sizeof(power);
}

void        Component::writeHeader(DataFile &file, index_t index, recsize_t size, offset_t redirect) const {
    file.write(&index);
    file.write(&size);
    file.write(&redirect);
}

index_t     Component::readHeader(DataFile &file) {
    DataRecordHeader tempHeader;

    while (true) {
        file.read(&tempHeader.index);
        file.read(&tempHeader.size);
        file.read(&tempHeader.redirect);
        if (tempHeader.index == 0 && tempHeader.redirect != 0)
            file.setWritePos(tempHeader.redirect);
        else
            break;
            
    }

    return tempHeader.index;
}

void     Component::serializeData(DataFile &file) const {
    file.write(name);
    file.write(&tier);
    file.write(&mass);
    file.write(&durability);
    file.write(&power);
}

void     Component::deserializeData(DataFile &file) {
    file.read(name);
    file.read(&tier);
    file.read(&mass);
    file.read(&durability);
    file.read(&power);
}
