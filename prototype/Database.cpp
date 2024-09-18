

#include "Database.h"

void dummy() {
    
FileHeader file_header;
file_header.file_type = FileCode::ships;
}

std::string     Database::default_file_name_        = "default.dat";
MagicBytes      Database::default_magic_bytes_;//   = {0xCA, 0x70, 0xCA, 0xFE, 0x53, 0x48, 0x49, 0x50};


char            Database::default_file_version_     = 1;
FileFlags       Database::initial_file_flags_       = FileFlags::good;
FileHeader      Database::file_header_template_;//     = {default_magic_bytes_, FileType("    "),
                                                    //    default_file_version_, (uint8_t) initial_file_flags_,
                                                    //    sizeof(FileHeader), sizeof(FileHeader),
                                                    //    sizeof(FileHeader) + sizeof(IndexHeader)};
IndexHeader     Database::empty_index_header_       = {sizeof(IndexHeader)};
uint8_t         Database::default_eof_[2]           = {0x0E, 0x0F};


Database::Database() {
    openFile(default_file_name_);
}
Database::Database(std::string file_name) {
    openFile(file_name);
}

Database::~Database() {
    if (database_->is_open()) {
        database_->close();
    }
    delete database_;
}



bool Database::openFile(std::string file_name) {
    database_ = new std::fstream{file_name, std::ios::binary | std::ios::in | std::ios::out};

    
    // if file not opened (doesn't exist), use ofstream to create one with same name
    // then close ofstream, open file as fstream, and initFile to initialize the counter to 0
    if (!*database_) {
        delete database_;
        std::ofstream* temp_stream = new std::ofstream(file_name);
        temp_stream->close();
        // delete temp_stream;
        database_ = new std::fstream{file_name, std::ios::binary | std::ios::in | std::ios::out};
        initFile();
    }
}

bool Database::atEOF(int) {
    // save current read pointer position
    auto curr_pos = database_->tellg();

    // read next two bytes
    uint8_t two_bytes[2];
    read(two_bytes, sizeof(two_bytes[0]) * 2);

    // if they match the EOF bytes return true
    if (two_bytes[0] == default_eof_[0] && two_bytes[1] == default_eof_[1]) {
        return true;
    }

    // otherwise move read pointer to previous location and return false
    moveReadPointer(curr_pos);
    return false;
}

void Database::moveWritePointer(long long offset) {
    database_->seekp(offset, std::ios::beg);
}

void Database::moveReadPointer(long long offset) {
    database_->seekg(offset, std::ios::beg);
}


void Database::write(void *data, int size, long long pos) {
    moveWritePointer(pos);
    database_->write(reinterpret_cast<char*>(data), size);
}

void Database::write(void *data, int size) {
    database_->write(reinterpret_cast<char*>(data), size);
}

void Database::read(void *data, int size, long long pos) {
    moveReadPointer(pos);
    database_->read(reinterpret_cast<char*>(data), size);
}

void Database::read(void *data, int size) {
    database_->read(reinterpret_cast<char*>(data), size);
}

void Database::initFile() {
    // make sure write pointer is at file start
    moveWritePointer(0);

    // write file header template
    write(&file_header_template_.magic_bites, sizeof(file_header_template_.magic_bites));
    write(&file_header_template_.file_type, sizeof(file_header_template_.file_type));
    write(&file_header_template_.file_version, sizeof(file_header_template_.file_version));
    write(&file_header_template_.file_flags, sizeof(file_header_template_.file_flags));
    write(&file_header_template_.file_size, sizeof(file_header_template_.file_size));
    write(&file_header_template_.index_offset, sizeof(file_header_template_.index_offset));
    write(&file_header_template_.data_offset, sizeof(file_header_template_.data_offset));
    write(file_header_template_.header_padding, sizeof(file_header_template_.header_padding[0]) * 6);

    // write empty index
    write(&empty_index_header_.index_size, sizeof(empty_index_header_.index_size));
    write(&empty_index_header_.index_count, sizeof(empty_index_header_.index_count));

    // write EOF
    write(default_eof_, sizeof(default_eof_[0]) * 2);
}





