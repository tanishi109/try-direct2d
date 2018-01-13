#pragma once

class CanvasState;

class SceneState
{
public:
    SceneState();
    ~SceneState();
    virtual void onRender() {}

    static CanvasState canvas;
};

