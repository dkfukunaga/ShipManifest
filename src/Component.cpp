


#include "Component.h"


using namespace std;


// *************** COMPONENT BASE CLASS ***************

// getters
char        Component::getTier() const          { return tier; }
int         Component::getMass() const          { return mass; }
int         Component::getPower() const         { return power; }
// setters
void        Component::setName(string nm)       { name = nm; }
void        Component::setTier(char tr)         { tier = tr; }
void        Component::setMass(int m)           { mass = m; }
void        Component::setPower(int pow)        { power = pow; }


// *************** REACTOR ***************

// getters
int         Reactor::getPowerGen() const        { return power_gen; }
int         Reactor::getFuelRate() const        { return fuel_rate; }
float       Reactor::getReliability() const     { return reliability; }
// setters
void        Reactor::setPowerGen(int pg)        { power_gen = pg; }
void        Reactor::setFuelRate(int fr)        { fuel_rate = fr; }
void        Reactor::setReliability(float rel)  { reliability = rel; }

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

void        FTLDrive::use()                     {

}
