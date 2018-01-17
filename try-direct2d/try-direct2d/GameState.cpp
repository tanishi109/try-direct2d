#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "Input.h"
#include "Render.h"

GameState::GameState()
{
}


GameState::~GameState()
{
}

void GameState::enter()
{
}

SceneState* GameState::update()
{
    Render::Clear();

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