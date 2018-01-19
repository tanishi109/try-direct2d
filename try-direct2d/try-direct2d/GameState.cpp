#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "CanvasState.h"
#include "Input.h"
#include "Render.h"
#include "Mathtool.h"

int GameState::m_screenPos[2] = {0, 0};

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

    return NULL;
}

void GameState::onMouseMove()
{
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
}