


#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include "Component.h"

class Reactor : Component {
public:
    void            use() override;
};

class SubDrive : Component {
public:
    void            use() override;
};

class FTLDrive : Component {
public:
    void            use() override;
};

class ShieldGen : Component {
public:
    void            use() override;
};



#endif