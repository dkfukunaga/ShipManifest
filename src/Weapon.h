



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
    string          getName() const;
    char            getTier() const;
    WeaponSize      getSize() const;
    int             getBaseDamage() const;
    int             getFireRate() const;
    int             getRange() const;
    int             getPower() const;
    void            setName(string nm);
    void            setTier(char tr);
    void            setSize(WeaponSize sz);
    void            setBaseDamage(int bs_dmg);
    void            setFireRate(int fr);
    void            setRange(int rng);
    void            setPower(int pwr);
    virtual int     getDamage(double dist) = 0;
};


// *************** WEAPON CLASSES ***************


class Beam : public Weapon {
private:
    int             eff_range;
    int             calcDamage(double dist);
public:
    int             getEffRange() const;
    void            setEffRange(int eff_rng);
    int             getDamage(double dist) override;
};


class Kinetic : public Weapon {
private:
    int             max_ammo;
    int             curr_ammo;
public:
    int             getMaxAmmo() const;
    int             getCurrAmmo() const;
    void            setMaxAmmo(int ma);
    void            setCurrAmmo(int ca);
    int             getDamage(double dist) override ;
};

class Missile : public Weapon {
private:
    int             speed;
    float           tracking;
    int             hull;
public:
    int             getSpeed() const;
    float           getTracking() const;
    int             getHull() const;
    void            setSpeed(int spd);
    void            setTracking(float trck);
    void            setHull(int hl);
    int             getDamage(double dist) override ;
};


#endif