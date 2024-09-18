

#include "Ship.h"

// serializes Ship data and writes to file
//
// returns number of bytes written
//
// NEEDS TO BE REWRITTEN TO USE Database FUNCTIONS INSTEAD OF DataFile DIRECTLY
// I THINK
uint16_t Ship::serialize(DataFile *file, const long long pos) {
    // check if file is open
    if (!file->isOpen())
        return 0;
    
    uint16_t chunk_size = 0;

    file->write(&registry, sizeof(registry), pos);
    file->write(name);
    file->write(&size_class, sizeof(size_class));
    file->write(&speed, sizeof(speed));


    return chunk_size;
}

// deserializes Ship data from file and assigns to struct members
//
// returns number of bytes read
uint16_t Ship::deserialize(DataFile *file, const index_t index) {
    // check if file is open
    if (!*file || !file->is_open())
        return 0;
    
    uint16_t chunk_size = 0;

    read(file, &registry, sizeof(registry), chunk_size);
    read(file, name, chunk_size);
    read(file, &size_class, sizeof(size_class), chunk_size);
    read(file, &speed, sizeof(speed), chunk_size);

    file_index = index;
    
    return chunk_size;
}