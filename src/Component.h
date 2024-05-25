



#ifndef COMPONENT_H
#define COMPONENT_H

#include "ShipTypes.h"
#include <string>



// Component base abstract class
class Component {
protected:
    std::string         name;
    char                tier;
    int                 mass;
    int                 power;

public:
    // getters
    std::string         getName() const;
    char                getTier() const;
    int                 getMass() const;
    int                 getPower() const;

    // setters
    void                setName(std::string nm);
    void                setTier(char tr);
    void                setMass(int m);
    void                setPower(int pow);

    // operators
    bool                operator==(const Component &c) const;
    bool                operator!=(const Component &c) const;

    // virtual
    virtual void        use() = 0;

    // constructors
    Component(std::string nm, char tr, int m, int p);
    Component();
};

// *************** COMPONENT CLASSES ***************

class Reactor : Component {
private:
    int             power_gen;
    int             fuel_rate;
    float           reliability;

public:
    // getters
    int             getPowerGen() const;
    int             getFuelRate() const;
    float           getReliability() const;

    // setters
    void            setPowerGen(int pg);
    void            setFuelRate(int fr);
    void            setReliability(float rel);

    // operators
    bool            operator==(const Reactor &r) const;
    bool            operator!=(const Reactor &r) const;

    // virtual
    void            use() override;

    // constructors
    Reactor(std::string nm, char tr, int m, int p, int pg, int fr, float r);
    Reactor(Reactor &other);
    Reactor();
};

class SubDrive : Component {
private:
    float           accel;
    int             maneuver;
    int             speed;

public:
    // getters
    float           getAccel() const;
    int             getManeuver() const;
    int             getSpeed() const;

    // setters
    void            setAccel(float acc);
    void            setManeuver(int manu);
    void            setSpeed(int spd);

    // operators
    bool            operator==(const SubDrive &s) const;
    bool            operator!=(const SubDrive &s) const;

    // virtual override
    void            use() override;

    // constructors
    SubDrive(std::string nm, char tr, int m, int p, float acc, int mn, int spd);
    SubDrive(SubDrive &other);
    SubDrive();
};

class FTLDrive : Component {
private:
    int             charge_rate;
    ShipSize        max_size;
    int             fuel_use;

public:
    // getters
    int             getChargeRate() const;
    ShipSize        getMaxSize() const;
    int             getFuelUse() const;

    // setters
    void            setChargeRate(int cr);
    void            setMaxSize(ShipSize ms);
    void            setFuelUse(int fu);

    // operators
    bool            operator==(const FTLDrive &f) const;
    bool            operator!=(const FTLDrive &f) const;

    // virtual override
    void            use() override;

    // constructors
    FTLDrive(std::string nm, char tr, int m, int p, int cr, ShipSize sz, int fu);
    FTLDrive(FTLDrive &other);
    FTLDrive();
};

#endif