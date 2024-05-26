

#include "ShipTypes.h"
#include "Ship.h"
#include <string>



// ******************** SHIP DEFENSES ********************

// constructor
ShipDefenses::ShipDefenses(int hul, int arm, int barr) :
    hull(hul),
    armor(arm),
    barrier(barr) { }


// ******************** SHIP COMPONENTS ********************

// constructor
ShipComponents::ShipComponents(Reactor *reac, SubDrive *sub, FTLDrive *ftl) :
    reactor(reac),
    sub_drive(sub),
    ftl_drive(ftl) { }


// ******************** SHIP WEAPONS ********************

// constructor
ShipWeapons::ShipWeapons(uchar num_mis, uchar num_hvy, uchar num_med, uchar num_lt,
        Weapon **mis_weaps, Weapon **hvy_weaps, Weapon **med_weaps, Weapon **lt_weaps) :
    num_missile(num_mis),
    num_heavy(num_hvy),
    num_medium(num_med),
    num_light(num_lt) {
    if (mis_weaps == nullptr) {
        missile_weapons = new Weapon*[num_mis];
        for (int i = 0; i < num_mis; ++i) {
            *(missile_weapons + i) = EmptyWeaponSLot::no_missile;
        }
    } else {
        missile_weapons = mis_weaps;
    }
    if (hvy_weaps == nullptr) {
        heavy_weapons = new Weapon*[num_hvy];
        for (int i = 0; i < num_hvy; ++i) {
            *(heavy_weapons + i) = EmptyWeaponSLot::no_heavy;
        }
    } else {
        heavy_weapons = hvy_weaps;
    }
    if (med_weaps == nullptr) {
        medium_weapons = new Weapon*[num_med];
        for (int i = 0; i < num_med; ++i) {
            *(medium_weapons + i) = EmptyWeaponSLot::no_medium;
        }
    } else {
        medium_weapons = med_weaps;
    }
    if (lt_weaps == nullptr) {
        light_weapons = new Weapon*[num_lt];
        for (int i = 0; i < num_lt; ++i) {
            *(light_weapons + i) = EmptyWeaponSLot::no_light;
        }
    } else {
        light_weapons = lt_weaps;
    }
    // missile_weapons = (mis_weaps == nullptr ? new Weapon*[num_mis] : mis_weaps);
    // heavy_weapons = (hvy_weaps == nullptr ? new Weapon*[num_hvy] : hvy_weaps);
    // medium_weapons = (med_weaps == nullptr ? new Weapon*[num_med] : med_weaps);
    // light_weapons = (lt_weaps == nullptr ? new Weapon*[num_lt] : lt_weaps);
}


// ******************** SHIP CLASS ********************

ShipClass *ShipClass::place_holder = new ShipClass();

// size getter
std::string ShipClass::getSize() const { return ship_sizes[(int) size]; }
ShipSize ShipClass::getSizeCode() const { return size; }

// constructor
ShipClass::ShipClass(std::string class_name, int num_off, int num_crew, ShipSize ship_size,
        ShipDefenses ship_def, ShipComponents ship_comp, ShipWeapons ship_weaps) :
    name(class_name),
    officers(num_off),
    crew(num_crew),
    size(ship_size),
    defenses(ship_def),
    components(ship_comp),
    weapons(ship_weaps) { }


// ******************** SHIP ********************

// void Ship::resetRegShipSize() { registry.setShipSize(ship_class->getSizeCode()); }
// ShipRegistry *Ship::getRegistry() { return registry; }
ShipRegistry *Ship::def_reg = new ShipRegistry();

// constructor
Ship::Ship(ShipRegistry *reg, std::string ship_name, std::string cmdr, std::string engi,
        ShipClass *shp_class) :
    registry(reg),
    name(ship_name),
    commander(cmdr),
    engineer(engi),
    ship_class(shp_class) {
    defenses = ship_class->defenses;
    components = ship_class->components;
    weapons = ship_class->weapons;
    registry = reg;
    registry->setShipSize(ship_class->getSizeCode());
}

