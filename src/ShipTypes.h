


#ifndef SHIP_TYPES_H
#define SHIP_TYPES_H

#include <string>

using namespace std;

enum class ShipSize : unsigned char {
    // unmanned
    drone           = 0,
    // solo pilot
    tiny_l          = 1,
    tiny_m          = 2,
    tiny_h          = 3,
    // small crew - shuttle sized
    small_l         = 4,
    small_m         = 5,
    small_h         = 6,
    // standard crew - light freighter sized
    standard_l      = 7,
    standard_m      = 8,
    standard_h      = 9,
    // corvettes
    corvette_l      = 10,
    corvette_m      = 11,
    corvette_h      = 12,
    // frigates
    frigate_l       = 13,
    frigate_m       = 14,
    frigate_h       = 15,
    // cruisers
    cruiser_l       = 16,
    cruiser_m       = 17,
    cruiser_h       = 18,
    // capital ships
    capital_l       = 19,
    capital_m       = 20,
    capital_h       = 21
};

enum class ShipFlagCode : unsigned char {
    union_of_earth = 1,
    pacifica_free_states = 2,
    federated_states_of_cobol = 3,
    new_sumerian_ascendancy = 4,
    vanaheim_alliance = 5,
    shinwa_confederacy = 6,
    sanbao_republic = 7
};

enum class ShipFTL : char {
    system = 'S',
    gate = 'G',
    restricted = 'R',
    unrestricted = 'U'
};

enum class ShipType : char {
    private_owner = 'C',
    passenger = 'T',
    merchant = 'F',
    commercial = 'I',
    exloratory = 'X',
    goverment = 'V',
    military = 'Z'
};


// weapon sizes
enum class WeaponSize {
    small   = 1,
    medium  = 2,
    large   = 3
};


#endif