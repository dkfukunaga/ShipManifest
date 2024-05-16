



#ifndef COMPONENT_H
#define COMPONENT_H


#include <string>

using namespace std;

class Component {
public:
    string              name;
    char                tier;
    int                 mass;
    int                 power;
    virtual void        use() = 0;
};



#endif