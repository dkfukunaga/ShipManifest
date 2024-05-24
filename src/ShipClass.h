


#ifndef SHIP_CLASS_H
#define SHIP_CLASS_H

#include "ShipTypes.h"
#include "Component.h"
#include "Weapon.h"
#include <string>


struct ShipComponents {
    Reactor         *reactor;
    SubDrive        *sub_drive;
    FTLDrive        *ftl_drive;
};

struct ShipDefenses {
    int             hull;
    int             armor;
    int             barrier;
};

struct ShipWeapons {
    char            num_heavy;
    char            num_medium;
    char            num_light;
    Weapon          **heavy_weapons;
    Weapon          **medium_weapons;
    Weapon          **light_weapons;
};

struct ShipClass {
    string          name;
    int             officers;
    int             crew;
    ShipSize        size;
    ShipComponents  default_components;
    ShipDefenses    default_defenses;
    ShipWeapons     default_weapons;
};


#endif