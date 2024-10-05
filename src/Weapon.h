
#ifndef SHIP_WEAPON_H
#define SHIP_WEAPON_H

#include "DataFile.h"
#include "Headers.h"
#include "Serializable.h"
#include "Subsystem.h"
#include <string>
#include <cstdint>

enum class WeaponSize : uint8_t {
    light = 0,
    medium,
    heavy,
};

enum class DamageType :uint8_t {
    kinetic,
    energy,
    explosive,
};

struct Weapon : Subsystem {
    WeaponSize     size_class      = WeaponSize::light;
    DamageType          damage_type     = DamageType::kinetic;
    int32_t             damage          = 0;
    int32_t             range           = 0;

    Weapon() { };
    Weapon(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
            WeaponSize new_size, DamageType new_dmg_type, int32_t new_damage, int32_t new_range):
        Subsystem(new_name, new_tier, new_mass, new_dur, new_power),
        size_class(new_size),
        damage_type(new_dmg_type),
        damage(new_damage),
        range(new_range) { };
    
    recsize_t           getSize() const;
protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct Kinetic : Weapon {
    uint32_t            velocity        = 0;
    uint32_t            ammo_capacity   = 0;

    Kinetic() { };
    Kinetic(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
            WeaponSize new_size, DamageType new_dmg_type, int32_t new_damage, int32_t new_range,
            uint32_t new_vel, uint32_t new_ammo_cap):
        Weapon(new_name, new_tier, new_mass, new_dur, new_power, new_size, new_dmg_type, new_damage, new_range),
        velocity(new_vel),
        ammo_capacity(new_ammo_cap) { };
    
    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct Beam : Weapon {
    uint8_t             shield_penetration  = 0;
    uint8_t             range_penalty       = 0;
    uint16_t            capacitor_charge    = 0;

    Beam() { };
    Beam(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
            WeaponSize new_size, DamageType new_dmg_type, int32_t new_damage, int32_t new_range,
            uint8_t new_shield_penetration, uint8_t new_range_pen, uint16_t new_cap_charge):
        Weapon(new_name, new_tier, new_mass, new_dur, new_power, new_size, new_dmg_type, new_damage, new_range),
        shield_penetration(new_shield_penetration),
        range_penalty(new_range_pen),
        capacitor_charge(new_cap_charge) { };
    
    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct Missile : Weapon {
    uint32_t            velocity        = 0;
    uint16_t            evasion         = 0;
    uint16_t            tracking        = 0;

    Missile() { };
    Missile(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
            WeaponSize new_size, DamageType new_dmg_type, int32_t new_damage, int32_t new_range,
            uint32_t new_vel, uint16_t new_evation, uint16_t new_tracking):
        Weapon(new_name, new_tier, new_mass, new_dur, new_power, new_size, new_dmg_type, new_damage, new_range),
        velocity(new_vel),
        evasion(new_evation),
        tracking(new_tracking) { };
    
    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

#endif