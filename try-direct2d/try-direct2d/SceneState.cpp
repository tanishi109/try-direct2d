#include "stdafx.h"
#include "SceneState.h"

#include "CanvasState.h"
#include "CanvasMenuState.h"

SceneState::SceneState() :
m_screen(new Screen())
{
}


SceneState::~SceneState()
{
    delete m_screen;
}

void SceneState::enter(Scene& scene)
{
}

void SceneState::renderGameObjects()
{
    for (auto gameObj = m_gameObjects.begin(); gameObj != m_gameObjects.end(); gameObj++) {
        (*gameObj)->render(m_screen);
    }
}

void SceneState::onMouseMove()
{
}
