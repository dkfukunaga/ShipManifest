
#include "Database.h"



void Database::setFileSize(DataFile &file, filesize_t len) {
    FileHeader header = readFileHeader(file);

    header.size = len;

    header.serialize(file, 0);
}

void Database::updateFileSize(DataFile &file, filesize_t len) {
    FileHeader header = readFileHeader(file);

    header.size += len;

    header.serialize(file, 0);
}

void Database::writeFileHeader(DataFile &file, FileType file_type, filesize_t len, offset_t index_offset) {
    FileHeader header{
        .sig            = FileSig::ship_registry,
        .flags          = FileFlags::good,
        .version        = default_db_version,
        .type           = file_type,
        .size           = sizeof(header) + len,
        .index_offset   = index_offset
    };

    header.serialize(file, 0);
}

void Database::writeSectiontHeader(DataFile &file, offset_t pos, SectionType sec_type, secsize_t len) {
    SectionHeader header{
        .size = len,
        .type = sec_type
    };

    header.serialize(file, pos);

    updateFileSize(file, sizeof(header));
}

void Database::writeEOF(DataFile &file, offset_t pos) {
    SectionHeader end {
        .size = 0,
        .type = SectionType::eof
    };

    end.serialize(file, pos);

    updateFileSize(file, sizeof(end));
}

FileHeader Database::readFileHeader(DataFile &file) {
    FileHeader header;

    header.deserialize(file, 0);

    return header;
}



