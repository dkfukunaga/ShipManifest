



#ifndef WEAPON_H
#define WEAPON_H

#include "ShipTypes.h"
#include <string>

using namespace std;


// Weapon base abstract class
class Weapon {
protected:
    string          name;
    char            tier;
    WeaponSize      size;
    int             base_damage;
    int             fire_rate;
    int             range;
    int             power;

public:
    // getters
    string          getName() const;
    char            getTier() const;
    WeaponSize      getSize() const;
    int             getBaseDamage() const;
    int             getFireRate() const;
    int             getRange() const;
    int             getPower() const;

    // setters
    void            setName(string nm);
    void            setTier(char tr);
    void            setSize(WeaponSize sz);
    void            setBaseDamage(int bs_dmg);
    void            setFireRate(int fr);
    void            setRange(int rng);
    void            setPower(int pwr);

    // operators
    bool            operator==(const Weapon &w) const;
    bool            operator!=(const Weapon &w) const;

    // virtual
    virtual int     getDamage(double dist) = 0;
};


// *************** WEAPON CLASSES ***************


class Beam : public Weapon {
private:
    int             eff_range;
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
};


class Kinetic : public Weapon {
private:
    int             max_ammo;
    int             curr_ammo;

public:
    // getters
    int             getMaxAmmo() const;
    int             getCurrAmmo() const;

    // setters
    void            setMaxAmmo(int ma);
    void            setCurrAmmo(int ca);

    // operators
    bool            operator==(const Kinetic &k) const;
    bool            operator!=(const Kinetic &k) const;

    // virtual override
    int             getDamage(double dist) override;
};

class Missile : public Weapon {
private:
    int             speed;
    float           tracking;
    int             hull;
    
public:
    // getters
    int             getSpeed() const;
    float           getTracking() const;
    int             getHull() const;

    // setters
    void            setSpeed(int spd);
    void            setTracking(float trck);
    void            setHull(int hl);

    // operators
    bool            operator==(const Missile &m) const;
    bool            operator!=(const Missile &m) const;
    
    // virtual override
    int             getDamage(double dist) override;
};


#endif