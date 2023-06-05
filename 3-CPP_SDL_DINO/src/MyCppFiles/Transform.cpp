#include "MyHeaderFiles/CONFIG.h"
#include "MyHeaderFiles/Transform.h"
#include <iostream>
#include "MyHeaderFiles/Config.h"

Transform::Transform()
{
    Id = CONFIG::ObjectNumberCreated++;
}
Transform::~Transform()
{
    delete position;
    delete scale;
    CONFIG::ObjectNumberCreated--;
}
