#ifndef SHIP_MANIFEST_COMMON_H
#define SHIP_MANIFEST_COMMON_H

#include <cstdint>

using index_t = uint32_t;

enum class ShipType : uint32_t {
    corvette = 1,
    frigate,
    destroyer,
    light_cruiser,
    heavy_cruiser,
    battleship,
};

enum class OffRank : uint32_t {
    na = 0,
    ensign,
    sub_lieutenant,
    lieutenant,
    sub_commander,
    commander,
    captain,
};

enum class ShipDept : uint32_t {
    command = 1,
    operations,
    engineering,
    navigation,
    weapons,
    medical,
};

#endif