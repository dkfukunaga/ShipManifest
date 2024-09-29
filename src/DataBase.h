


#ifndef DATABASE_H
#define DATABASE_H

#include "DataFile.h"
#include "Headers.h"
// #include "Ship.h"
// #include "ShipClass.h"
// #include "Subsystem.h"
// #include "Weapon.h"
// #include "Officer.h"
// #include <vector>
#include <map>
#include <string>
#include <filesystem>

class DataBase {
public:
    DataBase();

    static const std::string default_file_path;
    static const std::string default_ship_file;
    static const std::string default_ship_class_file;
    static const std::string default_ship_component_file;
    static const std::string default_game_character_file;
private:
    std::string                     file_path_;
    DataFile                        ships_file_;
    DataFile                        ship_classes_file_;
    DataFile                        ship_components_file_;
    DataFile                        game_characters_file_;

    // std::map<index_t, Ship>         ship_index_;
    // std::map<index_t, ShipClass>    ship_class_index_;
    // std::map<index_t, Subsystem>    subsystem_index_;
    // std::map<index_t, Weapon>       weapon_index_;
    // std::map<index_t, Officer>      officer_index_;

    void                            openFile(DataFile &file);
    void                            openFiles();
    void                            initializeFile(DataFile &file, FileType file_type);
    FileHeader                      readHeader(DataFile &file);
};

const std::string DataBase::default_file_path = ".\\data\\";
const std::string DataBase::default_ship_file = "shipdb.dat";
const std::string DataBase::default_ship_class_file = "shipclassdb.dat";
const std::string DataBase::default_ship_component_file = "shipcomponentdb.dat";
const std::string DataBase::default_game_character_file = "gamecharacterdb.dat";



#endif