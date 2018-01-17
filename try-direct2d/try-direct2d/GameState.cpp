#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "Input.h"
#include "Render.h"
#include "Mathtool.h"

GameState::GameState() :
m_player(new Player(0, 0, 50, 20)),
m_isFocus(false)
{
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

    if (m_isFocus) {

        // set player rotation
        int mouseX = Input::GetMousePosX();
        int mouseY = Input::GetMousePosY();
        int mainPinX;
        int mainPinY;
        std::tie(mainPinX, mainPinY) = m_player->getMainPinPos();
        int dx = mouseX - mainPinX;
        int dy = mouseY - mainPinY;
        double radian = std::atan2(dy, dx);
        m_player->m_degree = Mathtool::radToDeg(radian);

        // set player position
        float subPinX;
        float subPinY;
        std::tie(subPinX, subPinY) = m_player->getSubPinPosRotated();
        float w = subPinX - m_player->m_x;
        float h = subPinY - m_player->m_y;
        m_player->m_x = mouseX - w;
        m_player->m_y = mouseY - h;

    }

    // Menu
    if (!m_isFocus) {
        Render::DrawText(0, 0, 400, 40, L"Click to start game");
    } else {
        Render::DrawText(0, 0, 400, 40, L"Push escape to stop game");
    }

    bool isMenuKeyDowned = Input::GetKey(VK_ESCAPE);

    if (isMenuKeyDowned) {
        ClipCursor(NULL);
        ShowCursor(true);
        m_isFocus = false;

        return new MenuState();
    }

    // FIXME: m_isFocusもチェックしないと何度もShowCursor(false)が呼ばれて、一度のShowCursor(true)の呼び出しだけでは可視化できなくなる
    if (Input::GetMouseDownL() && m_isFocus != true) {
        RECT rc;
        GetWindowRect(Render::m_hwnd, &rc);
        ClipCursor(&rc);
        ShowCursor(false);
        m_isFocus = true;
    }
    return NULL;
}

void GameState::onMouseMove()
{
}