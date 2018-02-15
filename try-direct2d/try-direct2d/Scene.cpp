#include "stdafx.h"
#include "Scene.h"
#include "SceneState.h"
#include "StageSelectState.h"
#include "Render.h"

Scene::Scene() :
m_currentState(new StageSelectState())
{
    push(m_currentState);
}


Scene::~Scene()
{
}

void Scene::enter()
{
    m_currentState->enter(*this);
}

void Scene::update()
{
    m_currentState->renderGameObjects();

    m_currentState->update(this);
}

void Scene::onMouseMove()
{
    m_currentState->onMouseMove();
}

void Scene::push(SceneState* state)
{
    m_stateStack.push_back(state);
    m_currentState = m_stateStack.back();
    enter();
}

void Scene::pop()
{
    m_stateStack.pop_back();
    m_currentState = m_stateStack.back();
    enter();
}
