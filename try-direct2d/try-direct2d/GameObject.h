#pragma once
#include "Screen.h"

class GameObject
{
public:
    GameObject();
    ~GameObject();
    int m_x;
    int m_y;
    virtual void render(Screen* screen) = 0;
};

