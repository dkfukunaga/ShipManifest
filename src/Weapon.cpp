


#include "Weapon.h"
#include <string>
#include <cmath>
#include <typeinfo>

// ******************** WEAPON ********************

// Weapon getters
std::string Weapon::getName() const             { return name; }
char        Weapon::getTier() const             { return tier; }
WeaponSize  Weapon::getSize() const             { return size; }
int         Weapon::getBaseDamage() const       { return base_damage; }
int         Weapon::getFireRate() const         { return fire_rate; }
int         Weapon::getRange() const            { return range; }
int         Weapon::getPower() const            { return power; }

// Weapon setters
void        Weapon::setName(std::string nm)          { name = nm; }
void        Weapon::setTier(char tr)            { tier = tr; }
void        Weapon::setSize(WeaponSize sz)      { size = sz; }
void        Weapon::setBaseDamage(int bs_dmg)   { base_damage = bs_dmg; }
void        Weapon::setFireRate(int fr)         { fire_rate = fr; }
void        Weapon::setRange(int rng)           { range = rng; }
void        Weapon::setPower(int pwr)           { power = pwr; }

// Weapon operator overload
bool        Weapon::operator==(const Weapon &w) const {
    return this->name == w.name &&
           this->tier == w.tier &&
           this->size == w.size &&
           this->base_damage == w.base_damage &&
           this->fire_rate == w.fire_rate &&
           this->range == w.range &&
           this->power == w.power;
}
bool        Weapon::operator!=(const Weapon &w) const {
    return !(*this == w);
}

// constructors
Weapon::Weapon(std::string nm, char tr, WeaponSize ws, int bd, int fr, int r, int p) :
    name(nm),
    tier(tr),
    size(ws),
    base_damage(bd),
    fire_rate(fr),
    range(r),
    power(p) { }

Weapon::Weapon() :
    name(""),
    tier('Z'),
    size(WeaponSize::small),
    base_damage(0),
    fire_rate(0),
    range(0),
    power(0) { }


// ******************** BEAM ********************

// Beam getters
int         Beam::getEffRange() const           { return eff_range; };
int         Beam::getDamage(double dist) { return calcDamage(dist); }

// Beam setters
void        Beam::setEffRange(int eff_rng)      { eff_range = eff_rng; }

// Beam operator overload
bool        Beam::operator==(const Beam &b) const {
    return typeid(*this) == typeid(b) &&
           Weapon::operator==(b) &&
           this->eff_range == b.eff_range;
}
bool        Beam::operator!=(const Beam &b) const {
    return !(*this == b);
}

// Beam private function
// Beam will do max damage at 0 range, reducing to 90% damage
// at effective range, further down to 10% damage at max range
int         Beam::calcDamage(double dist)       {
    // 0 damage past max range
    if (dist > range)
        return 0;
    // exponent for damage calculation
    double p = log2(9)/log2(range/eff_range);
    // calculation for damage that decreases after effective range and
    // goes to 0 at max range
    int dmg = ceil(base_damage -((0.1*base_damage)/pow(eff_range, p)) * pow(dist, p));
    return dmg;
}

// constructors
Beam::Beam(std::string nm, char tr, WeaponSize ws, int bd, int fr, int r, int p, int er) :
    Weapon(nm, tr, ws, bd, fr, r, p),
    eff_range(er) { }

Beam::Beam(Beam &other) :
    Weapon(other.name, other.tier, other.size, other.base_damage, other.fire_rate,
        other.range, other.power),
    eff_range(other.eff_range) { }

Beam::Beam() :
    Weapon(),
    eff_range(0) { }


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

// Kinetic opeator overload
bool        Kinetic::operator==(const Kinetic &k) const {
    return typeid(*this) == typeid(k) &&
           Weapon::operator==(k) &&
           this->max_ammo == k.max_ammo &&
           this->curr_ammo == k.curr_ammo;
}
bool        Kinetic::operator!=(const Kinetic &k) const {
    return !(*this == k);
}

// constructors
Kinetic::Kinetic(std::string nm, char tr, WeaponSize ws, int bd, int fr, int r, int p, int ma, int ca) :
    Weapon(nm, tr, ws, bd, fr, r, p),
    max_ammo(ma),
    curr_ammo(ca) { }
Kinetic::Kinetic(Kinetic &other) :
    Weapon(other.name, other.tier, other.size, other.base_damage, other.fire_rate,
        other.range, other.power),
    max_ammo(other.max_ammo),
    curr_ammo(other.curr_ammo) { }
Kinetic::Kinetic() :
    Weapon(),
    max_ammo(0),
    curr_ammo(0) { }


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

// Missile operator overload
bool        Missile::operator==(const Missile &m) const {
    return typeid(*this) == typeid(m) &&
           Weapon::operator==(m) &&
           this->speed == m.speed &&
           this->tracking == m.tracking &&
           this->hull == m.hull;
}
bool        Missile::operator!=(const Missile &m) const {
    return !(*this == m);
}

// constructors
Missile::Missile(std::string nm, char tr, WeaponSize ws, int bd, int fr, int r, int p,
    int spd, float t, int h) :
    Weapon(nm, tr, ws, bd, fr, r, p),
    speed(spd),
    tracking(t),
    hull(h) { }

Missile::Missile(Missile &other) :
    Weapon(other.name, other.tier, other.size, other.base_damage, other.fire_rate,
        other.range, other.power),
    speed(0),
    tracking(0.0),
    hull(0) { }

Missile::Missile() :
    Weapon(),
    speed(0),
    tracking(0.0),
    hull(0) { }

