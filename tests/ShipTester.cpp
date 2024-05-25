


#include "Ship.h"
#include <iostream>



int main() {

    Ship *ship = new Ship;

    ShipRegistry reg;

    std::cout << reg.getVIC() << endl;

    delete ship;

    return 0;
}



