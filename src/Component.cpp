


#include "Component.h"
#include <typeinfo>

using namespace std;


// *************** COMPONENT BASE CLASS ***************

// getters
string      Component::getName() const          { return name; }
char        Component::getTier() const          { return tier; }
int         Component::getMass() const          { return mass; }
int         Component::getPower() const         { return power; }

// setters
void        Component::setName(string nm)       { name = nm; }
void        Component::setTier(char tr)         { tier = tr; }
void        Component::setMass(int m)           { mass = m; }
void        Component::setPower(int pow)        { power = pow; }

// operator overload
bool        Component::operator==(const Component &c) const {
    return this->name == c.name &&
           this->tier == c.tier &&
           this->mass == c.mass &&
           this->power == c.power;
}
bool        Component::operator!=(const Component &c) const {
    return !(*this == c);
}


// *************** REACTOR ***************

// getters
int         Reactor::getPowerGen() const        { return power_gen; }
int         Reactor::getFuelRate() const        { return fuel_rate; }
float       Reactor::getReliability() const     { return reliability; }

// setters
void        Reactor::setPowerGen(int pg)        { power_gen = pg; }
void        Reactor::setFuelRate(int fr)        { fuel_rate = fr; }
void        Reactor::setReliability(float rel)  { reliability = rel; }
// operator overload

bool        Reactor::operator==(const Reactor &r) const {
    return typeid(*this) == typeid(r) &&
           Component::operator==(r) &&
           this->power_gen == r.power_gen &&
           this->fuel_rate == r.fuel_rate &&
           this->reliability == r.reliability;
}
bool        Reactor::operator!=(const Reactor &r) const {
    return !(*this == r);
}

void        Reactor::use()                      {

}


// *************** SUBDRIVE ***************

// getters
float       SubDrive::getAccel() const          { return accel; }
int         SubDrive::getManeuver() const       { return maneuver; }
int         SubDrive::getSpeed() const          { return speed; }

// setters
void        SubDrive::setAccel(float acc)       { accel = acc; }
void        SubDrive::setManeuver(int manu)     { maneuver = manu; }
void        SubDrive::setSpeed(int spd)         { speed = spd; }

// operator overload
bool        SubDrive::operator==(const SubDrive &s) const {
    return typeid(*this) == typeid(s) &&
           Component::operator==(s) &&
           this->accel == s.accel &&
           this->maneuver == s.maneuver &&
           this->speed == s.speed;
}
bool        SubDrive::operator!=(const SubDrive &s) const {
    return !(*this == s);
}

void        SubDrive::use()                     {

}


// *************** FTLDRIVE ***************

// getters
int         FTLDrive::getChargeRate() const     { return charge_rate; }
ShipSize    FTLDrive::getMaxSize() const        { return max_size; }
int         FTLDrive::getFuelUse() const        { return fuel_use; }

// setters
void        FTLDrive::setChargeRate(int cr)     { charge_rate = cr; }
void        FTLDrive::setMaxSize(ShipSize ms)   { max_size = ms; }
void        FTLDrive::setFuelUse(int fu)        { fuel_use = fu; }

// operator overload
bool        FTLDrive::operator==(const FTLDrive &f) const {
    return typeid(*this) == typeid(f) &&
           Component::operator==(f) &&
           this->charge_rate == f.charge_rate &&
           this->max_size == f.max_size &&
           this->fuel_use == f.fuel_use;
}
bool        FTLDrive::operator!=(const FTLDrive &f) const {
    return !(*this == f);
}

void        FTLDrive::use()                     {

}
