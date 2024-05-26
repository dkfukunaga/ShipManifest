


#include "..\src\Ship.h"
#include <iostream>



int main() {

    Ship *ship;

    Beam basic_beam("Basic Beam", 3, WeaponSize::small, 15, 1, 20, 5, 15);
    Kinetic medium_cannon("Medium Cannon", 2, WeaponSize::medium, 25, 1, 50, 10, 50, 50);
    Beam heavy_beam("Heavy Beam", 2, WeaponSize::large, 35, 1, 50, 25, 35);
    Missile torp("Torp", 3, WeaponSize::medium, 85, 0, 100, 15, 20, .75, 50);

    Reactor basic_reac("Basic Reactor", 3, 100, 0, 100, 5, .85);
    SubDrive basic_drive("Basic Drive", 3, 40, 10, .75, 10, 20);
    FTLDrive basic_ftl("Basic FTL", 3, 25, 20, 10, ShipSize::standard_h, 5);

    Weapon *torps[2] = {&torp, EmptyWeaponSLot::no_missile};
    Weapon *heavies[1] = {&heavy_beam};
    Weapon *mediums[2] = {&medium_cannon, EmptyWeaponSLot::no_medium};
    Weapon *lights[4] = {&basic_beam, &basic_beam, EmptyWeaponSLot::no_light, EmptyWeaponSLot::no_light};

    int num_torps = sizeof(torps) / sizeof(Weapon *);
    int num_heavies = sizeof(heavies) / sizeof(Weapon *);
    int num_mediums = sizeof(mediums) / sizeof(Weapon *);
    int num_lights = sizeof(lights) / sizeof(Weapon *);

    ShipDefenses test_def(100, 50, 50);
    ShipComponents test_comps(&basic_reac, &basic_drive, &basic_ftl);
    ShipWeapons test_weaps(num_torps, num_heavies, num_mediums, num_lights,
        torps, heavies, mediums, lights);

    ShipClass *test_class = new ShipClass("Test Class", 5, 10,
        ShipSize::standard_m, test_def, test_comps, test_weaps);

    ShipRegistry *reg = new ShipRegistry();
    // reg.setShipSize(test_class->getSizeCode());

    std::string test_ship_name = "Test Ship";
    std::string cmdr = "Captain Testerson";
    std::string engi = "Commander Exampleson";

    ship = new Ship(reg, test_ship_name, cmdr, engi, test_class);
    ship->registry->setShipUID(12345678);

    std::cout << std::endl;
    std::cout << "\"" << ship->name << "\" Registry: " << reg->getVIC() << std::endl;
    std::cout << "=========================================" << std::endl;
    std::cout << "Commander: " << ship->commander << std::endl;
    std::cout << "Engineer:  " << ship->engineer << std::endl;
    std::cout << "Ship Class:" << std::endl;
    std::cout << "    Name: " << ship->ship_class->name << std::endl;
    std::cout << "    Officers: " << ship->ship_class->officers << ", Crew: "
              << ship->ship_class->crew << std::endl;
    std::cout << "    Size: " << ship->ship_class->getSize() << std::endl;
    std::cout << "    Weapon Slots:" << std::endl;
    std::cout << "        Missile: " << (int) ship->ship_class->weapons.num_missile << std::endl;
    std::cout << "        Heavy:   " << (int) ship->ship_class->weapons.num_heavy << std::endl;
    std::cout << "        Medium:  " << (int) ship->ship_class->weapons.num_medium << std::endl;
    std::cout << "        Light:   " << (int) ship->ship_class->weapons.num_light << std::endl;
    std::cout << "Defenses:" << std::endl;
    std::cout << "    Hull:    " << ship->ship_class->defenses.hull << std::endl;
    std::cout << "    Armor:   " << ship->ship_class->defenses.armor << std::endl;
    std::cout << "    Barrier: " << ship->ship_class->defenses.barrier << std::endl;
    
    std::cout << "Components:" << std::endl;
    std::cout << "    Reactor:        " << std::endl;
    std::cout << "        Name: " << ship->components.reactor->getName() << ", Tier: "
              << (int) ship->components.reactor->getTier() <<  ", Mass: "
              << ship->components.reactor->getMass() << ", Power Use: "
              << ship->components.reactor->getPower() << std::endl;
    std::cout << "        Power Generation: " << ship->components.reactor->getPowerGen()
              << ", Fuel Rate: " << ship->components.reactor->getFuelRate() << ", Reliability: "
              << ship->components.reactor->getReliability() << std::endl;
    std::cout << "    Sublight Drive: " << std::endl;
    std::cout << "        Name: " << ship->components.sub_drive->getName() << ", Tier: "
              << (int) ship->components.sub_drive->getTier() << ", Mass: "
              << ship->components.sub_drive->getMass() << ", Power Use: "
              << ship->components.sub_drive->getPower() << std::endl;
    std::cout << "        Acceleration: " << ship->components.sub_drive->getAccel()
              << ", Maneuverability: " << ship->components.sub_drive->getManeuver()
              << ", Speed: " << ship->components.sub_drive->getSpeed() << std::endl;
    std::cout << "    FTL Drive:      " << std::endl;
    std::cout << "        Name: " << ship->components.ftl_drive->getName() << ", Tier: "
              << (int) ship->components.ftl_drive->getTier() << ", Mass: "
              << ship->components.ftl_drive->getMass() << ", Power Use: "
              << ship->components.ftl_drive->getPower() << std::endl;
    std::cout << "        Charge Rate: " << ship->components.ftl_drive->getChargeRate()
              << ", Max Hull Size: " << ship->components.ftl_drive->getMaxSize() << ", Fuel Use: "
              << ship->components.ftl_drive->getFuelUse() << std::endl;
    std::cout << "Weapons:" << std::endl;

    std::cout << "    Missiles (" << (int) ship->weapons.num_missile << ") :" << std::endl;
    for (int i = 0; i < ship->weapons.num_missile; ++i) {
        Weapon *temp = *(ship->weapons.missile_weapons + i);
        
        if (temp != EmptyWeaponSLot::no_missile) {
            std::cout << "       " << i + 1 << ". Name: " << temp->getName() << ", Tier: "
                      << (int) temp->getTier() << ", Base Damage: " << temp->getBaseDamage()
                      << ", Fire Rate: " << temp->getFireRate() << std::endl;
            std::cout << "          Range: " << temp->getRange() << ", Power Use: "
                      << temp->getPower() << std::endl;
            Missile *mis_temp = (Missile *) temp;
            std::cout << "          Speed: " << mis_temp->getSpeed() << ", Tracking: "
                      << mis_temp->getTracking() << ", Hull: " << mis_temp->getHull() << std::endl;
        } else {
            std::cout << "       " << i + 1 << ". (" << temp->getName() << ")" << std::endl;
        }
    }
    std::cout << "    Heavy Weapons (" << (int) ship->weapons.num_heavy << ") :" << std::endl;
    for (int i = 0; i < ship->weapons.num_heavy; ++i) {
        Weapon *temp = *(ship->weapons.heavy_weapons + i);
        
        if (temp != EmptyWeaponSLot::no_heavy) {
            std::cout << "       " << i + 1 << ". Name: " << temp->getName() << ", Tier: "
                      << (int) temp->getTier() << ", Base Damage: " << temp->getBaseDamage()
                      << ", Fire Rate: " << temp->getFireRate() << std::endl;
            std::cout << "          Range: " << temp->getRange() << ", Power Use: "
                      << temp->getPower() << std::endl;
            if (typeid(temp) == typeid(Beam)) {
                Beam *beam_temp = (Beam *) temp;
                std::cout << "          Effective Range: " << beam_temp->getEffRange() << std::endl;
            } else if (typeid(temp) == typeid(Kinetic)) {
                Kinetic *kin_temp = (Kinetic *) temp;
                std::cout << "          Max Ammo: " << kin_temp->getMaxAmmo()
                          << ", Current Ammo: " << kin_temp->getCurrAmmo() << std::endl;
            }
        } else {
            std::cout << "       " << i + 1 << ". (" << temp->getName() << ")" << std::endl;
        }
    }
    std::cout << "    Medium Weapons (" << (int) ship->weapons.num_medium << ") :" << std::endl;
    for (int i = 0; i < ship->weapons.num_medium; ++i) {
        Weapon *temp = *(ship->weapons.medium_weapons + i);
        
        if (temp != EmptyWeaponSLot::no_medium) {
            std::cout << "       " << i + 1 << ". Name: "<< temp->getName() << ", Tier: "
                      << (int) temp->getTier() << ", Base Damage: " << temp->getBaseDamage()
                      << ", Fire Rate: " << temp->getFireRate() << std::endl;
            std::cout << "          Range: " << temp->getRange() << ", Power Use: "
                      << temp->getPower() << std::endl;
            if (typeid(temp) == typeid(Beam)) {
                Beam *beam_temp = (Beam *) temp;
                std::cout << "          Effective Range: " << beam_temp->getEffRange() << std::endl;
            } else if (typeid(temp) == typeid(Kinetic)) {
                Kinetic *kin_temp = (Kinetic *) temp;
                std::cout << "          Max Ammo: " << kin_temp->getMaxAmmo()
                          << ", Current Ammo: " << kin_temp->getCurrAmmo() << std::endl;
            }
        } else {
            std::cout << "       " << i + 1 << ". (" << temp->getName() << ")" << std::endl;
        }
    }
    std::cout << "    Light Weapons (" << (int) ship->weapons.num_light << ") : " << std::endl;
    for (int i = 0; i < ship->weapons.num_light; ++i) {
        Weapon *temp = *(ship->weapons.light_weapons + i);
        
        if (temp != EmptyWeaponSLot::no_light) {
            std::cout << "       " << i + 1 << ". Name: " << temp->getName() << ", Tier: "
                      << (int) temp->getTier() << ", Base Damage: " << temp->getBaseDamage()
                      <<", Fire Rate: " << temp->getFireRate() << std::endl;
            std::cout << "          Range: " << temp->getRange() << ", Power Use: "
                      << temp->getPower() << std::endl;
            if (typeid(temp) == typeid(Beam)) {
                Beam *beam_temp = (Beam *) temp;
                std::cout << "          Effective Range: " << beam_temp->getEffRange() << std::endl;
            } else if (typeid(temp) == typeid(Kinetic)) {
                Kinetic *kin_temp = (Kinetic *) temp;
                std::cout << "          Max Ammo: " << kin_temp->getMaxAmmo()
                          << ", Current Ammo: " << kin_temp->getCurrAmmo() << std::endl;
            }
        } else {
            std::cout << "       " << i + 1 << ". (" << temp->getName() << ")" << std::endl;
        }
    }

    std::cout << std::endl;

    delete ship;
    delete reg;
    delete test_class;


    return 0;
}



