



#ifndef COMPONENT_H
#define COMPONENT_H

#include "ShipTypes.h"
#include <string>



// Component base abstract class
class Component {
protected:
    std::string         m_name;
    char                m_tier;
    int                 m_mass;
    int                 m_power;

public:
    // getters
    std::string         getName() const;
    uchar               getTier() const;
    int                 getMass() const;
    int                 getPower() const;

    // setters
    void                setName(std::string name);
    void                setTier(uchar tier);
    void                setMass(int mass);
    void                setPower(int power);

    // operators
    bool                operator==(const Component &c) const;
    bool                operator!=(const Component &c) const;

    // virtual
    virtual void        use() = 0;

    // constructors
    Component(std::string name = "NONE", uchar tier = 'C', int mass = 0, int power = 0);
};

// *************** COMPONENT CLASSES ***************

class Reactor : public Component {
private:
    int             m_power_gen;
    int             m_fuel_rate;
    int             m_reliability;

public:
    // getters
    int             getPowerGen() const;
    int             getFuelRate() const;
    int             getReliability() const;

    // setters
    void            setPowerGen(int power_gen);
    void            setFuelRate(int fuel_rate);
    void            setReliability(int reliability);

    // operators
    bool            operator==(const Reactor &reliability) const;
    bool            operator!=(const Reactor &reliability) const;

    // virtual
    void            use() override;

    // constructors
    Reactor(std::string name = "NONE", uchar tier = 'C', int mass = 0, int power = 0,
        int power_gen = 0, int fuel_rate = 0, int reliability = 0);
    Reactor(Reactor &other);
};

class SubDrive : public Component {
private:
    int             m_accel;
    int             m_maneuver;
    int             m_speed;

public:
    // getters
    int             getAccel() const;
    int             getManeuver() const;
    int             getSpeed() const;

    // setters
    void            setAccel(int accel);
    void            setManeuver(int maneuver);
    void            setSpeed(int speed);

    // operators
    bool            operator==(const SubDrive &s) const;
    bool            operator!=(const SubDrive &s) const;

    // virtual override
    void            use() override;

    // constructors
    SubDrive(std::string name = "NONE", uchar tier = 'C', int mass = 0, int power = 0,
        int accel = 0, int maneuver = 0, int speed = 0);
    SubDrive(SubDrive &other);
};

class FTLDrive : public Component {
private:
    int             m_charge_rate;
    ShipSize        m_max_size;
    int             m_fuel_use;

public:
    // getters
    int             getChargeRate() const;
    std::string     getMaxSize() const;
    int             getFuelUse() const;

    // setters
    void            setChargeRate(int charge_rate);
    void            setMaxSize(ShipSize max_size);
    void            setFuelUse(int fuel_use);

    // operators
    bool            operator==(const FTLDrive &f) const;
    bool            operator!=(const FTLDrive &f) const;

    // virtual override
    void            use() override;

    // constructors
    FTLDrive(std::string name = "NONE", uchar tier = 'C', int mass = 0, int power = 0,
        int charge_rate = 0, ShipSize size = ShipSize::drone, int fuel_use = 0);
    FTLDrive(FTLDrive &other);
};

#endif