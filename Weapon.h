



#ifndef WEAPON_H
#define WEAPON_H

#include <string>

using namespace std;

enum class WeaponSize;

class Weapon {
public:
    string      name;
    char        tier;
    WeaponSize  size;
    int         base_damage;
    int         fire_rate;
    int         range;
    int         power;
    virtual int getDamage(double distance) = 0;
};




#endif