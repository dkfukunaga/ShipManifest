


#ifndef SHIP_CLASS_H
#define SHIP_CLASS_H

#include "ShipTypes.h"
#include "Component.h"
#include "ComponentTypes.h"
#include "Weapon.h"
#include "WeaponTypes.h"
#include <string>


struct ShipComponents {
    Reactor         *reactor;
    SubDrive        *sub_drive;
    FTLDrive        *ftl_drive;
    ShieldGen       *shield_gen;
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
    short           officers;
    short           crew;
    ShipSize        size;
    ShipComponents  components;
    ShipDefenses    defenses;
    ShipWeapons     weapons;
};


#endif