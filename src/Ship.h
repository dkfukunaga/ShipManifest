


#ifndef SHIP_H
#define SHIP_H

#include "ShipTypes.h"
#include "ShipRegistry.h"
#include "ShipClass.h"
#include "Component.h"
#include "Weapon.h"
#include <string>

using namespace std;



struct Ship {
private:
    string          name;
    ShipRegistry    registry;
    string          commander;
    string          engineer;
    ShipClass*      ship_class;
    ShipComponents  components;
    ShipDefenses    defenses;
    ShipWeapons     weapons;
public:
    string          getName() const;
    string          getRegistry() const;
    string          getCommander() const;
    string          getEngineer() const;
    ShipClass*      getShipClass() const;
    void            setName(string nm);
    void            setRegistry(ShipRegistry reg);
    void            setCommander(string cmdr);
    void            setEngineer(string engi);
    void            setShipClass(ShipClass *cls);
};


#endif

