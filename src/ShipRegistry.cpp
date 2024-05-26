


#include "ShipTypes.h"
#include "ShipRegistry.h"
#include <string>


// ShipFlag 3 letter codes
const std::string   ShipFlag::flags[] =    {"UNK",   // unknown
                                            "UOE",   // Union of Earth
                                            "PFS",   // Pacifica Free States
                                            "FSC",   // Federated States of Cobol
                                            "NSA",   // New Sumerican Ascandency
                                            "VAN",   // Vanheim Alliance
                                            "SWC",   // Shinwa Confederacy
                                            "SBR"};  // Sanbao Republic

// ********** SHIP FLAG ************

// getters
ShipFlagCode    ShipFlag::getFlagCode() const                 { return m_flag_code; }
std::string     ShipFlag::getFlag() const                     { return flags[(int) m_flag_code]; }

// setters
void            ShipFlag::setFlagCode(ShipFlagCode flag_code) { m_flag_code = flag_code; }
void            ShipFlag::setFlag(std::string flag)           {
    // check for valid 3 letter flag code
    if (flag.length() == 3) {
        for (int i = 0; i < flags->length(); ++i) {
            if (flags[i] == flag)
                m_flag_code = (ShipFlagCode) i;
        }
    }
    // if flag code not found
    m_flag_code = ShipFlagCode::unknown;
}

// std::string constructor
// searches flags array for matching 3 letter code
// assigns "UNK" if not found
ShipFlag::ShipFlag(std::string flag) {
    // check for valid 3 letter flag code
    if (flag.length() == 3) {
        for (int i = 0; i < flags->length(); ++i) {
            if (flags[i] == flag)
                m_flag_code = (ShipFlagCode) i;
        }
    }
    // if flag code not found
    m_flag_code = ShipFlagCode::unknown;
}

// ShipFlagCode constructor
// assigns ShipFlag directly from ShipFlagCode
ShipFlag::ShipFlag(ShipFlagCode flag_code) {
    m_flag_code = flag_code;
}

// default constructor
// assigns "UNK"
ShipFlag::ShipFlag() {
    m_flag_code = ShipFlagCode::unknown;
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

// return a formatted std::string of the VIC
// example: "UOE 04SC 1234 5678"
std::string ShipRegistry::getVIC() const {
    // raw c-std::string to hold VIC as it is built
    char raw_vic[19];

    // 3 letter flag code
    memcpy(raw_vic, this->getShipFlag().getFlag().c_str(), 3);
    // space
    raw_vic[3] = ' ';

    // ship size
    raw_vic[4] = ((int) m_ship_size / 10) + 48;
    raw_vic[5] = ((int) m_ship_size % 10) + 48;
    // ship ftl class code
    raw_vic[6] = ship_ftl_codes[(int) m_ship_ftl];
    // ship type code
    raw_vic[7] = ship_type_codes[(int) m_ship_type];
    // space
    raw_vic[8] = ' ';

    // first 4 digits of uid
    int digit = 10000000;
    for (int i = 9; i <= 12; ++i) {
        raw_vic[i] = ((m_ship_uid / digit) % 10) + 48;
        digit /= 10;
    }
    // space
    raw_vic[13] = ' ';

    // last 4 digits of uid
    for (int i = 14; i <= 17; ++i) {
        raw_vic[i] = ((m_ship_uid / digit) % 10) + 48;
        digit /= 10;
    }
    raw_vic[19] = '\0';

    return std::string(raw_vic);
}


// getters
ShipFlag        ShipRegistry::getShipFlag() const           {
    ShipFlag flag(m_ship_flag_code);
    return flag;
}

ShipFTL         ShipRegistry::getShipFTL() const            { return m_ship_ftl; }
ShipSize        ShipRegistry::getShipSize() const           { return m_ship_size; }
ShipType        ShipRegistry::getShipType() const           { return m_ship_type; }
int             ShipRegistry::getShipUID() const            { return m_ship_uid; }


// setters
void            ShipRegistry::setShipFlag(ShipFlag flag_code) { m_ship_flag_code = flag_code.getFlagCode(); }
void            ShipRegistry::setShipFlag(ShipFlagCode flag)  { m_ship_flag_code = flag; }
void            ShipRegistry::setShipFTL(ShipFTL ftl)         { m_ship_ftl = ftl; }
void            ShipRegistry::setShipSize(ShipSize size)      { m_ship_size = size; }
void            ShipRegistry::setShipType(ShipType type)      { m_ship_type = type; }
void            ShipRegistry::setShipUID(int uid)             { m_ship_uid = uid; }


// operators
bool            ShipRegistry::operator==(const ShipRegistry &s) const {
    return  this->m_ship_uid == s.m_ship_uid &&
            this->m_ship_type == s.m_ship_type &&
            this->m_ship_ftl == s.m_ship_ftl &&
            this->m_ship_size == s.m_ship_size &&
            this->m_ship_flag_code == s.m_ship_flag_code;
}
bool            ShipRegistry::operator!=(const ShipRegistry &s) const {
    return !(*this == s);
}
bool            ShipRegistry::operator<(const ShipRegistry &s) const {
    if (this->m_ship_flag_code < s.m_ship_flag_code)
        return true;
    if (this->m_ship_size < s.m_ship_size)
        return true;
    if (this->m_ship_ftl < s.m_ship_ftl)
        return true;
    if (this->m_ship_type < s.m_ship_type)
        return true;
    if (this->m_ship_uid < s.m_ship_uid)
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
ShipRegistry::ShipRegistry(ShipFlagCode flag_code, ShipFTL ftl, ShipSize size,
        ShipType type, int uid) :
    m_ship_flag_code(flag_code),
    m_ship_ftl(ftl),
    m_ship_size(size),
    m_ship_type(type),
    m_ship_uid(uid) { }

// ShipRegistry::ShipRegistry() :
//     m_ship_flag_code(ShipFlagCode::union_of_earth),
//     m_ship_ftl(ShipFTL::system),
//     m_ship_size(ShipSize::drone),
//     m_ship_type(ShipType::private_owner),
//     m_ship_uid(0) { }
