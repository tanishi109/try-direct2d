#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "CanvasState.h"
#include "Input.h"
#include "Render.h"
#include "Mathtool.h"
#include "Collision.h"

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

bool GameState::checkCollision()
{
    bool isHit = false;

    int size = CanvasState::m_world->SIZE;
    int offsetX = m_screenPos[0];
    int offsetY = m_screenPos[1];
    for (int x = 0; x < CanvasState::m_world->WIDTH; x++) {
        for (int y = 0; y < CanvasState::m_world->HEIGHT; y++) {
            Terrain* tile = CanvasState::m_world->m_tiles[x][y];
            if (tile->m_type == 0) {
                continue;
            }

            int mainPinX;
            int mainPinY;
            std::tie(mainPinX, mainPinY) = m_player->getMainPinPos();
            isHit = Collision::CheckCircleCollision(
                x * size + offsetX, y * size + offsetY, size / 2,
                mainPinX, mainPinY, m_player->m_collisionRadius
            );
            if (isHit) {
                return isHit;
            }

            for (int c = 0; c < m_player->m_childrenCount; c++) {
                Player* child = m_player->getNthChild(c);

                int childMainPinX;
                int childMainPinY;
                std::tie(childMainPinX, childMainPinY) = child->getMainPinPos();
                isHit = Collision::CheckCircleCollision(
                    x * size + offsetX, y * size + offsetY, size / 2,
                    childMainPinX, childMainPinY, child->m_collisionRadius
                );
                if (isHit) {
                    return isHit;
                }
            }
        }
    }

    return false;
}

SceneState* GameState::update()
{
    Render::Clear();

    // World
    // TODO: CanvasStateから直接取ってきているが、外部ファイルとして保存して読み出す形式にしたい
    CanvasState::m_world->render(m_screenPos[0], m_screenPos[1]);

    // Player
    m_player->render();

    // Menu
    bool isMenuKeyDowned = Input::GetKey(VK_ESCAPE);

    // Handle focus
    if (isMenuKeyDowned) {
        m_isFocus = false;
        ClipCursor(NULL);
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

    // 当たり判定チェック
    // FIXME: 総当たり以外の方法がある
    bool isHit = checkCollision();
    if (isHit) {
        log("hit top = %d!\n", isHit);
    }

    return NULL;
}

void GameState::onMouseMove()
{
    if (m_isFocus) {
        m_player->update();
    }
}