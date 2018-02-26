#include "stdafx.h"
#include "GameState.h"
#include "GameMenuState.h"
#include "CanvasState.h"
#include "Input.h"
#include "Render.h"
#include "Mathtool.h"
#include "Collision.h"

GameState::GameState() :
m_player(new Player(0, 0, 50, 10))
{
}

// FIXME; こういうのやるならresourceに書くべき
int CHILD_COUNT = 3;

GameState::~GameState()
{
    delete m_player;
}

void GameState::enter(Scene& scene)
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
    Input::m_captureCursorMode = true;
}

void GameState::update(Scene* scene)
{
    if (Input::GetKeyDown(VK_ESCAPE)) {
        // FIXME: onLeave的なのが欲しいね
        // FIXME: IdleStateでやっていることの後処理であることが分かりにくい
        ClipCursor(nullptr);
        Input::m_captureCursorMode = false;
        ShowCursor(true);

        scene->push(new GameMenuState());
        return;
    }

    // FIXME: playerにsceneも渡すより、onGoalハンドラを持たせて実行したほうがいいかな?
    m_player->update(*m_screen, *scene);
}

void GameState::initPosition()
{
    long width;
    long height;
    std::tie(width, height) = Render::GetClientSize();

    // スタート地点が画面中央に来るようにscreenを配置
    m_screen->m_x = -1 * width / 2  + World::TILE_SIZE * 2;
    m_screen->m_y = -1 * height / 2 + World::TILE_SIZE * 2;

    // 中心に配置
    Player* targetPlayer = m_player;
    int playerX;
    int playerY;
    std::tie(playerX, playerY) = m_screen->screenToWorld(width / 2, height / 2);
    while (targetPlayer != nullptr) {
        targetPlayer->setMainPinPos(playerX, playerY);
        targetPlayer = targetPlayer->m_child;
    }
}
