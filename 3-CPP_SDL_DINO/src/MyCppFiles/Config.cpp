#include "MyHeaderFiles/Config.h"

int CONFIG::ObjectNumberCreated = 0;
std::vector<bool> CONFIG::HasCollidedArray;

void CONFIG::ResizeHasCollidedArray()
{
    CONFIG::HasCollidedArray.resize(CONFIG::ObjectNumberCreated);
}