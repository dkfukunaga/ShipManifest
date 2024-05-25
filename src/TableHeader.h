


#ifndef TABLE_HEADER_H
#define TABLE_HEADER_H


// Three character codes to indicate the type of table.
// Tables are in all caps; sub-tables are in all lower case.
namespace TableType {
    const char ship[3]              = { 'S', 'H', 'P' };    // Ship table: "SHP"
    const char ship_string[3]       = { 'S', 'S', 'T' };    // ShipString table: "SST"
    const char game_character[3]    = { 'G', 'C', 'H' };    // GameCharacter table: "GCH"
    const char ship_class[3]        = { 'S', 'C', 'L' };    // ShipClass table: "SCL"
    const char ship_weapons[3]      = { 'S', 'W', 'P' };    // ShipWeapons table: "SWP"
    const char component[3]         = { 'C', 'M', 'P' };    // Components table: "CMP"
    const char reactor[3]           = { 'r', 'c', 't' };    //     Reactor Component sub-table: "rct"
    const char sublight[3]          = { 's', 'b', 'l' };    //     Sublight Component sub-table: "sbl"
    const char ftl[3]               = { 'f', 't', 'l' };    //     FTL Component sub-table:  "ftl"
    const char shield[3]            = { 's', 'h', 'd' };    //     Shield Component sub-table:  "shd"
    const char weapon[3]            = { 'W', 'E', 'P' };    // Weapon table: "WEP"
    const char beam[3]              = { 'b', 'e', 'm' };    //     Beam Weapon sub-table:  "bem"
    const char kinetic[3]           = { 'k', 'i', 'n' };    //     Kinetic Weapon sub-table:  "kin"
    const char missile[3]           = { 'm', 'i', 's' };    //     Missile Weapon sub-table:  "mis"
    const char string[3]            = { 'S', 'T', 'R' };    // String table: "STR"
};


struct TableHeader {
    char                tbl_type[3];
    unsigned char       rec_size;
    short               rec_count;
    short               tbl_size;
};




#endif