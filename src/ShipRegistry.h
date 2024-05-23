



#ifndef SHIP_REGISTRY_H
#define SHIP_REGISTRY_H


#include <string>


using namespace std;

enum class ShipFlagCode;
enum class ShipSize;
enum class ShipFTL;
enum class ShipType;

struct ShipFlag {
private:
    // private static member
    static const string         flags[];
    int             index;
public:
    // member variable
    string          flag;
    // getter
    ShipFlagCode    getFlagCode() const;
    // constructors
    ShipFlag(string flag);
    ShipFlag(ShipFlagCode flag_code);
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
    void            setShipFlag(ShipFlag flag_code);
    void            setShipFlag(ShipFlagCode flag);
    void            setShipFTL(ShipFTL ftl);
    void            setShipSize(ShipSize size);
    void            setShipType(ShipType type);
    void            setShipUID(int uid);

    // constructors
    ShipRegistry(ShipFlagCode flag_code, ShipFTL ftl, ShipSize size, ShipType type, int uid);
};







#endif