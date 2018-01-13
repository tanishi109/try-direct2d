#pragma once
#include "SceneState.h"

class Scene
{
public:
    Scene();
    ~Scene();
    virtual void onRender();
    SceneState* m_state;
};

