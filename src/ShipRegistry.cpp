


#include "ShipRegistry.h"
#include <string>

using namespace std;


// ********** ENUMS ************

enum class ShipFlagCode : unsigned char {
    union_of_earth = 1,
    pacifica_free_states = 2,
    federated_states_of_cobol = 3,
    new_sumerian_ascendancy = 4,
    vanaheim_alliance = 5,
    shinwa_confederacy = 6,
    sanbao_republic = 7
};

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

// ShipFlag 3 letter codes
const string ShipFlag::flags[] =    {"UNK",   // unknown
                                     "UOE",   // Union of Earth
                                     "PFS",   // Pacifica Free States
                                     "FSC",   // Federated States of Cobol
                                     "NSA",   // New Sumerican Ascandency
                                     "VAN",   // Vanheim Alliance
                                     "SWC",   // Shinwa Confederacy
                                     "SBR"};  // Sanbao Republic

// ********** SHIP FLAG ************

ShipFlagCode ShipFlag::getFlagCode() const { return (ShipFlagCode) index; }

// string constructor
// searches flags array for matching 3 letter code
// assigns "UNK" if not found
ShipFlag::ShipFlag(string flag) {
    // check for valid 3 letter flag code
    if (flag.length() == 3) {
        for (int i = 0; i < flags->length(); ++i) {
            if (flags[i] == flag)
                flag = flags[i];
                index = i;
        }
    }
    // if flag code not found
    if (flag.empty())
        flag = flags[0];
        index = 0;
}

// ShipFlagCode constructor
// assigns ShipFlag directly from ShipFlagCode
ShipFlag::ShipFlag(ShipFlagCode flag_code) {
    flag = flags[(int) flag_code];
}

// default constructor
// assigns "UNK"
ShipFlag::ShipFlag() {
    flag = flags[0];
}


// ********** SHIP REGISTRY ************

// return a formatted string of the VIC
// example: "UOE 04SC 1234 5678"
string ShipRegistry::getVIC() const {
    // raw c-string to hold VIC as it is built
    char raw_vic[19];

    // 3 letter flag code
    memcpy(raw_vic, this->getShipFlag().flag.c_str(), 3);
    // space
    raw_vic[3] = ' ';

    // ship size
    raw_vic[4] = ((int) ship_size / 10) + 48;
    raw_vic[5] = ((int) ship_size % 10) + 48;
    // ship ftl class code
    raw_vic[6] = (char) ship_ftl;
    // ship type code
    raw_vic[7] = (char) ship_type;
    // space
    raw_vic[8] = ' ';

    // first 4 digits of uid
    int digit = 10000000;
    for (int i = 9; i <= 12; ++i) {
        raw_vic[i] = ((ship_uid / digit) % 10) + 48;
        digit /= 10;
    }
    // space
    raw_vic[13] = ' ';

    // last 4 digits of uid
    for (int i = 14; i <= 17; ++i) {
        raw_vic[i] = ((ship_uid / digit) % 10) + 48;
        digit /= 10;
    }
    raw_vic[19] = '\0';

    return string(raw_vic);
}


// getters
ShipFlag ShipRegistry::getShipFlag() const {
    ShipFlag flag(ship_flag_code);
    return flag;
}

ShipFTL ShipRegistry::getShipFTL() const { return ship_ftl; }

ShipSize ShipRegistry::getShipSize() const { return ship_size; }

ShipType ShipRegistry::getShipType() const { return ship_type; }

int ShipRegistry::getShipUID() const { return ship_uid; }


// setters
void ShipRegistry::setShipFlag(ShipFlag flag_code) {
    ship_flag_code = flag_code.getFlagCode();
}

void ShipRegistry::setShipFlag(ShipFlagCode flag) {
    ship_flag_code = flag;
}

void ShipRegistry::setShipFTL(ShipFTL ftl) {
    ship_ftl = ftl;
}

void ShipRegistry::setShipSize(ShipSize size) {
    ship_size = size;
}

void ShipRegistry::setShipType(ShipType type) {
    ship_type = type;
}

void ShipRegistry::setShipUID(int uid) {
    ship_uid = uid;
}


// constructors
ShipRegistry::ShipRegistry(ShipFlagCode flag_code, ShipFTL ftl, ShipSize size, ShipType type, int uid) :
    ship_flag_code(flag_code),
    ship_ftl(ftl),
    ship_size(size),
    ship_type(type),
    ship_uid(uid) { }

