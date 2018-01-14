#pragma once

class CanvasState;

class SceneState
{
public:
    SceneState();
    ~SceneState();
    virtual void enter() {}
    virtual void update() {}

    static CanvasState canvas;
};

