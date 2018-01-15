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
    static int m_screenPos[2];
private:
    HCURSOR m_grabCursor;
    HCURSOR m_defaultCursor;
};

