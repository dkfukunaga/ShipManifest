

#include "testItem.cpp"
#include <iostream>
#include <filesystem>

int main() {
    std::string str_1 = "Hello world!";
    std::string str_2 = "This is the song that doesn't end, yes it goes on and on my "
                        "friend! Some people started singing it not knowing what it "
                        "was, and they'll continue singing it forever just because...";

    TestItem write_test_1(str_1, 0xEFCDAB8967452301, 420.69);
    TestItem write_test_2(str_2, 0x1032547698BADCFE, 69.420);
    short foot_2[6] = {1, 17, 273, 4369, -1, 15001};
    std::copy(std::begin(foot_2), std::end(foot_2), std::begin(write_test_2.test_foot));

    std::cout << "Test 1: \n" << write_test_1.toString() << "\n\n";
    std::cout << "Test 2: \n" << write_test_2.toString() << "\n\n";

    std::cout << "Test 1 size: " << write_test_1.getSize() << "\n";
    std::cout << "Test 2 size: " << write_test_2.getSize() << "\n";
    std::cout << "Total size:  " << write_test_1.getSize() + write_test_2.getSize()
              << "\n\n";
    
    // DataFile file("test.dat");
    DataFile file;
    file.setFileExtension(".dat");
    file.setFileName("test");
    file.setFilePath(".\\doctest\\data\\");
    file.open(OpenMode::overwrite);

    // file.setWritePos(0);
    write_test_1.serialize(file);
    write_test_2.serialize(file, write_test_1.getSize());

    file.close();
    file.open(OpenMode::readonly);
    file.hexDump();
    file.hexDump(0, write_test_1.getSize());
    file.hexDump(write_test_1.getSize(), write_test_2.getSize());

    std::cout << "\n";
    TestItem read_test_1;
    TestItem read_test_2;
    TestItem read_test_3;
    TestItem read_test_4;
    TestItem read_test_5;
    file.setReadPos(0);
    read_test_1.deserialize(file);
    read_test_2.deserialize(file);
    read_test_3.deserialize(file, write_test_1.getSize());
    read_test_4.deserialize(file, 0);
    // read_test_1.serialize(file);
    // file.hexDump();

    file.close();
    file.open(OpenMode::edit);
    file.setWritePosEnd();
    write_test_1.serialize(file);
    file.close();
    file.open(OpenMode::readonly);
    std::cout << "test\n";
    file.hexDump();

    file.setReadPos(read_test_1.getSize() + read_test_2.getSize());
    read_test_5.deserialize(file);

    std::cout << "Test 1: \n" << read_test_1.toString() << "\n\n";
    std::cout << "Test 2: \n" << read_test_2.toString() << "\n\n";
    std::cout << "Test 3: \n" << read_test_3.toString() << "\n\n";
    std::cout << "Test 4: \n" << read_test_4.toString() << "\n\n";
    std::cout << "Test 5: \n" << read_test_5.toString() << "\n\n";

    file.close();

    // get list of files in directory

    std::vector<std::string> paths;
    paths.push_back(".\\doctest\\");

    int slash_index, dot_index;
    std::string temp;

    for (int i = 0; i < paths.size(); ++i) {
        std::cout << paths[i] << std::endl;
        for (const auto &entry : std::filesystem::directory_iterator(paths[i])) {
            slash_index = entry.path().string().find_last_of("\\");
            if (slash_index != std::string::npos) {
                dot_index = entry.path().string().substr(slash_index).find_last_of('.');
                if (dot_index == std::string::npos) {
                    paths.push_back(entry.path().string());
                }
            }
            slash_index = entry.path().string().find_last_of("\\");
            std::cout << "    " << entry.path().string().substr(++slash_index) << std::endl;
        }
    std::cout << std::endl;
    }

    // path: .\doctest\
    //   .\doctest\data
    //   .\doctest\DataFileTest.cpp
    //   .\doctest\doctest.h
    //   .\doctest\testDriver.cpp
    //   .\doctest\testItem.cpp
    //   .\doctest\testItem.h
    //
    // path: .\doctest\data
    //   .\doctest\data\test.dat
    //   .\doctest\data\test_file.dt2
    //   .\doctest\data\test_name.dat

    return 0;
}