#pragma once

#include "SceneState.h"

class MenuState : public SceneState
{
public:
    MenuState();
    ~MenuState();
    virtual void enter();
    virtual SceneState* update();
};

