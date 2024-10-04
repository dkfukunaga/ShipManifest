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

        file.open();
        for (int i = 0; i < 3; ++i) {
            test_reactors[i]->serialize(file, i+1, 0);
        }
        file.hexDump();
        file.close();

        Reactor *read_reactors[3];
        for (int i = 0; i < 3; ++i) {
            read_reactors[i] = new Reactor();
        }

        file.open(OpenMode::readonly);

        for (int i = 0; i < 3; ++i) {
            index_t index = read_reactors[i]->deserialize(file);
            REQUIRE(index == i + 1);
        }

        for (int i = 0; i < 3; ++i) {
            CHECK(read_reactors[i]->name == test_reactors[i]->name);
            CHECK(read_reactors[i]->tier == test_reactors[i]->tier);
            CHECK(read_reactors[i]->mass == test_reactors[i]->mass);
            CHECK(read_reactors[i]->durability == test_reactors[i]->durability);
            CHECK(read_reactors[i]->power == test_reactors[i]->power);
            CHECK(read_reactors[i]->fuel_use == test_reactors[i]->fuel_use);
        }
    }
    file.close();
}



