


#ifndef SHIP_TYPES_H
#define SHIP_TYPES_H



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
    unknown,
    union_of_earth,
    pacifica_free_states,
    federated_states_of_cobol,
    new_sumerian_ascendancy,
    vanaheim_alliance,
    shinwa_confederacy,
    sanbao_republic
};

// enum class ShipFTL : char {
//     system = 'S',
//     gate = 'G',
//     restricted = 'R',
//     unrestricted = 'U'
// };

// bool    operator<(const ShipFTL &lhs, const ShipFTL &rhs);
// bool    operator>(const ShipFTL &lhs, const ShipFTL &rhs);
// bool    operator<=(const ShipFTL &lhs, const ShipFTL &rhs);
// bool    operator>=(const ShipFTL &lhs, const ShipFTL &rhs);


enum class ShipFTL : unsigned char {
    system,
    gate,
    restricted,
    unrestricted
};

static const char ship_ftl_codes[] = { 'S', 'G', 'R', 'U' };

// enum class ShipType : char {
//     private_owner = 'C',
//     passenger = 'T',
//     merchant = 'F',
//     commercial = 'I',
//     exloratory = 'X',
//     goverment = 'V',
//     military = 'Z'
// };

// bool    operator<(const ShipType &lhs, const ShipType &rhs);
// bool    operator>(const ShipType &lhs, const ShipType &rhs);
// bool    operator<=(const ShipType &lhs, const ShipType &rhs);
// bool    operator>=(const ShipType &lhs, const ShipType &rhs);

enum class ShipType : unsigned char {
    private_owner,
    passenger,
    merchant,
    commercial,
    exloratory,
    goverment,
    military
};

static const char ship_type_codes[] = { 'C', 'T', 'F', 'I', 'X', 'V', 'Z' };


// weapon sizes
enum class WeaponSize {
    small   = 1,
    medium  = 2,
    large   = 3,
    missile
};


#endif