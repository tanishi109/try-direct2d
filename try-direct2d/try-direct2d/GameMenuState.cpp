#include "stdafx.h"
#include "GameMenuState.h"
#include "Render.h"
#include "Input.h"

std::function<void(int)> GameMenuState::m_onSelect = [](int index){
};


ScrollableList& GameMenuState::m_list = *new ScrollableList(m_onSelect, {
    "Back"
});

GameMenuState::GameMenuState()
{
    m_list.m_marginPx.assign(8, 80);
    m_gameObjects.push_back(&m_list);
}


GameMenuState::~GameMenuState()
{
}

void GameMenuState::enter(Scene& scene)
{
    Render::TakeScreenShot();

    m_onSelect = [&scene, this](int index){
        if (index == 0) {
            scene.pop();
            scene.pop();
            return;
        }
    };
}

void GameMenuState::update(Scene* scene)
{
    Render::DrawScreenShot(0);

    if (Input::GetKeyDown(VK_ESCAPE)) {
        scene->pop();
    }
}
