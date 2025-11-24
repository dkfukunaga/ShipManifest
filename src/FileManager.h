#pragma once
#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <cstdint>
#include <string>
#include <fstream>
#include <memory>
#include "DataFile/src/DataFile.h"

using DbFile = std::pair<std::unique_ptr<DataFile>, std::unique_ptr<DataFile>>;

class FileManager {
public:
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    static FileManager*         getInstance(std::string& meta_data_file_name) {
        if (instance_ == nullptr || instance_->meta_data_file_name_ != meta_data_file_name)
            instance_ = new FileManager(meta_data_file_name);
        return instance_;
    }

    static FileManager*         getInstance() {
        if (instance_ == nullptr)
            instance_ = new FileManager(DEFAULT_META_DATA_FILE_NAME);
        return instance_;
    }

private:
    uint32_t                        last_uid_;
    uint16_t                        version_;

    std::unique_ptr<std::fstream>   meta_data_file_;
    DbFile                          weapons_file_;
    DbFile                          officers_file_;
    DbFile                          ship_classes_file_;
    DbFile                          ships_file_;

    std::string                     meta_data_file_name_;
    std::string                     weapons_file_name_;
    std::string                     officers_file_name_;
    std::string                     ship_classes_file_name_;
    std::string                     ships_file_name_;

    static const std::string        INI_EXTENSION;
    static const std::string        INDEX_EXTENSION;
    static const std::string        DATA_EXTENSION;
    static const std::string        DEFAULT_META_DATA_FILE_NAME;

    static FileManager*             instance_;

    explicit FileManager(std::string meta_data_file_name):
        meta_data_file_name_(meta_data_file_name) {
            init();
        };

    void                            init();
};

#endif