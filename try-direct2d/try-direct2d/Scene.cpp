#include "stdafx.h"
#include "Scene.h"

#include "SceneState.h"
#include "CanvasState.h"


Scene::Scene()
{
    m_state = &SceneState::canvas;
}


Scene::~Scene()
{
}

void Scene::onRender()
{
    m_state->onRender();
};