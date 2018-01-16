#pragma once

#include "SceneState.h"
#include "World.h"

class CanvasState : public SceneState
{
public:
    CanvasState();
    ~CanvasState();
    virtual void enter();
    virtual SceneState* update();
    virtual void onMouseMove();
    static World* m_world;
private:
    static int m_screenPos[2];
    HCURSOR m_grabCursor;
    HCURSOR m_defaultCursor;
};

