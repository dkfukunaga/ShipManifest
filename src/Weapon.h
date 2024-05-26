



#ifndef WEAPON_H
#define WEAPON_H

#include "ShipTypes.h"
#include <string>


// Weapon base abstract class
class Weapon {
protected:
    std::string     m_name;
    uchar           m_tier;
    WeaponSize      m_size;
    int             m_base_damage;
    int             m_fire_rate;
    int             m_range;
    int             m_power;

public:
    // getters
    std::string     getName() const;
    uchar           getTier() const;
    WeaponSize      getSize() const;
    int             getBaseDamage() const;
    int             getFireRate() const;
    int             getRange() const;
    int             getPower() const;

    // setters
    void            setName(std::string name);
    void            setTier(uchar tier);
    void            setSize(WeaponSize size);
    void            setBaseDamage(int base_dmg);
    void            setFireRate(int fire_rate);
    void            setRange(int range);
    void            setPower(int power);

    // operators
    bool            operator==(const Weapon &w) const;
    bool            operator!=(const Weapon &w) const;

    // virtual
    virtual int     getDamage(double dist) = 0;

    // constructor
    Weapon(std::string name = "NONE", uchar tier = 'C', WeaponSize size = WeaponSize::small,
        int base_dmg = 0, int fire_rate = 0, int range = 0, int power = 0);
};


// *************** WEAPON CLASSES ***************


class EmptyWeaponSLot : public Weapon {
    public:
    // placeholders for empty weapon slots
    static EmptyWeaponSLot *no_missile;
    static EmptyWeaponSLot *no_heavy;
    static EmptyWeaponSLot *no_medium;
    static EmptyWeaponSLot *no_light;

    // virutal override
    int             getDamage(double dist) override;

    // constructor
    EmptyWeaponSLot(std::string name = "NONE", uchar tier = 'C',
        WeaponSize size = WeaponSize::small, int base_dmg = 0, int fire_rate = 0,
        int range = 0, int power = 0);
};


class Beam : public Weapon {
private:
    // member variable
    int             m_eff_rng;

    // helper function
    int             calcDamage(double dist);

public:
    // getters
    int             getEffRange() const;

    // setters
    void            setEffRange(int eff_rng);

    // operators
    bool            operator==(const Beam &b) const;
    bool            operator!=(const Beam &b) const;

    // virutal override
    int             getDamage(double dist) override;

    // constructors
    Beam(std::string name = "NONE", uchar tier = 'C', WeaponSize size = WeaponSize::small,
        int base_dmg = 0, int fire_rate = 0, int range = 0, int power = 0,
        int eff_range = 0);
    Beam(Beam &other);
};


class Kinetic : public Weapon {
private:
    int             m_max_ammo;
    int             m_curr_ammo;

public:
    // getters
    int             getMaxAmmo() const;
    int             getCurrAmmo() const;

    // setters
    void            setMaxAmmo(int max_ammo);
    void            setCurrAmmo(int curr_ammo);

    // operators
    bool            operator==(const Kinetic &k) const;
    bool            operator!=(const Kinetic &k) const;

    // virtual override
    int             getDamage(double dist) override;

    // constructors
    Kinetic(std::string name = "NONE", uchar tier = 'C', WeaponSize size = WeaponSize::small,
        int base_dmg = 0, int fire_rate = 0, int range = 0, int power = 0,
        int max_ammo = 0, int curr_ammo = 0);
    Kinetic(Kinetic &other);
};

class Missile : public Weapon {
private:
    int             m_speed;
    float           m_tracking;
    int             m_hull;

public:
    // getters
    int             getSpeed() const;
    float           getTracking() const;
    int             getHull() const;

    // setters
    void            setSpeed(int speed);
    void            setTracking(float tracking);
    void            setHull(int hull);

    // operators
    bool            operator==(const Missile &m) const;
    bool            operator!=(const Missile &m) const;

    // virtual override
    int             getDamage(double dist) override;

    // constructors
    Missile(std::string name = "NONE", uchar tier = 'C', WeaponSize size = WeaponSize::small,
        int base_dmg = 0, int fire_rate = 0, int range = 0, int power = 0,
        int speed = 0, float tracking = 0.0, int hull = 0);
    Missile(Missile &other);
};


#endif