#pragma once

#include "Screen.h"
#include "GameObject.h"

class SceneState
{
public:
    SceneState();
    ~SceneState();
    void renderGameObjects();
    virtual void enter() {}
    virtual SceneState* update() = 0;
    virtual void onMouseMove() {}
protected:
    Screen* m_screen;
    std::vector<GameObject*> m_gameObjects;
};

