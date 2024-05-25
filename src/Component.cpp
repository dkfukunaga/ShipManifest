


#include "ShipTypes.h"
#include "Component.h"
#include <typeinfo>
#include <string>



// *************** COMPONENT BASE CLASS ***************

// getters
std::string Component::getName() const          { return m_name; }
char        Component::getTier() const          { return m_tier; }
int         Component::getMass() const          { return m_mass; }
int         Component::getPower() const         { return m_power; }

// setters
void        Component::setName(std::string name) { m_name = name; }
void        Component::setTier(char tier)       { m_tier = tier; }
void        Component::setMass(int mass)        { m_mass = mass; }
void        Component::setPower(int power)      { m_power = power; }

// operator overload
bool        Component::operator==(const Component &c) const {
    return this->m_name == c.m_name &&
           this->m_tier == c.m_tier &&
           this->m_mass == c.m_mass &&
           this->m_power == c.m_power;
}
bool        Component::operator!=(const Component &c) const {
    return !(*this == c);
}

// constructors
Component::Component(std::string name, char tier, int mass, int power) :
    m_name(name),
    m_tier(tier),
    m_mass(mass),
    m_power(power) { }


// *************** REACTOR ***************

// getters
int         Reactor::getPowerGen() const        { return m_power_gen; }
int         Reactor::getFuelRate() const        { return m_fuel_rate; }
int         Reactor::getReliability() const     { return m_reliability; }

// setters
void        Reactor::setPowerGen(int power_gen) { m_power_gen = power_gen; }
void        Reactor::setFuelRate(int fire_rate) { m_fuel_rate = fire_rate; }
void        Reactor::setReliability(int rel)    { m_reliability = rel; }
// operator overload

bool        Reactor::operator==(const Reactor &rel) const {
    return typeid(*this) == typeid(rel) &&
           Component::operator==(rel) &&
           this->m_power_gen == rel.m_power_gen &&
           this->m_fuel_rate == rel.m_fuel_rate &&
           this->m_reliability == rel.m_reliability;
}
bool        Reactor::operator!=(const Reactor &rel) const {
    return !(*this == rel);
}

void        Reactor::use()                      {

}

// constructors
Reactor::Reactor(std::string name, char tier, int mass, int power, int power_gen,
    int fire_rate, int rel) :
    Component(name, tier, mass, power),
    m_power_gen(power_gen),
    m_fuel_rate(fire_rate),
    m_reliability(rel) { }

Reactor::Reactor(Reactor &other) :
    Component(other.m_name, other.m_tier, other.m_mass, other.m_power),
    m_power_gen(other.m_power_gen),
    m_fuel_rate(other.m_fuel_rate),
    m_reliability(other.m_reliability) { }


// *************** SUBDRIVE ***************

// getters
int         SubDrive::getAccel() const          { return m_accel; }
int         SubDrive::getManeuver() const       { return m_maneuver; }
int         SubDrive::getSpeed() const          { return m_speed; }

// setters
void        SubDrive::setAccel(int accel)     { m_accel = accel; }
void        SubDrive::setManeuver(int maneuver) { m_maneuver = maneuver; }
void        SubDrive::setSpeed(int speed)       { m_speed = speed; }

// operator overload
bool        SubDrive::operator==(const SubDrive &s) const {
    return typeid(*this) == typeid(s) &&
           Component::operator==(s) &&
           this->m_accel == s.m_accel &&
           this->m_maneuver == s.m_maneuver &&
           this->m_speed == s.m_speed;
}
bool        SubDrive::operator!=(const SubDrive &s) const {
    return !(*this == s);
}

void        SubDrive::use()                     {

}

// constructors
SubDrive::SubDrive(std::string name, char tier, int mass, int power,
    int accel, int maneuver, int speed) :
    Component(name, tier, mass, power),
    m_accel(accel),
    m_maneuver(maneuver),
    m_speed(speed) { }

SubDrive::SubDrive(SubDrive &other) :
    Component(other.m_name, other.m_tier, other.m_mass, other.m_power),
    m_accel(other.m_accel),
    m_maneuver(other.m_maneuver),
    m_speed(other.m_speed) { }



// *************** FTLDRIVE ***************

// getters
int         FTLDrive::getChargeRate() const     { return m_charge_rate; }
std::string FTLDrive::getMaxSize() const        { return ship_sizes[(int) m_max_size]; }
int         FTLDrive::getFuelUse() const        { return m_fuel_use; }

// setters
void        FTLDrive::setChargeRate(int charge_rate) { m_charge_rate = charge_rate; }
void        FTLDrive::setMaxSize(ShipSize max_size)  { m_max_size = max_size; }
void        FTLDrive::setFuelUse(int fuel_use)       { m_fuel_use = fuel_use; }

// operator overload
bool        FTLDrive::operator==(const FTLDrive &f) const {
    return typeid(*this) == typeid(f) &&
           Component::operator==(f) &&
           this->m_charge_rate == f.m_charge_rate &&
           this->m_max_size == f.m_max_size &&
           this->m_fuel_use == f.m_fuel_use;
}
bool        FTLDrive::operator!=(const FTLDrive &f) const {
    return !(*this == f);
}

void        FTLDrive::use()                     {

}

// constructors
FTLDrive::FTLDrive(std::string name, char tier, int mass, int power,
    int charge_rate, ShipSize size, int fuel_use) :
    Component(name, tier, mass, power),
    m_charge_rate(charge_rate),
    m_max_size(size),
    m_fuel_use(fuel_use) { }

FTLDrive::FTLDrive(FTLDrive &other) :
    Component(other.m_name, other.m_tier, other.m_mass, other.m_power),
    m_charge_rate(other.m_charge_rate),
    m_max_size(other.m_max_size),
    m_fuel_use(other.m_fuel_use) { }



