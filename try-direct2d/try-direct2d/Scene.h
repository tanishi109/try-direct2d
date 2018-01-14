#pragma once
#include "SceneState.h"

class Scene
{
public:
    Scene();
    ~Scene();
    virtual void enter();
    virtual void update();
    SceneState* m_state;
};

