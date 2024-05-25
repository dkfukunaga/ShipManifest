



#ifndef SHIP_REGISTRY_H
#define SHIP_REGISTRY_H


#include "ShipTypes.h"
#include <string>


using namespace std;


class ShipFlag {
private:
    // private static member
    static const string         flags[];
    // member variables
    ShipFlagCode    flag_code;

public:
    // getter
    ShipFlagCode    getFlagCode() const;
    string          getFlag() const;

    // setters
    void            setFlagCode(ShipFlagCode fc);
    void            setFlag(string f);

    // // operators
    // bool            operator==(const ShipFlag &s) const;
    // bool            operator!=(const ShipFlag &s) const;
    // bool            operator<(const ShipFlag &s) const;
    // bool            operator>(const ShipFlag &s) const;
    // bool            operator<=(const ShipFlag &s) const;
    // bool            operator>=(const ShipFlag &s) const;

    // constructors
    ShipFlag(string f);
    ShipFlag(ShipFlagCode fc);
    ShipFlag();
};

// store ship registry data and generate VIC string
// "FLG SZFT XXXX XXXX"
class ShipRegistry {
private:
    ShipFlagCode    ship_flag_code;     // 1-digit code
    ShipSize        ship_size;          // 2-digit code
    ShipFTL         ship_ftl;           // 1-letter code
    ShipType        ship_type;          // 1-letter code
    int             ship_uid;           // 8 digit unique id

public:
    // generate string of Vessel Identification Code
    string          getVIC() const;

    // getters
    ShipFlag        getShipFlag() const;
    ShipFTL         getShipFTL() const;
    ShipSize        getShipSize() const;
    ShipType        getShipType() const;
    int             getShipUID() const;

    // setters
    void            setShipFlag(ShipFlag fc);
    void            setShipFlag(ShipFlagCode f);
    void            setShipFTL(ShipFTL ftl);
    void            setShipSize(ShipSize size);
    void            setShipType(ShipType type);
    void            setShipUID(int uid);

    // operators
    bool            operator==(const ShipRegistry &s) const;
    bool            operator!=(const ShipRegistry &s) const;
    bool            operator<(const ShipRegistry &s) const;
    bool            operator>(const ShipRegistry &s) const;
    bool            operator<=(const ShipRegistry &s) const;
    bool            operator>=(const ShipRegistry &s) const;

    // constructors
    ShipRegistry(ShipFlagCode fc, ShipFTL ftl, ShipSize size, ShipType type, int uid);
    ShipRegistry();
};







#endif