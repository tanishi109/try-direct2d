#include "stdafx.h"
#include "Scene.h"

#include "SceneState.h"
#include "CanvasState.h"

Scene::Scene()
{
    m_state = new CanvasState();
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
    SceneState* new_scene = m_state->update();

    if (new_scene != NULL) {
        delete m_state;
        m_state = new_scene;
        m_state->enter();
    }
};

void Scene::onMouseMove()
{
    m_state->onMouseMove();
};
