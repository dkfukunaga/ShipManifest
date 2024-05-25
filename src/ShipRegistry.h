



#ifndef SHIP_REGISTRY_H
#define SHIP_REGISTRY_H


#include "ShipTypes.h"
#include <string>



class ShipFlag {
private:
    // private static member
    static const std::string flags[];
    // member variables
    ShipFlagCode    m_flag_code;

public:
    // getter
    ShipFlagCode    getFlagCode() const;
    std::string     getFlag() const;

    // setters
    void            setFlagCode(ShipFlagCode flag_code);
    void            setFlag(std::string flag);

    // // operators
    // bool            operator==(const ShipFlag &s) const;
    // bool            operator!=(const ShipFlag &s) const;
    // bool            operator<(const ShipFlag &s) const;
    // bool            operator>(const ShipFlag &s) const;
    // bool            operator<=(const ShipFlag &s) const;
    // bool            operator>=(const ShipFlag &s) const;

    // constructors
    ShipFlag(std::string flag);
    ShipFlag(ShipFlagCode flag_code);
    ShipFlag();
};

// store ship registry data and generate VIC std::string
// "FLG SZFT XXXX XXXX"
class ShipRegistry {
private:
    ShipFlagCode    m_ship_flag_code;   // 1-digit code
    ShipSize        m_ship_size;        // 2-digit code
    ShipFTL         m_ship_ftl;         // 1-letter code
    ShipType        m_ship_type;        // 1-letter code
    int             m_ship_uid;         // 8 digit unique id

public:
    // generate std::string of Vessel Identification Code
    std::string          getVIC() const;

    // getters
    ShipFlag        getShipFlag() const;
    ShipFTL         getShipFTL() const;
    ShipSize        getShipSize() const;
    ShipType        getShipType() const;
    int             getShipUID() const;

    // setters
    void            setShipFlag(ShipFlag flag_code);
    void            setShipFlag(ShipFlagCode flag);
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
    ShipRegistry(ShipFlagCode flag_code, ShipFTL ftl, ShipSize size, ShipType type, int uid);
    ShipRegistry();
};







#endif