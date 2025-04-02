


#ifndef DATABASE_H
#define DATABASE_H

#include "..\DataFile\src\DataFile.h"
#include "Headers.h"
#include "DataRecord.h"
#include "Subsystem.h"
#include "Weapon.h"
// #include "Officer.h"
// #include "ShipClass.h"
// #include "Ship.h"
// #include <vector>
#include <map>
#include <string>
#include <filesystem>

class Database {
public:
    Database();

    void                            init();

    static const std::string        default_file_path;
    static const std::string        default_ships_file;
    static const std::string        default_ship_classes_file;
    static const std::string        default_subsystems_file;
    static const std::string        default_weapons_file;
    static const std::string        default_officers_file;
    static const uint8_t            default_db_version;
private:
    std::string                     file_path_;
    DataFile                        ships_file_;
    DataFile                        ship_classes_file_;
    DataFile                        subsystems_file_;
    DataFile                        weapons_file_;
    DataFile                        game_characters_file_;
    uint8_t                         db_version_;

    // std::map<index_t, Ship>         ship_index_;
    // std::map<index_t, ShipClass>    ship_class_index_;
    std::map<index_t, Subsystem>    subsystem_index_;
    std::map<index_t, Weapon>       weapon_index_;
    // std::map<index_t, Officer>      officer_index_;

    void                            openFile(DataFile &file);
    void                            openFiles();

    void                            setFileSize(DataFile &file, filesize_t new_size);
    void                            updateFileSize(DataFile &file, filesize_t size_adj);

    void                            writeFileHeader(DataFile &file, FileType file_type, filesize_t new_size = 0, offset_t index_offset = 0);
    void                            writeSectiontHeader(DataFile &file, offset_t pos, SectionType sec_type, secsize_t new_size = 0);
    void                            writeEOF(DataFile &file, offset_t pos = -1);

    FileHeader                      readFileHeader(DataFile &file);
    SectionHeader                   readSectionHeader(DataFile &file, offset_t pos);
};

const std::string Database::default_file_path           = ".\\data\\";
const std::string Database::default_ships_file          = "ships.dat";
const std::string Database::default_ship_classes_file   = "shipclasses.dat";
const std::string Database::default_subsystems_file     = "subsystems.dat";
const std::string Database::default_weapons_file        = "weapons.dat";
const std::string Database::default_officers_file       = "gamecharacters.dat";
const uint8_t     Database::default_db_version          = 1;



#endif