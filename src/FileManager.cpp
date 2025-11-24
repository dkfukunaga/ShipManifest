

#include "FileManager.h"
#include "FileFormat.h"


// default file extensions
const std::string FileManager::INI_EXTENSION = "ini";
const std::string FileManager::INDEX_EXTENSION = "idx";
const std::string FileManager::DATA_EXTENSION = "dat";

// default ini file name
const std::string FileManager::DEFAULT_META_DATA_FILE_NAME = "shipmanifest";


void FileManager::init() {
    // read metadata and set file names

    // open databases
    //   load ini file and verify file type
    //   load dat file
}
