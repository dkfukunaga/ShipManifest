


#ifndef SHIP_H
#define SHIP_H

#include "ShipClass.h"
#include <string>

using namespace std;


enum class ShipFlag;

class ShipRegistry {
public:
    string          getVINString() const;       // generate string of Vessel Identification Number
    long            getVINNum() const;          // generate nummber of Vessel Identification Number
    ShipFlag        getShipFlag() const;
    bool            isMilitary() const;
    ShipFlag        getShipType() const;
    bool            setShipFlag(string flag_code);
    bool            setShipFlag(ShipFlag flag);
    void            setIsMilitary(bool is_military);
    bool            setShipCategory(ShipCategory ship_type_code, bool is_military = false);
    int             generateShipUID();
private:
    short           m_ship_flag_code;   // 3 digit country code
    short           m_ship_type_code;   // 1 digit civilian/military
                                        // 3 digit ship type code
    int             m_ship_uid;         // 8 digit unique id
    bool            m_ship_uid_ok;      // bool to indicate uid has been checked
                                        // against database for duplicates
};

class Ship {
public:
    string          getName() const;
    string          getRegistryString() const;
    long            getRegistryNum() const;
    string          getCommander() const;
    string          getEngineer() const;
    ShipClass*      getShipClass() const;
    bool            setName(string name);
private:
    string          m_name;
    ShipRegistry    m_registry;
    string          m_commander;
    string          m_engineer;
    ShipClass*      m_ship_class;
};


#endif

