#include "Weapon.h"


uint32_t Weapon::getUID() const { return uid_; }

uint32_t Weapon::getDamage() const { return damage_; }

uint32_t Weapon::getRange() const { return range_; }

void Weapon::setDamage(uint32_t damage) { damage_ = damage; }

void Weapon::setRange(uint32_t range) { range_ = range; }

