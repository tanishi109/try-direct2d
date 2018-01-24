#pragma once

#include "Screen.h"

class SceneState
{
public:
    SceneState();
    ~SceneState();
    virtual void enter() {}
    virtual SceneState* update() {return NULL;}
    virtual void onMouseMove() {}
protected:
    Screen* m_screen;
};

