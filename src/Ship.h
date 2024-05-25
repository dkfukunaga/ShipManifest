


#ifndef SHIP_H
#define SHIP_H

#include "ShipTypes.h"
#include "ShipRegistry.h"
#include "Component.h"
#include "Weapon.h"
#include <string>

using namespace std;

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
    ShipDefenses    defenses;
    ShipComponents  components;         // stock components
    ShipWeapons     weapons;            // stock weapons loadout
};


struct Ship {
    ShipRegistry    registry;
    string          name;
    string          commander;
    string          engineer;
    ShipClass*      ship_class;
    ShipDefenses    defenses;
    ShipComponents  components;
    ShipWeapons     weapons;
};


#endif

