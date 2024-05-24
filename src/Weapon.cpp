


#include "Weapon.h"
#include <cmath>

// ******************** WEAPON ********************

// Weapon getters
string      Weapon::getName() const             { return name; }
char        Weapon::getTier() const             { return tier; }
WeaponSize  Weapon::getSize() const             { return size; }
int         Weapon::getBaseDamage() const       { return base_damage; }
int         Weapon::getFireRate() const         { return fire_rate; }
int         Weapon::getRange() const            { return range; }
int         Weapon::getPower() const            { return power; }

// Weapon setters
void        Weapon::setName(string nm)          { name = nm; }
void        Weapon::setTier(char tr)            { tier = tr; }
void        Weapon::setSize(WeaponSize sz)      { size = sz; }
void        Weapon::setBaseDamage(int bs_dmg)   { base_damage = bs_dmg; }
void        Weapon::setFireRate(int fr)         { fire_rate = fr; }
void        Weapon::setRange(int rng)           { range = rng; }
void        Weapon::setPower(int pwr)           { power = pwr; }


// ******************** BEAM ********************

// Beam getters
int         Beam::getEffRange() const           { return eff_range; };
int         Beam::getDamage(double dist) { return calcDamage(dist); }

// Beam setters
void        Beam::setEffRange(int eff_rng)      { eff_range = eff_rng; }
// Beam private function
int         Beam::calcDamage(double dist)       {
    // exponent for damage calculation
    double p = log2(10)/log2(range/eff_range);
    // calculation for damage that decreases after effective range and
    // goes to 0 at max range
    int dmg = ceil(base_damage -((0.1*base_damage)/pow(eff_range, p)) * pow(dist, p));
    return dmg;
}


// ******************** KINETIC ********************

// Kinetic getters
int         Kinetic::getMaxAmmo() const         { return max_ammo; }
int         Kinetic::getCurrAmmo() const        { return curr_ammo; }
int         Kinetic::getDamage(double dist)     {
    return (dist <= range ? base_damage : 0);
}

// Kinetic setters
void        Kinetic::setMaxAmmo(int ma)         { max_ammo = ma; }
void        Kinetic::setCurrAmmo(int ca)        { curr_ammo = ca; }


// ******************** MISSILE ********************

// Missile getters
int         Missile::getSpeed() const           { return speed; }
float       Missile::getTracking() const        { return tracking; }
int         Missile::getHull() const            { return hull; }
int         Missile::getDamage(double dist)     { return base_damage; }

// Missile setters
void        Missile::setSpeed(int spd)          { speed = spd; }
void        Missile::setTracking(float trck)    { tracking = trck; }
void        Missile::setHull(int hl)            { hull = hl; }



