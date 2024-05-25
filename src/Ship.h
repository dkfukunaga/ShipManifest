


#ifndef SHIP_H
#define SHIP_H

#include "ShipTypes.h"
#include "ShipRegistry.h"
#include "Component.h"
#include "Weapon.h"
#include <string>

using namespace std;

struct ShipComponents {
    Reactor         *reactor = nullptr;
    SubDrive        *sub_drive = nullptr;
    FTLDrive        *ftl_drive = nullptr;
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
    Weapon          **heavy_weapons = nullptr;
    Weapon          **medium_weapons = nullptr;
    Weapon          **light_weapons = nullptr;
};

struct ShipClass {
    std::string     name;
    int             officers;
    int             crew;
    ShipSize        size;
    ShipDefenses    defenses;
    ShipComponents  components;         // stock components loadout
    ShipWeapons     weapons;            // stock weapons loadout
};


struct Ship {
    ShipRegistry    registry;
    std::string     name;
    std::string     commander;
    std::string     engineer;
    ShipClass*      ship_class = nullptr;
    ShipDefenses    defenses;
    ShipComponents  components;
    ShipWeapons     weapons;
};


#endif

