#pragma once
#ifndef LASER_H
#define LASER_H

#include "Weapon.h"

class Laser : public Weapon {
public:
    Laser(uint32_t uid, WeaponSize size, uint32_t damage, uint32_t range, uint32_t energy):
        Weapon(uid, WeaponType::laser, size, damage, range),
        energy_(energy) { };
    ~Laser() = default;

    uint32_t                getEnergy() const;
    uint32_t                getSize() const;

    void                    serialize(DataFile &file) const override;
    bool                    deserialize(DataFile &file) override;

    void                    setEnergy(uint32_t energy);
private:
    uint32_t                energy_;
};


#endif