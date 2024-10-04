#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "..\src\Subsystem.h"
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

        std::fstream fstr;
        fstr.open(".\\doctest\\data\\components_test.dat", std::ios::binary | std::ios::in);

        for (int i = 0; i < 3; ++i) {
            fstr.read(reinterpret_cast<char*>(&headers[i]->index), sizeof(headers[i]->index));
            fstr.read(reinterpret_cast<char*>(&headers[i]->size), sizeof(headers[i]->size));
            fstr.read(reinterpret_cast<char*>(&headers[i]->redirect), sizeof(headers[i]->redirect));

            CHECK(headers[i]->index == i+1);
            CHECK(headers[i]->size == test_reactors[i]->getSize());
            CHECK(headers[i]->redirect == 0);

            uint16_t len;

            fstr.read(reinterpret_cast<char*>(&len), sizeof(len));
            std::vector<char> buffer(len + 1);
            fstr.read(buffer.data(), len);
            buffer.data()[len] = '\0';
            read_reactors[i]->name = std::string(buffer.data());

            fstr.read(reinterpret_cast<char*>(&read_reactors[i]->tier), sizeof(read_reactors[i]->tier));
            fstr.read(reinterpret_cast<char*>(&read_reactors[i]->mass), sizeof(read_reactors[i]->mass));
            fstr.read(reinterpret_cast<char*>(&read_reactors[i]->durability), sizeof(read_reactors[i]->durability));
            fstr.read(reinterpret_cast<char*>(&read_reactors[i]->power), sizeof(read_reactors[i]->power));
            fstr.read(reinterpret_cast<char*>(&read_reactors[i]->fuel_use), sizeof(read_reactors[i]->fuel_use));

            CHECK(read_reactors[i]->name == test_reactors[i]->name);
            CHECK(read_reactors[i]->tier == test_reactors[i]->tier);
            CHECK(read_reactors[i]->mass == test_reactors[i]->mass);
            CHECK(read_reactors[i]->durability == test_reactors[i]->durability);
            CHECK(read_reactors[i]->power == test_reactors[i]->power);
            CHECK(read_reactors[i]->fuel_use == test_reactors[i]->fuel_use);

        }
        fstr.close();

        for (int i = 0; i < 3; ++i) {
            delete test_reactors[i];
            delete headers[i];
            delete read_reactors[i];
        }

    }

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



