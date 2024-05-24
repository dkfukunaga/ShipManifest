



#ifndef COMPONENT_H
#define COMPONENT_H

#include "ShipTypes.h"
#include <string>

using namespace std;


// Component base abstract class
class Component {
protected:
    string              name;
    char                tier;
    int                 mass;
    int                 power;
public:
    string              getName() const;
    char                getTier() const;
    int                 getMass() const;
    int                 getPower() const;
    void                setName(string nm);
    void                setTier(char tr);
    void                setMass(int m);
    void                setPower(int pow);
    virtual void        use() = 0;
};

// *************** COMPONENT CLASSES ***************

class Reactor : Component {
private:
    int             power_gen;
    int             fuel_rate;
    float           reliability;
public:
    int             getPowerGen() const;
    int             getFuelRate() const;
    float           getReliability() const;
    void            setPowerGen(int pg);
    void            setFuelRate(int fr);
    void            setReliability(float rel);
    void            use() override;
};

class SubDrive : Component {
private:
    float           accel;
    int             maneuver;
    int             speed;
public:
    float           getAccel() const;
    int             getManeuver() const;
    int             getSpeed() const;
    void            setAccel(float acc);
    void            setManeuver(int manu);
    void            setSpeed(int spd);
    void            use() override;
};

class FTLDrive : Component {
private:
    int             charge_rate;
    ShipSize        max_size;
    int             fuel_use;
public:
    int             getChargeRate() const;
    ShipSize        getMaxSize() const;
    int             getFuelUse() const;
    void            setChargeRate(int cr);
    void            setMaxSize(ShipSize ms);
    void            setFuelUse(int fu);
    void            use() override;
};

#endif