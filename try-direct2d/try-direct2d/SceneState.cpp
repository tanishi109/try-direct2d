#include "stdafx.h"
#include "SceneState.h"

#include "CanvasState.h"
#include "MenuState.h"

SceneState::SceneState() :
m_screen(new Screen())
{
}


SceneState::~SceneState()
{
}

void SceneState::render()
{
    for (auto gameObj = m_gameObjects.begin(); gameObj != m_gameObjects.end(); gameObj++) {
        (*gameObj)->render(m_screen);
    }
}
