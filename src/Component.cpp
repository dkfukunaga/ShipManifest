


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

// constructors
Component::Component(string nm, char tr, int m, int p) :
    name(nm),
    tier(tr),
    mass(m),
    power(p) { }

Component::Component() :
    Component("", 'Z', 0, 0) { }


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

// constructors
Reactor::Reactor(string nm, char tr, int m, int p, int pg, int fr, float r) :
    Component(nm, tr, m, p),
    power_gen(pg),
    fuel_rate(fr),
    reliability(r) { }

Reactor::Reactor(Reactor &other) :
    Component(other.name, other.tier, other.mass, other.power),
    power_gen(other.power_gen),
    fuel_rate(other.fuel_rate),
    reliability(other.reliability) { }

Reactor::Reactor() :
    Component(),
    power_gen(0),
    fuel_rate(0),
    reliability(0.0) { }


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

// constructors
SubDrive::SubDrive(string nm, char tr, int m, int p, float acc, int mn, int spd) :
    Component(nm, tr, m, p),
    accel(acc),
    maneuver(mn),
    speed(spd) { }

SubDrive::SubDrive(SubDrive &other) :
    Component(other.name, other.tier, other.mass, other.power),
    accel(other.accel),
    maneuver(other.maneuver),
    speed(other.speed) { }

SubDrive::SubDrive() :
    Component(),
    accel(0.0),
    maneuver(0),
    speed(0) { }



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

// constructors
FTLDrive::FTLDrive(string nm, char tr, int m, int p, int cr, ShipSize sz, int fu) :
    Component(nm, tr, m, p),
    charge_rate(cr),
    max_size(sz),
    fuel_use(fu) { }

FTLDrive::FTLDrive(FTLDrive &other) :
    Component(other.name, other.tier, other.mass, other.power),
    charge_rate(other.charge_rate),
    max_size(other.max_size),
    fuel_use(other.fuel_use) { }

FTLDrive::FTLDrive() :
    Component(),
    charge_rate(0),
    max_size(ShipSize::drone),
    fuel_use(0) { }



