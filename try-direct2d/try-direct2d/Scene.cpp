#include "stdafx.h"
#include "Scene.h"
#include "SceneState.h"
//#include "CanvasState.h"
#include "GameState.h"
#include "Render.h"

Scene::Scene()
{
    //m_state = new CanvasState();
    m_state = new GameState();
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
    Render::Clear();
    m_state->renderGameObjects();

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
