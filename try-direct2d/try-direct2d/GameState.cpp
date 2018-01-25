#include "stdafx.h"
#include "GameState.h"
#include "MenuState.h"
#include "CanvasState.h"
#include "Input.h"
#include "Render.h"
#include "Mathtool.h"
#include "Collision.h"

GameState::GameState() :
m_player(new Player(0, 0, 50, 10)),
m_isFocus(false)
{
}

// FIXME; こういうのやるならresourceに書くべき
int SCROLL_DISTANCE = 100;
int SCROLL_SPEED = 5;
int CHILD_COUNT = 3;

GameState::~GameState()
{
    delete m_player;
}

void GameState::enter()
{
    // World
    // TODO: CanvasStateから直接取ってきているが、外部ファイルとして保存して読み出す形式にしたい
    m_gameObjects.push_back(CanvasState::m_world);
    // Player
    m_gameObjects.push_back(m_player);

    // 子を追加
    Player* parent = m_player;
    for (int i = 0; i < CHILD_COUNT; i++) {
        parent->addChild();
        parent = parent->m_child;
    }

    initPosition();
}

// カーソルが中央から離れていたらスクロールさせる
void GameState::scroll()
{
    RECT windowRect;
    GetClientRect(Render::m_hwnd, &windowRect);

    long width = windowRect.right - windowRect.left;
    long height = windowRect.bottom - windowRect.top;

    POINT screenCenter = { width / 2, height / 2 };
    ClientToScreen(Render::m_hwnd, &screenCenter);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    float distance = Mathtool::getDistance(screenCenter.x, screenCenter.y, cursorPos.x, cursorPos.y);

    if (distance > SCROLL_DISTANCE) {
        float radian = Mathtool::getRadFromPos(screenCenter.x, screenCenter.y, cursorPos.x, cursorPos.y);

        float newCursorX = cursorPos.x - std::cos(radian) * SCROLL_SPEED;
        float newCursorY = cursorPos.y - std::sin(radian) * SCROLL_SPEED;

        // プレイヤーをスクロールのために移動
        POINT pt = { newCursorX, newCursorY };
        ScreenToClient(Render::m_hwnd, &pt);
        m_player->setSubPinPos(pt.x, pt.y);
        // 子も再帰的に移動
        Player* child = m_player->m_child;
        while (child != NULL) {
            int parentMainPinX;
            int parentMainPinY;
            std::tie(parentMainPinX, parentMainPinY) = child->m_parent->getMainPinPos();

            child->setSubPinPos(parentMainPinX, parentMainPinY);

            child = child->m_child;
        }
        // カーソルをスクロールのために移動
        SetCursorPos(newCursorX, newCursorY);
        m_screen->m_x += std::cos(radian) * SCROLL_SPEED;
        m_screen->m_y += std::sin(radian) * SCROLL_SPEED;
    }
}

Terrain* GameState::checkCollision()
{
    bool isHit = false;
    int size = CanvasState::m_world->TILE_SIZE;

    for (int x = 0; x < CanvasState::m_world->WIDTH; x++) {
        for (int y = 0; y < CanvasState::m_world->HEIGHT; y++) {

            Terrain* tile = CanvasState::m_world->m_tiles[x][y];

            // floorなら衝突チェックはしない
            // FIXME: Terrainにcollidable的なフィールドを足す
            if (tile->m_type == TerrainType_floor) {
                continue;
            }

            Player* player = m_player;
            while(player != NULL) {
                int mainPinX;
                int mainPinY;
                std::tie(mainPinX, mainPinY) = player->getMainPinPos();
                isHit = Collision::CheckCircleCollision(
                    x * size, y * size, size / 2,
                    mainPinX, mainPinY, player->m_collisionRadius
                );
                if (isHit) {
                    return tile;
                }
                // 子がいればその当たり判定もチェック
                player = player->m_child;
            }
        }
    }

    return NULL;
}

SceneState* GameState::update()
{
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

        setCursorOnPlayer();
    }

    if (m_isFocus) {
        scroll();
        m_player->move(m_screen);
    }

    // 当たり判定チェック
    // FIXME: 総当たり以外の方法がある
    Terrain* hitTerrain = checkCollision();
    if (hitTerrain != NULL) {
        if (hitTerrain->m_type == TerrainType_wall) {
            initPosition();
            setCursorOnPlayer();
        }
        if (hitTerrain->m_type == TerrainType_goal) {
            Render::DrawText(0, 0, 100, 32, L"Clear!");
        }
    }

    return NULL;
}

void GameState::initPosition()
{
    RECT rc;
    GetClientRect(Render::m_hwnd, &rc);

    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;

    // スタート地点が画面中央に来るようにscreenを配置
    m_screen->m_x = -1 * width / 2  + World::TILE_SIZE * 2;
    m_screen->m_y = -1 * height / 2 + World::TILE_SIZE * 2;

    // 中心に配置
    Player* player = m_player;
    while (player != NULL) {
        player->setMainPinPos(width / 2, height / 2);
        player = player->m_child;
    }
}

void GameState::setCursorOnPlayer()
{
    int playerX;
    int playerY;
    std::tie(playerX, playerY) = m_player->getSubPinPosRotated();
    POINT playerPos = {playerX, playerY};
    ClientToScreen(Render::m_hwnd, &playerPos);
    SetCursorPos(playerPos.x, playerPos.y);
}
