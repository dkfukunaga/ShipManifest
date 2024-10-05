#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "..\src\Subsystem.h"
#include "..\src\Weapon.h"
#include "..\src\Serializable.h"
#include "..\src\Headers.h"
#include "..\src\DataFile.h"
#include <string>
#include <fstream>


std::string file_name("components_test");
std::string file_path(".\\doctest\\data\\");



TEST_CASE("Serialization test") {
    DataFile file(file_name, file_path, OpenMode::overwrite);
    REQUIRE(file.getFileSize() == 0);
    file.close();

    SUBCASE("Subsystem test") {
        Subsystem *test_subsystems[6];
        test_subsystems[0] = new Reactor("Test reactor 1", 1, 50, 100, 100, 2);
        test_subsystems[1] = new Thrusters("Test thruster 1", 2, 55, 150, 200, 10, 10);
        test_subsystems[2] = new FTLdrive("Test ftldrive 1", 3, 60, 175, 250, 2);
        test_subsystems[3] = new Computer("Test computer 1", 1, 50, 100, 100, 10, 25);
        test_subsystems[4] = new Armor("Test armor 1", 2, 55, 150, 200, 15, 5);
        test_subsystems[5] = new Shields("Test shields 1", 3, 60, 175, 250, 20, 125, 10);

        offset_t offsets[6];

        file.open();
        for (int i = 0; i < 6; ++i) {
            switch (test_subsystems[i]->type) {
                case SubsystemType::reactor: {
                    Reactor *temp = (Reactor*) test_subsystems[i];
                    offsets[i] = temp->serialize(file, i + 1, 0);
                    break;
                }
                case SubsystemType::thrusters: {
                    Thrusters *temp = (Thrusters*) test_subsystems[i];
                    offsets[i] = temp->serialize(file, i + 1, 0);
                    break;
                }
                case SubsystemType::ftldrive: {
                    FTLdrive *temp = (FTLdrive*) test_subsystems[i];
                    offsets[i] = temp->serialize(file, i + 1, 0);
                    break;
                }
                case SubsystemType::computer: {
                    Computer *temp = (Computer*) test_subsystems[i];
                    offsets[i] = temp->serialize(file, i + 1, 0);
                    break;
                }
                case SubsystemType::armor: {
                    Armor *temp = (Armor*) test_subsystems[i];
                    offsets[i] = temp->serialize(file, i + 1, 0);
                    break;
                }
                case SubsystemType::shields: {
                    Shields *temp = (Shields*) test_subsystems[i];
                    offsets[i] = temp->serialize(file, i + 1, 0);
                    break;
                }
            }
        }
        file.hexDump();
        file.close();
        for (int i = 0; i < 6; ++i) {
            printf("Index %d: offset %3d (0x%02X)\n", i + 1, offsets[i], offsets[i]);
        }

        DataRecordHeader *headers[6];
        for (int i = 0; i < 6; ++i) {
            headers[i] = new DataRecordHeader();
        }

        Subsystem *read_subsystems[6];
        read_subsystems[0] = new Reactor();
        read_subsystems[1] = new Thrusters();
        read_subsystems[2] = new FTLdrive();
        read_subsystems[3] = new Computer();
        read_subsystems[4] = new Armor();
        read_subsystems[5] = new Shields();

        std::fstream in_file;
        in_file.open(".\\doctest\\data\\components_test.dat", std::ios::binary | std::ios::in);

        for (int i = 0; i < 6; ++i) {
            in_file.read(reinterpret_cast<char*>(&headers[i]->index), sizeof(headers[i]->index));
            in_file.read(reinterpret_cast<char*>(&headers[i]->size), sizeof(headers[i]->size));
            in_file.read(reinterpret_cast<char*>(&headers[i]->redirect), sizeof(headers[i]->redirect));

            CHECK(headers[i]->index == i+1);
            CHECK(headers[i]->size == test_subsystems[i]->getSize());
            CHECK(headers[i]->redirect == 0);

            uint16_t len;

            in_file.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::vector<char> buffer(len + 1);
            in_file.read(buffer.data(), len);
            buffer.data()[len] = '\0';
            read_subsystems[i]->name = std::string(buffer.data());

            in_file.read(reinterpret_cast<char*>(&read_subsystems[i]->tier), sizeof(read_subsystems[i]->tier));
            in_file.read(reinterpret_cast<char*>(&read_subsystems[i]->mass), sizeof(read_subsystems[i]->mass));
            in_file.read(reinterpret_cast<char*>(&read_subsystems[i]->durability), sizeof(read_subsystems[i]->durability));
            in_file.read(reinterpret_cast<char*>(&read_subsystems[i]->power), sizeof(read_subsystems[i]->power));

            CHECK(read_subsystems[i]->name == test_subsystems[i]->name);
            CHECK(read_subsystems[i]->tier == test_subsystems[i]->tier);
            CHECK(read_subsystems[i]->mass == test_subsystems[i]->mass);
            CHECK(read_subsystems[i]->durability == test_subsystems[i]->durability);
            CHECK(read_subsystems[i]->power == test_subsystems[i]->power);

            switch (read_subsystems[i]->type) {
                case SubsystemType::reactor: {
                    Reactor *temp1 = (Reactor*) read_subsystems[i];
                    Reactor *temp2 = (Reactor*) test_subsystems[i];

                    in_file.read(reinterpret_cast<char*>(&temp1->fuel_use), sizeof(temp1->fuel_use));
                    
                    CHECK(temp1->fuel_use == temp2->fuel_use);
                    break;
                }
                case SubsystemType::thrusters: {
                    Thrusters *temp1 = (Thrusters*) read_subsystems[i];
                    Thrusters *temp2 = (Thrusters*) test_subsystems[i];

                    in_file.read(reinterpret_cast<char*>(&temp1->speed), sizeof(temp1->speed));
                    in_file.read(reinterpret_cast<char*>(&temp1->maneuver), sizeof(temp1->maneuver));
                    
                    CHECK(temp1->speed == temp2->speed);
                    CHECK(temp1->maneuver == temp2->maneuver);
                    break;
                }
                case SubsystemType::ftldrive: {
                    FTLdrive *temp1 = (FTLdrive*) read_subsystems[i];
                    FTLdrive *temp2 = (FTLdrive*) test_subsystems[i];

                    in_file.read(reinterpret_cast<char*>(&temp1->ftl_rating), sizeof(temp1->ftl_rating));
                    
                    CHECK(temp1->ftl_rating == temp2->ftl_rating);
                    break;
                }
                case SubsystemType::computer: {
                    Computer *temp1 = (Computer*) read_subsystems[i];
                    Computer *temp2 = (Computer*) test_subsystems[i];

                    in_file.read(reinterpret_cast<char*>(&temp1->processing_power), sizeof(temp1->processing_power));
                    in_file.read(reinterpret_cast<char*>(&temp1->memory), sizeof(temp1->memory));
                    
                    CHECK(temp1->processing_power == temp2->processing_power);
                    CHECK(temp1->memory == temp2->memory);
                    break;
                }
                case SubsystemType::armor: {
                    Armor *temp1 = (Armor*) read_subsystems[i];
                    Armor *temp2 = (Armor*) test_subsystems[i];

                    in_file.read(reinterpret_cast<char*>(&temp1->armor_rating), sizeof(temp1->armor_rating));
                    in_file.read(reinterpret_cast<char*>(&temp1->hardness), sizeof(temp1->hardness));
                    
                    CHECK(temp1->armor_rating == temp2->armor_rating);
                    CHECK(temp1->hardness == temp2->hardness);
                    break;
                }
                case SubsystemType::shields: {
                    Shields *temp1 = (Shields*) read_subsystems[i];
                    Shields *temp2 = (Shields*) test_subsystems[i];

                    in_file.read(reinterpret_cast<char*>(&temp1->damage_reduction), sizeof(temp1->damage_reduction));
                    in_file.read(reinterpret_cast<char*>(&temp1->max_strength), sizeof(temp1->max_strength));
                    in_file.read(reinterpret_cast<char*>(&temp1->recharge_rate), sizeof(temp1->recharge_rate));
                    
                    CHECK(temp1->damage_reduction == temp2->damage_reduction);
                    CHECK(temp1->max_strength == temp2->max_strength);
                    CHECK(temp1->recharge_rate == temp2->recharge_rate);
                    break;
                }
            }

        }

        in_file.close();

        for (int i = 0; i < 3; ++i) {
            delete test_subsystems[i];
            delete headers[i];
            delete read_subsystems[i];
        }
    }

    SUBCASE("Weapon test") {
        Weapon *test_weapons[3];
        test_weapons[0] = new MassDriver("MassDriver 1", 1, 5, 25, 5, WeaponSize::light, DamageType::kinetic,
                                      8, 100, 100, 500);
        test_weapons[1] = new Beam("Beam 1", 2, 8, 30, 20, WeaponSize::light, DamageType::energy,
                                   12, 100, 10, 5, 55);
        test_weapons[2] = new Missile("Missile 1", 5, 15, 20, 5, WeaponSize::heavy, DamageType::explosive,
                                      350, 100, 100, 30, 30);
        
        offset_t offsets[3];

        file.open();
        for (int i = 0; i < 3; ++i) {
            if (typeid(*test_weapons[i]) == typeid(MassDriver)) {
                MassDriver *temp = (MassDriver*) test_weapons[i];
                offsets[i] = temp->serialize(file, i + 1, 0);
            } else if (typeid(*test_weapons[i]) == typeid(Beam)) {
                Beam *temp = (Beam*) test_weapons[i];
                offsets[i] = temp->serialize(file, i + 1, 0);
            } else if (typeid(*test_weapons[i]) == typeid(Missile)) {
                Missile *temp = (Missile*) test_weapons[i];
                offsets[i] = temp->serialize(file, i + 1, 0);
            }
        }
        file.hexDump();
        file.close();
        for (int i = 0; i < 3; ++i) {
            printf("Index %d: offset %3d (0x%02X)\n", i + 1, offsets[i], offsets[i]);
        }

        DataRecordHeader *headers[3];
        for (int i = 0; i < 3; ++i) {
            headers[i] = new DataRecordHeader();
        }

        Weapon *read_weapons[3];
        read_weapons[0] = new MassDriver();
        read_weapons[1] = new Beam();
        read_weapons[2] = new Missile();

        std::fstream in_file;
        in_file.open(".\\doctest\\data\\components_test.dat", std::ios::binary | std::ios::in);

        for (int i = 0; i < 3; ++i) {
            in_file.read(reinterpret_cast<char*>(&headers[i]->index), sizeof(headers[i]->index));
            in_file.read(reinterpret_cast<char*>(&headers[i]->size), sizeof(headers[i]->size));
            in_file.read(reinterpret_cast<char*>(&headers[i]->redirect), sizeof(headers[i]->redirect));

            CHECK(headers[i]->index == i+1);
            CHECK(headers[i]->size == test_weapons[i]->getSize());
            CHECK(headers[i]->redirect == 0);

            uint16_t len;

            in_file.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::vector<char> buffer(len + 1);
            in_file.read(buffer.data(), len);
            buffer.data()[len] = '\0';
            read_weapons[i]->name = std::string(buffer.data());

            in_file.read(reinterpret_cast<char*>(&read_weapons[i]->tier), sizeof(read_weapons[i]->tier));
            in_file.read(reinterpret_cast<char*>(&read_weapons[i]->mass), sizeof(read_weapons[i]->mass));
            in_file.read(reinterpret_cast<char*>(&read_weapons[i]->durability), sizeof(read_weapons[i]->durability));
            in_file.read(reinterpret_cast<char*>(&read_weapons[i]->power), sizeof(read_weapons[i]->power));
            in_file.read(reinterpret_cast<char*>(&read_weapons[i]->size_class), sizeof(read_weapons[i]->size_class));
            in_file.read(reinterpret_cast<char*>(&read_weapons[i]->damage_type), sizeof(read_weapons[i]->damage_type));
            in_file.read(reinterpret_cast<char*>(&read_weapons[i]->damage), sizeof(read_weapons[i]->damage));
            in_file.read(reinterpret_cast<char*>(&read_weapons[i]->range), sizeof(read_weapons[i]->range));

            CHECK(read_weapons[i]->name == read_weapons[i]->name);
            CHECK(read_weapons[i]->tier == read_weapons[i]->tier);
            CHECK(read_weapons[i]->mass == read_weapons[i]->mass);
            CHECK(read_weapons[i]->durability == read_weapons[i]->durability);
            CHECK(read_weapons[i]->power == read_weapons[i]->power);
            CHECK(read_weapons[i]->size_class == read_weapons[i]->size_class);
            CHECK(read_weapons[i]->damage_type == read_weapons[i]->damage_type);
            CHECK(read_weapons[i]->damage == read_weapons[i]->damage);
            CHECK(read_weapons[i]->range == read_weapons[i]->range);

            if (typeid(*test_weapons[i]) == typeid(MassDriver)) {
                MassDriver *temp1 = (MassDriver*) read_weapons[i];
                MassDriver *temp2 = (MassDriver*) test_weapons[i];

                in_file.read(reinterpret_cast<char*>(&temp1->velocity), sizeof(temp1->velocity));
                in_file.read(reinterpret_cast<char*>(&temp1->ammo_capacity), sizeof(temp1->ammo_capacity));

                CHECK(temp1->velocity == temp2->velocity);
                CHECK(temp1->ammo_capacity == temp2->ammo_capacity);
            } else if (typeid(*test_weapons[i]) == typeid(Beam)) {
                Beam *temp1 = (Beam*) read_weapons[i];
                Beam *temp2 = (Beam*) test_weapons[i];

                in_file.read(reinterpret_cast<char*>(&temp1->shield_penetration), sizeof(temp1->shield_penetration));
                in_file.read(reinterpret_cast<char*>(&temp1->range_penalty), sizeof(temp1->range_penalty));
                in_file.read(reinterpret_cast<char*>(&temp1->capacitor_charge), sizeof(temp1->capacitor_charge));

                CHECK(temp1->shield_penetration == temp2->shield_penetration);
                CHECK(temp1->range_penalty == temp2->range_penalty);
                CHECK(temp1->capacitor_charge == temp2->capacitor_charge);
            } else if (typeid(*test_weapons[i]) == typeid(Missile)) {
                Missile *temp1 = (Missile*) read_weapons[i];
                Missile *temp2 = (Missile*) test_weapons[i];

                in_file.read(reinterpret_cast<char*>(&temp1->velocity), sizeof(temp1->velocity));
                in_file.read(reinterpret_cast<char*>(&temp1->evasion), sizeof(temp1->evasion));
                in_file.read(reinterpret_cast<char*>(&temp1->tracking), sizeof(temp1->tracking));

                CHECK(temp1->velocity == temp2->velocity);
                CHECK(temp1->evasion == temp2->evasion);
                CHECK(temp1->tracking == temp2->tracking);
            }
        }

        for (int i = 0; i < 3; ++i) {
            delete test_weapons[i];
        }
        for (int i = 0; i < 3; ++i) {
            delete headers[i];
        }
        for (int i = 0; i < 3; ++i) {
            delete read_weapons[i];
        }
    }

    file.close();
}

TEST_CASE("Deserialization test") {
    
    DataFile file(file_name, file_path, OpenMode::overwrite);
    REQUIRE(file.getFileSize() == 0);
    file.close();

    SUBCASE("Reactor test") {
        Reactor *test_subsystems[3];
        test_subsystems[0] = new Reactor("Test reactor 1", 1, 50, 100, 100, 2);
        test_subsystems[1] = new Reactor("Test reactor 2", 2, 55, 150, 200, 3);
        test_subsystems[2] = new Reactor("Test reactor 3", 3, 60, 175, 250, 3);

        offset_t offsets[3];
        file.open();
        for (int i = 0; i < 2; ++i) {
            offsets[i] = test_subsystems[i]->serialize(file, i + 1, 0);
            
        }
        // manually change redirect of 3rd record to point to record 2
        offsets[2] = test_subsystems[2]->serialize(file, 0, offsets[1]);
        // offset_t test_redirect = offsets[1];
        // file.write(&test_redirect, offsets[2] + 4); // + 4 to skip index and size
        file.hexDump();
        file.close();
        for (int i = 0; i < 3; ++i) {
            printf("Index %d: offset %3d (0x%02X)\n", i + 1, offsets[i], offsets[i]);
        }

        Reactor *read_subsystems[4];
        for (int i = 0; i < 4; ++i) {
            read_subsystems[i] = new Reactor();
        }

        file.open(OpenMode::readonly);

        index_t index;
        for (int i = 0; i < 2; ++i) {
            index = read_subsystems[i]->deserialize(file);
            REQUIRE(index == i + 1);
        }
        index = read_subsystems[2]->deserialize(file, offsets[2]);
        REQUIRE(index == 2);
        index = read_subsystems[3]->deserialize(file, offsets[1]);
        REQUIRE(index == 2);

        for (int i = 0; i < 2; ++i) {
            CHECK(read_subsystems[i]->name == test_subsystems[i]->name);
            CHECK(read_subsystems[i]->tier == test_subsystems[i]->tier);
            CHECK(read_subsystems[i]->mass == test_subsystems[i]->mass);
            CHECK(read_subsystems[i]->durability == test_subsystems[i]->durability);
            CHECK(read_subsystems[i]->power == test_subsystems[i]->power);
            CHECK(read_subsystems[i]->fuel_use == test_subsystems[i]->fuel_use);
        }

        CHECK(read_subsystems[2]->name == test_subsystems[1]->name);
        CHECK(read_subsystems[2]->tier == test_subsystems[1]->tier);
        CHECK(read_subsystems[2]->mass == test_subsystems[1]->mass);
        CHECK(read_subsystems[2]->durability == test_subsystems[1]->durability);
        CHECK(read_subsystems[2]->power == test_subsystems[1]->power);
        CHECK(read_subsystems[2]->fuel_use == test_subsystems[1]->fuel_use);

        CHECK(read_subsystems[3]->name == test_subsystems[1]->name);
        CHECK(read_subsystems[3]->tier == test_subsystems[1]->tier);
        CHECK(read_subsystems[3]->mass == test_subsystems[1]->mass);
        CHECK(read_subsystems[3]->durability == test_subsystems[1]->durability);
        CHECK(read_subsystems[3]->power == test_subsystems[1]->power);
        CHECK(read_subsystems[3]->fuel_use == test_subsystems[1]->fuel_use);
    }
    file.close();
}



