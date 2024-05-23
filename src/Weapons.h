

#ifndef WEAPON_TYPES_H
#define WEAPON_TYPES_H

#include "Weapon.h"

using namespace std;


class Beam : public Weapon {
public:
    int getDamage(double distance) override ;
private:
    int             eff_range;

};


class Kinetic : public Weapon {

public:
    int getDamage(double distance) override ;
private:
    int             max_ammo;
    int             curr_ammo;

};

class Missile : public Weapon {

public:
    int getDamage(double distance) override ;
private:
    int             speed;
    float           tracking;
    int             hull;

};



#endif