#pragma once

class CanvasState;

class SceneState
{
public:
    SceneState();
    ~SceneState();
    virtual void enter() {}
    virtual void update() {}
    virtual void onMouseMove() {}

    static CanvasState canvas;
};

