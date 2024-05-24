


#include "Ship.h"

// getters
string      Ship::getName() const               { return name; }
string      Ship::getRegistry() const           { return registry.getVIC(); }
string      Ship::getCommander() const          { return commander; }
string      Ship::getEngineer() const           { return engineer; }
ShipClass*  Ship::getShipClass() const          { return ship_class; }
// setters
void        Ship::setName(string nm)            { name = nm; }
void        Ship::setRegistry(ShipRegistry reg) { registry = reg; }
void        Ship::setCommander(string cmdr)     { commander = cmdr; }
void        Ship::setEngineer(string engi)      { engineer = engi; }
void        Ship::setShipClass(ShipClass *cls)  { ship_class = cls; }


