#pragma once
#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include <cstdint>
#include "DataFile/src/DataFile.h"


enum class WeaponType {
    laser,
    kinetic,
    missile,
};

enum class WeaponSize {
    light,
    medium,
    heavy,
};



class Weapon {
public:
    Weapon(uint32_t uid, WeaponType type, WeaponSize size, uint32_t damage, uint32_t range):
        uid_(uid),
        type_(type),
        size_(size),
        damage_(damage),
        range_(range) { };

    uint32_t                getUID() const;
    uint32_t                getDamage() const;
    uint32_t                getRange() const;

    void                    setDamage(uint32_t damage);
    void                    setRange(uint32_t range);

    virtual                 ~Weapon() = default;
    virtual uint32_t        getSize() const = 0;

    virtual void            serialize(DataFile &file) const = 0;
    virtual bool            deserialize(DataFile &file) = 0;
private:
    uint32_t                uid_;
    WeaponType              type_;
    WeaponSize              size_;

    uint32_t                damage_;
    uint32_t                range_;
};




#endif


// #include "..\DataFile\src\DataFile.h"
// #include "Headers.h"
// #include "Serializable.h"
// #include "Subsystem.h"
// #include <string>
// #include <cstdint>

// enum class WeaponType {
//     none,
//     mass_driver,
//     beam,
//     missile,
// };

// enum class WeaponSize : uint8_t {
//     light = 0,
//     medium,
//     heavy,
// };

// enum class DamageType : uint8_t {
//     kinetic,
//     energy,
//     explosive,
// };

// struct Weapon : Subsystem {
//     WeaponType          type            = WeaponType::none;
//     WeaponSize          size_class      = WeaponSize::light;
//     DamageType          damage_type     = DamageType::kinetic;
//     int32_t             damage          = 0;
//     int32_t             range           = 0;

//     Weapon() { };
//     Weapon(WeaponType new_type, std::string new_name, uint8_t new_tier, uint16_t new_mass,
//            uint16_t new_dur, int32_t new_power, WeaponSize new_size, DamageType new_dmg_type,
//            int32_t new_damage, int32_t new_range):
//         Subsystem(SubsystemType::weapon, new_name, new_tier, new_mass, new_dur, new_power),
//         type(new_type),
//         size_class(new_size),
//         damage_type(new_dmg_type),
//         damage(new_damage),
//         range(new_range) { };
    
//     recsize_t           getSize() const;
// protected:
//     void                serializeData(DataFile &file) const;
//     void                deserializeData(DataFile &file);
// };

// struct MassDriver : Weapon {
//     uint32_t            velocity        = 0;
//     uint32_t            ammo_capacity   = 0;

//     MassDriver() { };
//     MassDriver(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
//                WeaponSize new_size, DamageType new_dmg_type, int32_t new_damage, int32_t new_range,
//                uint32_t new_vel, uint32_t new_ammo_cap):
//         Weapon(WeaponType::mass_driver, new_name, new_tier, new_mass, new_dur, new_power, new_size,
//                new_dmg_type, new_damage, new_range),
//         velocity(new_vel),
//         ammo_capacity(new_ammo_cap) { };
    
//     recsize_t           getSize() const;

// protected:
//     void                serializeData(DataFile &file) const;
//     void                deserializeData(DataFile &file);
// };

// struct Beam : Weapon {
//     uint8_t             shield_penetration  = 0;
//     uint8_t             range_penalty       = 0;
//     uint16_t            capacitor_charge    = 0;

//     Beam() { };
//     Beam(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
//             WeaponSize new_size, DamageType new_dmg_type, int32_t new_damage, int32_t new_range,
//             uint8_t new_shield_penetration, uint8_t new_range_pen, uint16_t new_cap_charge):
//         Weapon(WeaponType::beam, new_name, new_tier, new_mass, new_dur, new_power, new_size,
//                new_dmg_type, new_damage, new_range),
//         shield_penetration(new_shield_penetration),
//         range_penalty(new_range_pen),
//         capacitor_charge(new_cap_charge) { };
    
//     recsize_t           getSize() const;

// protected:
//     void                serializeData(DataFile &file) const;
//     void                deserializeData(DataFile &file);
// };

// struct Missile : Weapon {
//     uint32_t            velocity        = 0;
//     uint16_t            evasion         = 0;
//     uint16_t            tracking        = 0;

//     Missile() { };
//     Missile(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
//             WeaponSize new_size, DamageType new_dmg_type, int32_t new_damage, int32_t new_range,
//             uint32_t new_vel, uint16_t new_evation, uint16_t new_tracking):
//         Weapon(WeaponType::missile, new_name, new_tier, new_mass, new_dur, new_power, new_size,
//                new_dmg_type, new_damage, new_range),
//         velocity(new_vel),
//         evasion(new_evation),
//         tracking(new_tracking) { };
    
//     recsize_t           getSize() const;

// protected:
//     void                serializeData(DataFile &file) const;
//     void                deserializeData(DataFile &file);
// };