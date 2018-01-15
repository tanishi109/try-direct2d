#pragma once
#include "SceneState.h"

class Scene
{
public:
    Scene();
    ~Scene();
    virtual void enter();
    virtual void update();
    virtual void onMouseMove();
    SceneState* m_state;
};

