#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <cstdint>
#include <string>
#include <memory>

class DataFile;

class FileManager {
public:
private:
    uint32_t                    last_uid;
    uint16_t                    version;

    std::unique_ptr<DataFile>   weapons_file;
    std::unique_ptr<DataFile>   officers_file;
    std::unique_ptr<DataFile>   ship_classes_file;
    std::unique_ptr<DataFile>   ships_file;

    std::string                 meta_data_file_name;
    std::string                 weapons_file_name;
    std::string                 officers_file_name;
    std::string                 ship_classes_file_name;
    std::string                 ships_file_name;


    const std::string           INI_EXTENSION = "ini";
    const std::string           DAT_EXTENSION = "dat";
};

#endif