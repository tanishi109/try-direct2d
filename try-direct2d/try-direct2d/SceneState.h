#pragma once

class CanvasState;

class SceneState
{
public:
    SceneState();
    ~SceneState();
    virtual void update() {}

    static CanvasState canvas;
};

