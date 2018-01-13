#pragma once

#include "SceneState.h"

class CanvasState : public SceneState
{
public:
    CanvasState();
    ~CanvasState();
    virtual void onRender();
};

