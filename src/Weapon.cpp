


#include "ShipTypes.h"
#include "Weapon.h"
#include <string>
#include <cmath>
#include <typeinfo>

// ******************** WEAPON ********************

// static variables

// Weapon getters
std::string Weapon::getName() const             { return m_name; }
uchar       Weapon::getTier() const             { return m_tier; }
WeaponSize  Weapon::getSize() const             { return m_size; }
int         Weapon::getBaseDamage() const       { return m_base_damage; }
int         Weapon::getFireRate() const         { return m_fire_rate; }
int         Weapon::getRange() const            { return m_range; }
int         Weapon::getPower() const            { return m_power; }

// Weapon setters
void        Weapon::setName(std::string name)   { m_name = name; }
void        Weapon::setTier(uchar tier)         { m_tier = tier; }
void        Weapon::setSize(WeaponSize size)    { m_size = size; }
void        Weapon::setBaseDamage(int bs_dmg)   { m_base_damage = bs_dmg; }
void        Weapon::setFireRate(int fire_rate)  { m_fire_rate = fire_rate; }
void        Weapon::setRange(int range)         { m_range = range; }
void        Weapon::setPower(int power)         { m_power = power; }

// Weapon operator overload
bool        Weapon::operator==(const Weapon &w) const {
    return this->m_name == w.m_name &&
           this->m_tier == w.m_tier &&
           this->m_size == w.m_size &&
           this->m_base_damage == w.m_base_damage &&
           this->m_fire_rate == w.m_fire_rate &&
           this->m_range == w.m_range &&
           this->m_power == w.m_power;
}
bool        Weapon::operator!=(const Weapon &w) const {
    return !(*this == w);
}

// constructor
Weapon::Weapon(std::string name, uchar tier, WeaponSize size, int base_damage,
        int fire_rate, int range, int power) :
    m_name(name),
    m_tier(tier),
    m_size(size),
    m_base_damage(base_damage),
    m_fire_rate(fire_rate),
    m_range(range),
    m_power(power) { }


// ******************** WEAPON ********************

// static variables
EmptyWeaponSLot *EmptyWeaponSLot::no_missile = new EmptyWeaponSLot("empty", 99,
    WeaponSize::missile, 0, 0, 0, 0);
EmptyWeaponSLot *EmptyWeaponSLot::no_heavy = new EmptyWeaponSLot("empty", 99,
    WeaponSize::large, 0, 0, 0, 0);
EmptyWeaponSLot *EmptyWeaponSLot::no_medium = new EmptyWeaponSLot("empty", 99,
    WeaponSize::medium, 0, 0, 0, 0);
EmptyWeaponSLot *EmptyWeaponSLot::no_light = new EmptyWeaponSLot("empty", 99,
    WeaponSize::small, 0, 0, 0, 0);

// EmptyWeaponSlot getters
int         EmptyWeaponSLot::getDamage(double dist) { /* stub*/ return 0; }

// constructor
EmptyWeaponSLot::EmptyWeaponSLot(std::string name, uchar tier, WeaponSize size, int base_damage,
        int fire_rate, int range, int power) :
    Weapon(name, tier, size, base_damage, fire_rate, range, power) { }


// ******************** BEAM ********************

// Beam getters
int         Beam::getEffRange() const           { return m_eff_rng; };
int         Beam::getDamage(double dist) { return calcDamage(dist); }

// Beam setters
void        Beam::setEffRange(int eff_rng)      { m_eff_rng = eff_rng; }

// Beam operator overload
bool        Beam::operator==(const Beam &b) const {
    return typeid(*this) == typeid(b) &&
           Weapon::operator==(b) &&
           this->m_eff_rng == b.m_eff_rng;
}
bool        Beam::operator!=(const Beam &b) const {
    return !(*this == b);
}

// Beam private function
// Beam will do max damage at 0 range, reducing to 90% damage
// at effective range, further down to 10% damage at max range
int         Beam::calcDamage(double dist)       {
    // 0 damage past max range
    if (dist > m_range)
        return 0;
    // exponent for damage calculation
    double power = log2(9)/log2(m_range/m_eff_rng);
    // calculation for damage that decreases after effective range and
    // goes to 0 at max range
    int dmg = ceil(m_base_damage -((0.1*m_base_damage)/pow(m_eff_rng, power)) * pow(dist, power));
    return dmg;
}

// constructors
Beam::Beam(std::string name, uchar tier, WeaponSize size, int base_damage, int fire_rate, int range, int power, int er) :
    Weapon(name, tier, size, base_damage, fire_rate, range, power),
    m_eff_rng(er) { }

Beam::Beam(Beam &other) :
    Weapon(other.m_name, other.m_tier, other.m_size, other.m_base_damage, other.m_fire_rate,
        other.m_range, other.m_power),
    m_eff_rng(other.m_eff_rng) { }


// ******************** KINETIC ********************

// Kinetic getters
int         Kinetic::getMaxAmmo() const         { return m_max_ammo; }
int         Kinetic::getCurrAmmo() const        { return m_curr_ammo; }
int         Kinetic::getDamage(double dist)     {
    return (dist <= m_range ? m_base_damage : 0);
}

// Kinetic setters
void        Kinetic::setMaxAmmo(int max_ammo)   { m_max_ammo = max_ammo; }
void        Kinetic::setCurrAmmo(int curr_ammo) { m_curr_ammo = curr_ammo; }

// Kinetic opeator overload
bool        Kinetic::operator==(const Kinetic &k) const {
    return typeid(*this) == typeid(k) &&
           Weapon::operator==(k) &&
           this->m_max_ammo == k.m_max_ammo &&
           this->m_curr_ammo == k.m_curr_ammo;
}
bool        Kinetic::operator!=(const Kinetic &k) const {
    return !(*this == k);
}

// constructors
Kinetic::Kinetic(std::string name, uchar tier, WeaponSize size, int base_damage, int fire_rate, int range, int power, int max_ammo, int curr_ammo) :
    Weapon(name, tier, size, base_damage, fire_rate, range, power),
    m_max_ammo(max_ammo),
    m_curr_ammo(curr_ammo) { }

Kinetic::Kinetic(Kinetic &other) :
    Weapon(other.m_name, other.m_tier, other.m_size, other.m_base_damage, other.m_fire_rate,
        other.m_range, other.m_power),
    m_max_ammo(other.m_max_ammo),
    m_curr_ammo(other.m_curr_ammo) { }


// ******************** MISSILE ********************

// Missile getters
int         Missile::getSpeed() const           { return m_speed; }
float       Missile::getTracking() const        { return m_tracking; }
int         Missile::getHull() const            { return m_hull; }
int         Missile::getDamage(double dist)     { return m_base_damage; }

// Missile setters
void        Missile::setSpeed(int speed)        { m_speed = speed; }
void        Missile::setTracking(float trck)    { m_tracking = trck; }
void        Missile::setHull(int hull)          { m_hull = hull; }

// Missile operator overload
bool        Missile::operator==(const Missile &m) const {
    return typeid(*this) == typeid(m) &&
           Weapon::operator==(m) &&
           this->m_speed == m.m_speed &&
           this->m_tracking == m.m_tracking &&
           this->m_hull == m.m_hull;
}
bool        Missile::operator!=(const Missile &m) const {
    return !(*this == m);
}

// constructors
Missile::Missile(std::string name, uchar tier, WeaponSize size, int base_damage,
    int fire_rate, int range, int power, int speed, float trck, int hull) :
    Weapon(name, tier, size, base_damage, fire_rate, range, power),
    m_speed(speed),
    m_tracking(trck),
    m_hull(hull) { }

Missile::Missile(Missile &other) :
    Weapon(other.m_name, other.m_tier, other.m_size, other.m_base_damage, other.m_fire_rate,
        other.m_range, other.m_power),
    m_speed(0),
    m_tracking(0.0),
    m_hull(0) { }


