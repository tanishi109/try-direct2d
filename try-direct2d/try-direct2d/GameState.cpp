#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "CanvasState.h"
#include "Input.h"
#include "Render.h"
#include "Mathtool.h"

GameState::GameState() :
m_player(new Player(40, 60, 50, 20)),
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

    // World
    // TODO: CanvasStateから直接取ってきているが、外部ファイルとして保存して読み出す形式にしたい
    World* world = CanvasState::m_world;
    int size = world->SIZE;
    int offsetX = 0; // いったんゼロ
    int offsetY = 0;
    for (int x = 0; x < world->WIDTH; x++) {
        for (int y = 0; y < world->HEIGHT; y++) {

            Terrain* tile = world->m_tiles[x][y];
            Render::DrawRect(
                x * size - offsetX,
                y * size - offsetY,
                size,
                size,
                tile->m_type
            );
        }
    }

    // Player
    m_player->render();

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
        // カーソルの可動範囲を固定
        RECT rc;
        GetWindowRect(Render::m_hwnd, &rc);
        ClipCursor(&rc);
        // カーソルを不可視に
        ShowCursor(false);
        // カーソルをプレイヤーの座標に移動
        float subPinX;
        float subPinY;
        std::tie(subPinX, subPinY) = m_player->getSubPinPosRotated();
        POINT pt = {subPinX, subPinY};
        ClientToScreen(Render::m_hwnd, &pt);
        SetCursorPos(pt.x, pt.y);
        m_isFocus = true;
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