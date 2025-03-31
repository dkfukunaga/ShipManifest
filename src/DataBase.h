


#ifndef DATABASE_H
#define DATABASE_H

#include "..\DataFile\src\DataFile.h"
#include "Headers.h"
#include "DataRecord.h"
// #include "Component.h"
// #include "Subsystem.h"
// #include "Weapon.h"
// #include "Officer.h"
// #include "ShipClass.h"
// #include "Ship.h"
#include <vector>
#include <string>
#include <filesystem>


typedef std::pair<DataType, std::vector<offset_t>>  TableList;
typedef std::vector<offset_t>                       RecordIndex;

class Database {
private:
    DataFile*                       ship_file_;
    DataFile*                       ship_class_file_;
    DataFile*                       subsystem_file_;
    DataFile*                       weapon_file_;
    DataFile*                       officer_file_;

    std::string                     file_path;
    std::string                     ships_file;
    std::string                     ship_classes_file;
    std::string                     components_file;
    std::string                     officers_file;
    uint8_t                         db_version;

    std::string                     file_path_;
    std::string                     file_name_;
    DataFile                        db_file_;
    uint8_t                         db_version_;
    bool                            is_initialized_;

    TableList                       data_table_offsets_;
    TableList                       index_table_offsets_;
    offset_t                        eof_offset_;

    std::vector<RecordIndex>        record_indices_;
public:
    Database();

    void                            open(DataFile &file);
    void                            open(DataFile &file, FileType file_type);

    void                            setRecord(DataRecord* record);

    std::string                     getFileName(FileType file_type);
    DataRecord*                     getRecord(DataFile &file, RecordType type, index_t index);

    bool                            isInitialized();

    static const std::string        default_file_path;
    static const std::string        default_ships_file;
    static const std::string        default_ship_classes_file;
    static const std::string        default_components_file;
    static const std::string        default_officers_file;
    static const uint8_t            default_db_version;

    // RecordIndex                     ship_index_;
    // RecordIndex                     ship_class_index_;
    // RecordIndex                     subsystem_index_;
    // RecordIndex                     weapon_index_;
    // RecordIndex                     officer_index_;
private:
    void                            initFile(FileType file_type);

    void                            setFileSize(DataFile &file, filesize_t new_size);
    void                            updateFileSize(DataFile &file, filesize_t size_adj);

    void                            writeFileHeader(DataFile &file, FileType file_type, filesize_t new_size = 0, offset_t index_offset = 0);
    void                            writeSectiontHeader(DataFile &file, offset_t pos, SectionType sec_type, secsize_t new_size = 0);
    void                            writeDataRecord(DataFile &file, DataRecord &record, offset_t pos);
    void                            writeEOF(DataFile &file, offset_t pos = -1);

    FileHeader                      readFileHeader(DataFile &file);
    SectionHeader                   readSectionHeader(DataFile &file, offset_t pos);
    DataRecord*                     readDataRecord(DataFile &file, offset_t pos);
    void                            setRecordRedirect(DataFile &file, index_t index, offset_t offset);    
};

const std::string Database::default_file_path           = ".\\data\\";
const std::string Database::default_ships_file          = "ships.dat";
const std::string Database::default_ship_classes_file   = "shipclasses.dat";
const std::string Database::default_components_file     = "components.dat";
const std::string Database::default_officers_file       = "gamecharacters.dat";
const uint8_t     Database::default_db_version          = 1;



#endif