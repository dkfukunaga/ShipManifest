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

    SUBCASE("Reactor test") {
        Reactor *test_reactors[3];
        test_reactors[0] = new Reactor("Test reactor 1", 1, 50, 100, 100, 2);
        test_reactors[1] = new Reactor("Test reactor 2", 2, 55, 150, 200, 3);
        test_reactors[2] = new Reactor("Test reactor 3", 3, 60, 175, 250, 3);

        file.open();
        for (int i = 0; i < 3; ++i) {
            test_reactors[i]->serialize(file, i+1, 0);
        }
        file.hexDump();
        file.close();

        DataRecordHeader *headers[3];
        for (int i = 0; i < 3; ++i) {
            headers[i] = new DataRecordHeader();
        }

        Reactor *read_reactors[3];
        for (int i = 0; i < 3; ++i) {
            read_reactors[i] = new Reactor();
        }

        std::fstream in_file;
        in_file.open(".\\doctest\\data\\components_test.dat", std::ios::binary | std::ios::in);

        for (int i = 0; i < 3; ++i) {
            in_file.read(reinterpret_cast<char*>(&headers[i]->index), sizeof(headers[i]->index));
            in_file.read(reinterpret_cast<char*>(&headers[i]->size), sizeof(headers[i]->size));
            in_file.read(reinterpret_cast<char*>(&headers[i]->redirect), sizeof(headers[i]->redirect));

            CHECK(headers[i]->index == i+1);
            CHECK(headers[i]->size == test_reactors[i]->getSize());
            CHECK(headers[i]->redirect == 0);

            uint16_t len;

            in_file.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::vector<char> buffer(len + 1);
            in_file.read(buffer.data(), len);
            buffer.data()[len] = '\0';
            read_reactors[i]->name = std::string(buffer.data());

            in_file.read(reinterpret_cast<char*>(&read_reactors[i]->tier), sizeof(read_reactors[i]->tier));
            in_file.read(reinterpret_cast<char*>(&read_reactors[i]->mass), sizeof(read_reactors[i]->mass));
            in_file.read(reinterpret_cast<char*>(&read_reactors[i]->durability), sizeof(read_reactors[i]->durability));
            in_file.read(reinterpret_cast<char*>(&read_reactors[i]->power), sizeof(read_reactors[i]->power));
            in_file.read(reinterpret_cast<char*>(&read_reactors[i]->fuel_use), sizeof(read_reactors[i]->fuel_use));

            CHECK(read_reactors[i]->name == test_reactors[i]->name);
            CHECK(read_reactors[i]->tier == test_reactors[i]->tier);
            CHECK(read_reactors[i]->mass == test_reactors[i]->mass);
            CHECK(read_reactors[i]->durability == test_reactors[i]->durability);
            CHECK(read_reactors[i]->power == test_reactors[i]->power);
            CHECK(read_reactors[i]->fuel_use == test_reactors[i]->fuel_use);

        }
        in_file.close();

        for (int i = 0; i < 3; ++i) {
            delete test_reactors[i];
            delete headers[i];
            delete read_reactors[i];
        }
    }

    SUBCASE("Weapon test") {
        Weapon *test_weapons[3];
        test_weapons[0] = new Kinetic("Kinetic 1", 1, 5, 25, 5, WeaponSize::light, DamageType::kinetic,
                                      8, 100, 100, 500);
        test_weapons[1] = new Beam("Beam 1", 2, 8, 30, 20, WeaponSize::light, DamageType::energy,
                                   12, 100, 10, 5, 55);
        test_weapons[2] = new Missile("Missile 1", 5, 15, 20, 5, WeaponSize::heavy, DamageType::explosive,
                                      350, 100, 100, 30, 30);
        
        offset_t offsets[3];

        file.open();
        for (int i = 0; i < 3; ++i) {
            if (typeid(*test_weapons[i]) == typeid(Kinetic)) {
                Kinetic *temp = (Kinetic*) test_weapons[i];
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
            printf("Test weapon %d - offset %d (0x%02X)\n", i+1, offsets[i], offsets[i]);
        }

        DataRecordHeader *headers[3];
        for (int i = 0; i < 3; ++i) {
            headers[i] = new DataRecordHeader();
        }

        Weapon *read_weapons[3];
        read_weapons[0] = new Kinetic();
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

            if (typeid(*test_weapons[i]) == typeid(Kinetic)) {
                Kinetic *temp1 = (Kinetic*) read_weapons[i];
                Kinetic *temp2 = (Kinetic*) test_weapons[i];

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

    // WeaponSize     size_class      = WeaponSize::light;
    // DamageType          damage_type     = DamageType::kinetic;
    // int32_t             damage          = 0;
    // int32_t             range           = 0;
    file.close();
}

TEST_CASE("Deserialization test") {
    
    DataFile file(file_name, file_path, OpenMode::overwrite);
    REQUIRE(file.getFileSize() == 0);
    file.close();

    SUBCASE("Reactor test") {
        Reactor *test_reactors[3];
        test_reactors[0] = new Reactor("Test reactor 1", 1, 50, 100, 100, 2);
        test_reactors[1] = new Reactor("Test reactor 2", 2, 55, 150, 200, 3);
        test_reactors[2] = new Reactor("Test reactor 3", 3, 60, 175, 250, 3);

        offset_t offsets[3];
        file.open();
        for (int i = 0; i < 2; ++i) {
            offsets[i] = test_reactors[i]->serialize(file, i + 1, 0);
            
        }
        // manually change redirect of 3rd record to point to record 2
        offsets[2] = test_reactors[2]->serialize(file, 0, offsets[1]);
        // offset_t test_redirect = offsets[1];
        // file.write(&test_redirect, offsets[2] + 4); // + 4 to skip index and size
        file.hexDump();
        file.close();
        for (int i = 0; i < 3; ++i) {
            printf("Test reactor %d - offset %d (0x%02X)\n", i+1, offsets[i], offsets[i]);
        }

        Reactor *read_reactors[4];
        for (int i = 0; i < 4; ++i) {
            read_reactors[i] = new Reactor();
        }

        file.open(OpenMode::readonly);

        index_t index;
        for (int i = 0; i < 2; ++i) {
            index = read_reactors[i]->deserialize(file);
            REQUIRE(index == i + 1);
        }
        index = read_reactors[2]->deserialize(file, offsets[2]);
        REQUIRE(index == 2);
        index = read_reactors[3]->deserialize(file, offsets[1]);
        REQUIRE(index == 2);

        for (int i = 0; i < 2; ++i) {
            CHECK(read_reactors[i]->name == test_reactors[i]->name);
            CHECK(read_reactors[i]->tier == test_reactors[i]->tier);
            CHECK(read_reactors[i]->mass == test_reactors[i]->mass);
            CHECK(read_reactors[i]->durability == test_reactors[i]->durability);
            CHECK(read_reactors[i]->power == test_reactors[i]->power);
            CHECK(read_reactors[i]->fuel_use == test_reactors[i]->fuel_use);
        }

        CHECK(read_reactors[2]->name == test_reactors[1]->name);
        CHECK(read_reactors[2]->tier == test_reactors[1]->tier);
        CHECK(read_reactors[2]->mass == test_reactors[1]->mass);
        CHECK(read_reactors[2]->durability == test_reactors[1]->durability);
        CHECK(read_reactors[2]->power == test_reactors[1]->power);
        CHECK(read_reactors[2]->fuel_use == test_reactors[1]->fuel_use);

        CHECK(read_reactors[3]->name == test_reactors[1]->name);
        CHECK(read_reactors[3]->tier == test_reactors[1]->tier);
        CHECK(read_reactors[3]->mass == test_reactors[1]->mass);
        CHECK(read_reactors[3]->durability == test_reactors[1]->durability);
        CHECK(read_reactors[3]->power == test_reactors[1]->power);
        CHECK(read_reactors[3]->fuel_use == test_reactors[1]->fuel_use);
    }
    file.close();
}



