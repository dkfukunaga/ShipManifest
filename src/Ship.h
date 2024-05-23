


#ifndef SHIP_H
#define SHIP_H

#include "ShipClass.h"
#include "ShipRegistry.h"
#include <string>

using namespace std;



class Ship {
public:
    string          getName() const;
    string          getRegistry() const;
    string          getCommander() const;
    string          getEngineer() const;
    ShipClass*      getShipClass() const;
    bool            setName(string name);
private:
    string          name;
    ShipRegistry    registry;
    string          commander;
    string          engineer;
    ShipClass*      ship_class;
};


#endif

