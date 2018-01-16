#pragma once

class SceneState
{
public:
    SceneState();
    ~SceneState();
    virtual void enter() {}
    virtual SceneState* update() {return NULL;}
    virtual void onMouseMove() {}
};

