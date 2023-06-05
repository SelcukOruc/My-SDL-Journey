#ifndef CONFING_H
#define CONFING_H
#include <vector>

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 400

class CONFIG
{
public:
    static void ResizeHasCollidedArray();
    static std::vector<bool> HasCollidedArray;
    static int ObjectNumberCreated;
};

#endif