


#ifndef TABLE_HEADER_H
#define TABLE_HEADER_H

#include <string>

// Three character codes to indicate the type of table.
// Tables are in all caps; sub-tables are in all lower case.
namespace TableType {
    const char ship[3];
    const char ship_string[3];
    const char game_character[3];
    const char ship_class[3];
    const char ship_weapons[3];
    const char component[3];
    const char reactor[3];
    const char sublight[3];
    const char ftl[3];
    const char shield[3];
    const char weapon[3];
    const char beam[3];
    const char kinetic[3];
    const char missile[3];
    const char string[3];
};


struct TableHeader {
    char                tbl_type[3];
    unsigned char       rec_size;
    short               rec_count;
    short               tbl_size;
};




#endif