#pragma once

#include "Screen.h"
#include "GameObject.h"
#include "Scene.h"

class SceneState
{
public:
    SceneState();
    ~SceneState();
    SceneState(const SceneState&) = delete;
    SceneState& operator=(const SceneState&) = delete;
    void renderGameObjects();
    virtual void enter();
    virtual void update(Scene* scene) = 0;
    virtual void onMouseMove();
protected:
    Screen* m_screen;
    std::vector<GameObject*> m_gameObjects;
};

