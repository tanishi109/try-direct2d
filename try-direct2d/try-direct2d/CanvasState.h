#pragma once

#include "SceneState.h"
#include "World.h"

class CanvasState : public SceneState
{
public:
    CanvasState();
    ~CanvasState();
    virtual void enter();
    virtual void update();
    static World* m_world;
};

