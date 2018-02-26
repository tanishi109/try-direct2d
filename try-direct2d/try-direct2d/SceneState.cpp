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
    std::for_each(m_gameObjects.begin(), m_gameObjects.end(), [this](GameObject* gameObj) {
        gameObj->render(m_screen);
    });
}

void SceneState::onMouseMove()
{
}
