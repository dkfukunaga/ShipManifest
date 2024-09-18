

#include "DataFile.h"


DataFile::DataFile():
    file_name_(""),
    data_file_(new std::fstream()),
    is_initialized_(false) { };

DataFile::DataFile(std::string file_name) {
    setFileName(file_name);
    open(file_name_);
}


DataFile::~DataFile() {
    if (data_file_->is_open())
        data_file_->close();
    delete data_file_;
}


std::string DataFile::getFileName() const { return file_name_; }

void DataFile::setFileName(std::string file_name) {
    int len = file_name.length();
    if (len > 4 && file_name.substr(len - 4) == ".dat")
        file_name_ = file_name; 
    else if (len > 4)
        file_name_ = file_name + ".dat";
    else
        file_name_ = "";
}

bool DataFile::isOpen() const { return data_file_->is_open(); }

bool DataFile::isInitialized() const { return is_initialized_; }

bool DataFile::open(std::string file_name) {
    setFileName(file_name);
    data_file_ = new std::fstream{file_name_, std::ios::binary | std::ios::in | std::ios::out};

    // if file not opened (doesn't exist), use ofstream to create one with same name
    // then close ofstream, open file as fstream, and initFile to initialize the counter to 0
    if (!*data_file_) {
        delete data_file_;
        std::ofstream* temp_stream = new std::ofstream(file_name_);
        temp_stream->close();
        // delete temp_stream;
        data_file_ = new std::fstream{file_name_, std::ios::binary | std::ios::in | std::ios::out};
        is_initialized_ = false;
    }

    is_initialized_ = true;
}

void DataFile::close() {
    if (data_file_->is_open()) {
        data_file_->close();
    }
}


void DataFile::read(void *data, int size, long long pos) {
    moveReadPointer(pos);
    data_file_->read(reinterpret_cast<char*>(data), size);
}

void DataFile::read(void *data, int size) {
    data_file_->read(reinterpret_cast<char*>(data), size);
}

void DataFile::read(std::string &str, long long pos) {
    moveReadPointer(pos);

    uint8_t len;
    read(&len, sizeof(len));

    char cstr[len + 1];
    read(cstr, len);
    cstr[len] = '\0';

    str = std::string(str);
}

void DataFile::read(std::string &str) {
    uint8_t len;
    read(&len, sizeof(len));

    char cstr[len + 1];
    read(cstr, len);
    cstr[len] = '\0';
    
    str = std::string(str);
}

void DataFile::write(void *data, int size, long long pos) {
    moveWritePointer(pos);
    data_file_->write(reinterpret_cast<char*>(data), size);
}

void DataFile::write(void *data, int size) {
    data_file_->write(reinterpret_cast<char*>(data), size);
}

void DataFile::write(std::string &str, long long pos) {
    moveWritePointer(pos);

    uint8_t len = str.length();
    char cstr[len];
    memcpy(cstr, str.c_str(), len);

    write(&len, sizeof(len));
    write(cstr, len);
}

void DataFile::write(std::string &str) {
    uint8_t len = str.length();
    char cstr[len];
    memcpy(cstr, str.c_str(), len);

    write(&len, sizeof(len));
    write(cstr, len);
}


void DataFile::moveReadPointer(long long pos) {
    data_file_->seekg(pos, (pos < 0 ? std::ios::end : std::ios::beg));
}

void DataFile::moveWritePointer(long long pos) {
    data_file_->seekp(pos, (pos < 0 ? std::ios::end : std::ios::beg));
}



