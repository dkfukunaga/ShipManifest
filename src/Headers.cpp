
#include "Headers.h"




offset_t        FileHeader::serialize(DataFile &file) {
    if (!file.isOpen()) {
        return 0;
    }

    offset_t record_offset = file.getWritePos();

    file.write(&sig);
    file.write(&flags);
    file.write(&version);
    file.write(&type);
    file.write(&size);
    file.write(&index_offset);
    
    return record_offset;
}

offset_t        FileHeader::serialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return 0;
    }

    file.setWritePos(pos);
    return serialize(file);
}


void            FileHeader::deserialize(DataFile &file) {
    if (!file.isOpen()) {
        return;
    }

    file.read(&sig);
    file.read(&flags);
    file.read(&version);
    file.read(&type);
    file.read(&size);
    file.read(&index_offset);
}

void            FileHeader::deserialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return;
    }

    file.setReadPos(pos);

    deserialize(file);
}


/***** SectionHeader *****/

offset_t        SectionHeader::serialize(DataFile &file) {
    if (!file.isOpen()) {
        return 0;
    }

    offset_t record_offset = file.getWritePos();

    file.write(&size);
    file.write(&type);
    
    return record_offset;
}

offset_t        SectionHeader::serialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return 0;
    }

    file.setWritePos(pos);
    return serialize(file);
}


void            SectionHeader::deserialize(DataFile &file) {
    if (!file.isOpen()) {
        return;
    }

    file.read(&size);
    file.read(&type);
}

void            SectionHeader::deserialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return;
    }

    file.setReadPos(pos);

    deserialize(file);
}


/***** TableHeader *****/

offset_t        TableHeader::serialize(DataFile &file) {
    if (!file.isOpen()) {
        return 0;
    }

    offset_t record_offset = file.getWritePos();

    file.write(&size);
    file.write(&type);
    file.write(&count);
    
    return record_offset;
}

offset_t        TableHeader::serialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return 0;
    }

    file.setWritePos(pos);
    return serialize(file);
}


void            TableHeader::deserialize(DataFile &file) {
    if (!file.isOpen()) {
        return;
    }

    file.read(&size);
    file.read(&type);
    file.read(&count);
}

void            TableHeader::deserialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return;
    }

    file.setReadPos(pos);

    deserialize(file);
}


/***** DataRecordHeader *****/

offset_t        DataRecordHeader::serialize(DataFile &file) {
    if (!file.isOpen()) {
        return 0;
    }

    offset_t record_offset = file.getWritePos();

    file.write(&index);
    file.write(&size);
    file.write(&redirect);
    
    return record_offset;
}

offset_t        DataRecordHeader::serialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return 0;
    }

    file.setWritePos(pos);
    return serialize(file);
}


void            DataRecordHeader::deserialize(DataFile &file) {
    if (!file.isOpen()) {
        return;
    }

    file.read(&index);
    file.read(&size);
    file.read(&redirect);
}

void            DataRecordHeader::deserialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return;
    }

    file.setReadPos(pos);

    deserialize(file);
}


/***** IndexRecord *****/

offset_t        IndexRecord::serialize(DataFile &file) {
    if (!file.isOpen()) {
        return 0;
    }

    offset_t record_offset = file.getWritePos();

    file.write(&index);
    file.write(&offset);
    
    return record_offset;
}

offset_t        IndexRecord::serialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return 0;
    }

    file.setWritePos(pos);
    return serialize(file);
}


void            IndexRecord::deserialize(DataFile &file) {
    if (!file.isOpen()) {
        return;
    }

    file.read(&index);
    file.read(&offset);
}

void            IndexRecord::deserialize(DataFile &file, int64_t pos) {
    if (!file.isOpen()) {
        return;
    }

    file.setReadPos(pos);

    deserialize(file);
}
