


#ifndef SHIP_H
#define SHIP_H

#include "ShipTypes.h"
#include "ShipRegistry.h"
#include "Component.h"
#include "Weapon.h"
#include <string>


// TODO: add constructors


struct ShipDefenses {
    // member variables
    int             hull;
    int             armor;
    int             barrier;

    // constructor
    ShipDefenses(int hul = 0, int arm = 0, int barr = 0);
};

struct ShipComponents {
    // member variables
    Reactor         *reactor;
    SubDrive        *sub_drive;
    FTLDrive        *ftl_drive;

    // constructor
    ShipComponents(Reactor *reac = nullptr, SubDrive *sub = nullptr, FTLDrive *ftl = nullptr);
};

struct ShipWeapons {
    // member variables
    uchar           num_missile;
    uchar           num_heavy;
    uchar           num_medium;
    uchar           num_light;
    Weapon          **missile_weapons = nullptr;
    Weapon          **heavy_weapons = nullptr;
    Weapon          **medium_weapons = nullptr;
    Weapon          **light_weapons = nullptr;

    // constructor
    ShipWeapons(uchar num_mis = 0, uchar num_hvy = 0, uchar num_med = 0, uchar num_lt = 0,
        Weapon **mis_weaps = nullptr, Weapon **hvy_weaps = nullptr,
        Weapon **med_weaps = nullptr, Weapon **lt_weaps = nullptr);
};

struct ShipClass {
    // placeholder values
    static ShipClass *place_holder;

    // member variables
    std::string     name;
    int             officers;
    int             crew;
    ShipSize        size;
    ShipDefenses    defenses;
    ShipComponents  components;         // stock components loadout
    ShipWeapons     weapons;            // stock weapons loadout

    // getter
    std::string     getSize() const;

    // constructor
    ShipClass(std::string class_name = "NONAME", int num_off = 0, int num_crew = 0,
        ShipSize ship_size = ShipSize::drone, ShipDefenses ship_def = ShipDefenses(),
        ShipComponents ship_comp = ShipComponents(), ShipWeapons ship_weaps = ShipWeapons());
};



struct Ship {
    // member variables
    ShipRegistry    registry;
    std::string     name;
    std::string     commander;
    std::string     engineer;
    ShipClass*      ship_class;
    ShipDefenses    defenses;
    ShipComponents  components;
    ShipWeapons     weapons;

    // constructor
    Ship(ShipRegistry reg = ShipRegistry(), std::string ship_name = "UNNAMED",
         std::string cmdr = "COMMANDER", std::string engi = "ENGINEER",
         ShipClass *shp_class = ShipClass::place_holder);
};



// helper display functions

void displayMissiles(Ship *ship);
void displayHeavyWeapons(Ship *ship);
void displayMediumWeapons(Ship *ship);
void displayMissiles(Ship *ship);
void displayAllWeapons(Ship *ship);

void displayShipClass(ShipClass *ship_class);
void displayShip(Ship *ship);


#endif

