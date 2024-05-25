


#include "ShipRegistry.h"
#include <string>

using namespace std;




// ShipFlag 3 letter codes
const string    ShipFlag::flags[] =    {"UNK",   // unknown
                                        "UOE",   // Union of Earth
                                        "PFS",   // Pacifica Free States
                                        "FSC",   // Federated States of Cobol
                                        "NSA",   // New Sumerican Ascandency
                                        "VAN",   // Vanheim Alliance
                                        "SWC",   // Shinwa Confederacy
                                        "SBR"};  // Sanbao Republic

// ********** SHIP FLAG ************

// getters
ShipFlagCode    ShipFlag::getFlagCode() const               { return flag_code; }
string          ShipFlag::getFlag() const                   { return flags[(int) flag_code]; }

// setters
void            ShipFlag::setFlagCode(ShipFlagCode fc)      { flag_code = fc; }
void            ShipFlag::setFlag(string f)                 {
    // check for valid 3 letter flag code
    if (f.length() == 3) {
        for (int i = 0; i < flags->length(); ++i) {
            if (flags[i] == f)
                flag_code = (ShipFlagCode) i;
        }
    }
    // if flag code not found
    flag_code = ShipFlagCode::unknown;
}

// string constructor
// searches flags array for matching 3 letter code
// assigns "UNK" if not found
ShipFlag::ShipFlag(string f) {
    // check for valid 3 letter flag code
    if (f.length() == 3) {
        for (int i = 0; i < flags->length(); ++i) {
            if (flags[i] == f)
                flag_code = (ShipFlagCode) i;
        }
    }
    // if flag code not found
    flag_code = ShipFlagCode::unknown;
}

// ShipFlagCode constructor
// assigns ShipFlag directly from ShipFlagCode
ShipFlag::ShipFlag(ShipFlagCode fc) {
    flag_code = fc;
}

// default constructor
// assigns "UNK"
ShipFlag::ShipFlag() {
    flag_code = ShipFlagCode::unknown;
}

// // operators
// bool            ShipFlag::operator==(const ShipFlag &s) const {
//     return flag_code == s.flag_code;
// }
// bool            ShipFlag::operator!=(const ShipFlag &s) const {
//     return !(*this == s);
// }
// bool            ShipFlag::operator<(const ShipFlag &s) const {
//     return flag_code< s.flag_code;
// }
// bool            ShipFlag::operator>(const ShipFlag &s) const {
//     return s < *this;
// }
// bool            ShipFlag::operator<=(const ShipFlag &s) const {
//     return *this < s || *this == s;
// }
// bool            ShipFlag::operator>=(const ShipFlag &s) const {
//     return *this > s || *this == s;
// }


// ********** SHIP REGISTRY ************

// return a formatted string of the VIC
// example: "UOE 04SC 1234 5678"
string ShipRegistry::getVIC() const {
    // raw c-string to hold VIC as it is built
    char raw_vic[19];

    // 3 letter flag code
    memcpy(raw_vic, this->getShipFlag().getFlag().c_str(), 3);
    // space
    raw_vic[3] = ' ';

    // ship size
    raw_vic[4] = ((int) ship_size / 10) + 48;
    raw_vic[5] = ((int) ship_size % 10) + 48;
    // ship ftl class code
    raw_vic[6] = ShipFTLCodes[(int) ship_ftl];
    // ship type code
    raw_vic[7] = ShipTypeCodes[(int) ship_type];
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
ShipFlag        ShipRegistry::getShipFlag() const           {
    ShipFlag flag(ship_flag_code);
    return flag;
}

ShipFTL         ShipRegistry::getShipFTL() const            { return ship_ftl; }
ShipSize        ShipRegistry::getShipSize() const           { return ship_size; }
ShipType        ShipRegistry::getShipType() const           { return ship_type; }
int             ShipRegistry::getShipUID() const            { return ship_uid; }


// setters
void            ShipRegistry::setShipFlag(ShipFlag fc)      { ship_flag_code = fc.getFlagCode(); }
void            ShipRegistry::setShipFlag(ShipFlagCode f)   { ship_flag_code = f; }
void            ShipRegistry::setShipFTL(ShipFTL ftl)       { ship_ftl = ftl; }
void            ShipRegistry::setShipSize(ShipSize size)    { ship_size = size; }
void            ShipRegistry::setShipType(ShipType type)    { ship_type = type; }
void            ShipRegistry::setShipUID(int uid)           { ship_uid = uid; }


// operators
bool            ShipRegistry::operator==(const ShipRegistry &s) const {
    return  this->ship_uid == s.ship_uid &&
            this->ship_type == s.ship_type &&
            this->ship_ftl == s.ship_ftl &&
            this->ship_size == s.ship_size &&
            this->ship_flag_code == s.ship_flag_code;
}
bool            ShipRegistry::operator!=(const ShipRegistry &s) const {
    return !(*this == s);
}
bool            ShipRegistry::operator<(const ShipRegistry &s) const {
    if (this->ship_flag_code < s.ship_flag_code)
        return true;
    if (this->ship_size < s.ship_size)
        return true;
    if (this->ship_ftl < s.ship_ftl)
        return true;
    if (this->ship_type < s.ship_type)
        return true;
    if (this->ship_uid < s.ship_uid)
        return true;
    // else return false
    return false;
}
bool            ShipRegistry::operator>(const ShipRegistry &s) const {
    return s < *this;
}
bool            ShipRegistry::operator<=(const ShipRegistry &s) const {
    return *this < s || *this == s;
}
bool            ShipRegistry::operator>=(const ShipRegistry &s) const {
    return *this > s || *this == s;
}


// constructors
ShipRegistry::ShipRegistry(ShipFlagCode flag_code, ShipFTL ftl, ShipSize size, ShipType type, int uid) :
    ship_flag_code(flag_code),
    ship_ftl(ftl),
    ship_size(size),
    ship_type(type),
    ship_uid(uid) { }

