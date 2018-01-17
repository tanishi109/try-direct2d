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

    // set player rotation
    int mouseX = Input::GetMousePosX();
    int mouseY = Input::GetMousePosY();
    int mainPinX;
    int mainPinY;
    std::tie(mainPinX, mainPinY) = m_player->getMainPinPos();
    int dx = mouseX - mainPinX;
    int dy = mouseY - mainPinY;
    double radian = std::atan2(dy, dx);
    m_player->m_degree = radian * 180 / M_PI;

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