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

void Scene::enter()
{
    m_state->enter();
};

void Scene::update()
{
    m_state->update();
};

void Scene::onMouseMove()
{
    m_state->onMouseMove();
};
