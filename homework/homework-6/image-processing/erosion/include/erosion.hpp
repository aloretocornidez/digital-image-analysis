#ifndef __EROSION_H__
#define __EROSION_H__

#include <iostream>

class erosion
{
private:
public:
    erosion();
    ~erosion();

    void printHello();
};

erosion::erosion()
{
    std::cout << "Erosion Object Constructed" << std::endl;
}

erosion::~erosion()
{
    std::cout << "Erosion Object Destroyed" << std::endl;
}

#endif