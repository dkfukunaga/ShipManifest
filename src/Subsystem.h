

#ifndef SHIP_SUBSYSTEM_H
#define SHIP_SUBSYSTEM_H

#include "..\DataFile\src\DataFile.h"
#include "Headers.h"
#include "Serializable.h"
#include <string>
#include <cstdint>

enum class SubsystemType {
    none,
    reactor,
    thrusters,
    ftldrive,
    computer,
    armor,
    shields,
    weapon,
};

struct Subsystem : public Serializable {
    SubsystemType       type            = SubsystemType::none;
    std::string         name            = "NONAME";
    uint8_t             tier            = 0;
    uint16_t            mass            = 0;
    uint16_t            durability      = 0;
    int32_t             power           = 0;

    Subsystem() { };
    Subsystem(SubsystemType new_type, std::string new_name, uint8_t new_tier,
              uint16_t new_mass, uint16_t new_dur, int32_t new_power):
        type(new_type),
        name(new_name),
        tier(new_tier),
        mass(new_mass),
        durability(new_dur),
        power(new_power) { };
    Subsystem(const Subsystem &) = default;             // default copy constructor
    Subsystem(Subsystem &&) noexcept = default;         // default move construtor
    virtual ~Subsystem() = default;                     // default virtual destructor

    recsize_t           getSize() const;
protected:
    void                writeHeader(DataFile &file, index_t index, recsize_t size, offset_t offset) const;
    index_t             readHeader(DataFile &file);
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct Reactor : Subsystem {
    uint16_t            fuel_use        = 0;

    Reactor() {
        type = SubsystemType::reactor;
    };
    Reactor(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
            uint16_t new_fuel_use):
        Subsystem(SubsystemType::reactor, new_name, new_tier, new_mass, new_dur, new_power),
        fuel_use(new_fuel_use) { };

    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct Thrusters : Subsystem {

    uint16_t            speed           = 0;
    uint16_t            maneuver        = 0;

    Thrusters() {
        type = SubsystemType::thrusters;
    }
    Thrusters(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
              uint16_t new_speed, uint16_t new_maneuver):
        Subsystem(SubsystemType::thrusters, new_name, new_tier, new_mass, new_dur, new_power),
        speed(new_speed),
        maneuver(new_maneuver) { };
    
    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct FTLdrive : Subsystem {

    uint8_t             ftl_rating      = 0;

    FTLdrive() {
        type = SubsystemType::ftldrive;
    };
    FTLdrive(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
             uint8_t new_ftl_rating):
        Subsystem(SubsystemType::ftldrive, new_name, new_tier, new_mass, new_dur, new_power),
        ftl_rating(new_ftl_rating) { };
    
    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct Computer : Subsystem {

    uint16_t            processing_power    = 0;
    uint16_t            memory              = 0;

    Computer() {
        type = SubsystemType::computer;
    };
    Computer(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
             uint16_t new_processing_power, uint16_t new_memory):
        Subsystem(SubsystemType::computer, new_name, new_tier, new_mass, new_dur, new_power),
        processing_power(new_processing_power),
        memory(new_memory) { };

    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct Armor : Subsystem {

    uint8_t             armor_rating    = 0;
    uint8_t             hardness        = 0;

    Armor() {
        type = SubsystemType::armor;
    };
    Armor(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
          uint8_t new_armor_rating, uint8_t new_hardness):
        Subsystem(SubsystemType::armor, new_name, new_tier, new_mass, new_dur, new_power),
        armor_rating(new_armor_rating),
        hardness(new_hardness) { };

    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};

struct Shields : Subsystem {

    uint8_t             damage_reduction    = 0;
    uint16_t            max_strength        = 0;
    uint16_t            recharge_rate       = 0;

    Shields() {
        type = SubsystemType::shields;
    };
    Shields(std::string new_name, uint8_t new_tier, uint16_t new_mass, uint16_t new_dur, int32_t new_power,
            uint8_t new_damage_reduction, uint16_t new_max_strength, uint16_t new_recharge_rate):
        Subsystem(SubsystemType::shields, new_name, new_tier, new_mass, new_dur, new_power),
        damage_reduction(new_damage_reduction),
        max_strength(new_max_strength),
        recharge_rate(new_recharge_rate) { };

    recsize_t           getSize() const;

protected:
    void                serializeData(DataFile &file) const;
    void                deserializeData(DataFile &file);
};



#endif