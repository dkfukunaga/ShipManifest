#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <cstdint>
#include <string>
#include <memory>
#include "DataFile/src/DataFile.h"


class FileManager {
public:
private:
    uint32_t                    last_uid_;
    uint16_t                    version_;

    std::unique_ptr<DataFile>   weapons_file_;
    std::unique_ptr<DataFile>   officers_file_;
    std::unique_ptr<DataFile>   ship_classes_file_;
    std::unique_ptr<DataFile>   ships_file_;

    std::string                 meta_data_file_name_;
    std::string                 weapons_file_name_;
    std::string                 officers_file_name_;
    std::string                 ship_classes_file_name_;
    std::string                 ships_file_name_;


    const std::string           INI_EXTENSION = "ini";
    const std::string           DAT_EXTENSION = "dat";
};

#endif