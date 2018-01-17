#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "Input.h"
#include "Render.h"

GameState::GameState()
{
    m_player = new Player(0, 0, 50, 20);
}


GameState::~GameState()
{
    delete m_player;
}

void GameState::enter()
{
}

SceneState* GameState::update()
{
    Render::Clear();

    // Player
    m_player->render();

    // Menu
    Render::DrawText(0, 0, 400, 40, L"Click to start game");

    bool isMenuKeyDowned = Input::GetKey(VK_ESCAPE);

    if (isMenuKeyDowned) {
        return new MenuState();
    }

    return NULL;
}

void GameState::onMouseMove()
{
}