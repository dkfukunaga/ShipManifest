

#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include <string>
#include <cstdint>

class Subsystem {
private:
    std::string         name_;
    uint8_t             tier_;
    uint16_t            mass_;
    uint16_t            durability_;
    int32_t             power_;

public:
    Subsystem(std::string name, uint8_t tier, uint16_t mass, 
              uint16_t durability, int32_t new_power):
        name_(name),
        tier_(tier),
        mass_(mass),
        durability_(durability),
        power_(new_power) { };
    
    std::string         getName() const;
    uint8_t             getTier() const;
    uint16_t            getMass() const;
    uint16_t            getDurability() const;
    int32_t             getPower() const;

    void                setName(std::string name);
    void                setTier(uint8_t tier);
    void                setMass(uint16_t mass);
    void                setDurability(uint16_t durability);
    void                setPower(int32_t power);
};

class Reactor : Subsystem {
private:
    uint16_t            fuel_use_;

public:
    Reactor(std::string name, uint8_t tier, uint16_t mass, 
            uint16_t durability, uint32_t new_power, uint16_t new_fuel_use):
        Subsystem(name, tier, mass, durability, new_power),
        fuel_use_(new_fuel_use) { };
    

};

class Thrusters : Subsystem {
    uint16_t            speed_;
    uint16_t            maneuver_;
};

class FTLdrive : Subsystem {
    uint8_t             ftl_rating_;
};

class Computer : Subsystem {
    uint16_t            processing_power_;
    uint16_t            memory_;
};

class Armor : Subsystem {
    uint8_t             armor_rating_;
    uint8_t             hardness_;
};

class Shields : Subsystem {
    uint8_t             damage_reduction_;
    uint16_t            max_strength_;
    uint16_t            recharge_rate_;
};



#endif