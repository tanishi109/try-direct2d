#pragma once

#include "Screen.h"
#include "GameObject.h"

class SceneState
{
public:
    SceneState();
    ~SceneState();
    virtual void render();
    virtual void enter() {}
    virtual SceneState* update() {return NULL;}
    virtual void onMouseMove() {}
protected:
    Screen* m_screen;
    std::vector<GameObject*> m_gameObjects;
};

