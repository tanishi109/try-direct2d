#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "CanvasState.h"
#include "Input.h"
#include "Render.h"
#include "Mathtool.h"

int GameState::m_screenPos[2] = {0, 0};

GameState::GameState() :
m_player(new Player(0, 0, 50, 10, 3)),
m_isFocus(false)
{
}


GameState::~GameState()
{
    delete m_player;
}

void GameState::enter()
{
    RECT rc;
    GetClientRect(Render::m_hwnd, &rc);

    int width = static_cast<int>(rc.right) - static_cast<int>(rc.left);
    int height = rc.bottom - rc.top;

    // 中心に配置
    m_player->setMainPinPos(width / 2, height / 2);
}

SceneState* GameState::update()
{
    Render::Clear();

    // World
    // TODO: CanvasStateから直接取ってきているが、外部ファイルとして保存して読み出す形式にしたい
    World* world = CanvasState::m_world;
    int size = world->SIZE;
    int offsetX = m_screenPos[0];
    int offsetY = m_screenPos[1];
    for (int x = 0; x < world->WIDTH; x++) {
        for (int y = 0; y < world->HEIGHT; y++) {

            Terrain* tile = world->m_tiles[x][y];
            Render::DrawRect(
                x * size + offsetX,
                y * size + offsetY,
                size,
                size,
                tile->m_type
                //1
            );
        }
    }

    // Player
    m_player->render();

    // Menu
    bool isMenuKeyDowned = Input::GetKey(VK_ESCAPE);

    // Handle focus
    if (isMenuKeyDowned) {
        m_isFocus = false;
        return new MenuState();
    }

    if (Input::GetMouseDownL() && !m_isFocus) {
        m_isFocus = true;

        RECT rc;
        GetWindowRect(Render::m_hwnd, &rc);
        ClipCursor(&rc);
    }

    // Check cursor is not so far from center
    if (m_isFocus) {
        RECT windowRect;
        GetClientRect(Render::m_hwnd, &windowRect);

        long width = windowRect.right - windowRect.left;
        long height = windowRect.bottom - windowRect.top;

        POINT screenCenter = {width / 2, height / 2};
        ClientToScreen(Render::m_hwnd, &screenCenter);

        POINT cursorPos;
        GetCursorPos(&cursorPos);

        float distance = Mathtool::getDistance(screenCenter.x, screenCenter.y, cursorPos.x, cursorPos.y);

        if (distance > 20) {
            float radian = Mathtool::getRadFromPos(screenCenter.x, screenCenter.y, cursorPos.x, cursorPos.y);
            int delta = 5;
                                               
            float newCursorX = cursorPos.x - std::cos(radian) * delta;
            float newCursorY = cursorPos.y - std::sin(radian) * delta;

            POINT pt = {newCursorX, newCursorY};
            ScreenToClient(Render::m_hwnd, &pt);
            m_player->setSubPinPos(pt.x, pt.y);
            SetCursorPos(newCursorX, newCursorY);
            m_screenPos[0] -= std::cos(radian) * delta;
            m_screenPos[1] -= std::sin(radian) * delta;
        }
    }


    return NULL;
}

void GameState::onMouseMove()
{
    if (m_isFocus) {
        m_player->update();
    }
}