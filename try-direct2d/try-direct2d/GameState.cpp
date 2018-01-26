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

// FIXME; ���������̂��Ȃ�resource�ɏ����ׂ�
int SCROLL_DISTANCE = 10;
int FOLLOW_DISTANCE = 60;
int SCROLL_SPEED = 5;
int CHILD_COUNT = 3;

GameState::~GameState()
{
    delete m_player;
}

void GameState::enter()
{
    // World
    // TODO: CanvasState���璼�ڎ���Ă��Ă��邪�A�O���t�@�C���Ƃ��ĕۑ����ēǂݏo���`���ɂ�����
    m_gameObjects.push_back(CanvasState::m_world);
    // Player
    m_gameObjects.push_back(m_player);

    // �q��ǉ�
    Player* parent = m_player;
    for (int i = 0; i < CHILD_COUNT; i++) {
        parent->addChild();
        parent = parent->m_child;
    }

    initPosition();
    Input::m_captureCursorMode = true;
}

// �J�[�\�����������痣��Ă�����X�N���[��������
// TODO: �����̎�ŃX�N���[�����������Ƃ���
void GameState::scroll()
{
    RECT windowRect;
    GetClientRect(Render::m_hwnd, &windowRect);

    long width = windowRect.right - windowRect.left;
    long height = windowRect.bottom - windowRect.top;

    POINT screenCenter = { width / 2, height / 2 };

    float subPinX;
    float subPinY;
    std::tie(subPinX, subPinY) = m_player->getSubPinPosRotated();
    std::tie(subPinX, subPinY) = m_screen->WorldToScreen(subPinX, subPinY);

    float distance = Mathtool::getDistance(screenCenter.x, screenCenter.y, subPinX, subPinY);

    if (distance > SCROLL_DISTANCE) {
        float radian = Mathtool::getRadFromPos(screenCenter.x, screenCenter.y, subPinX, subPinY);

        if (distance > FOLLOW_DISTANCE) {
            // �傫������Ă�����X�N���[�����v���C���[���W�ƈ�v
            std::tie(subPinX, subPinY) = m_screen->screenToWorld(subPinX, subPinY);
            m_screen->m_x = subPinX - std::cos(radian) * FOLLOW_DISTANCE - width / 2 ;
            m_screen->m_y = subPinY - std::sin(radian) * FOLLOW_DISTANCE - height / 2;
            return;
        } else {
            m_screen->m_x += std::cos(radian) * SCROLL_SPEED;
            m_screen->m_y += std::sin(radian) * SCROLL_SPEED;
        }
    }
}

Terrain* GameState::checkCollision()
{
    bool isHit = false;
    int size = CanvasState::m_world->TILE_SIZE;

    for (int x = 0; x < CanvasState::m_world->WIDTH; x++) {
        for (int y = 0; y < CanvasState::m_world->HEIGHT; y++) {

            Terrain* tile = CanvasState::m_world->m_tiles[x][y];

            // floor�Ȃ�Փ˃`�F�b�N�͂��Ȃ�
            // FIXME: Terrain��collidable�I�ȃt�B�[���h�𑫂�
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
                // �q������΂��̓����蔻����`�F�b�N
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
        // FIXME: onLeave�I�Ȃ̂��~������
        m_isFocus = false;
        ClipCursor(NULL);
        Input::m_captureCursorMode = false;
        ShowCursor(true);
        return new MenuState();
    }

    if (Input::GetMouseDownL() && !m_isFocus) {
        m_isFocus = true;
        ShowCursor(false);

        RECT rc;
        GetWindowRect(Render::m_hwnd, &rc);
        ClipCursor(&rc);
    }

    if (m_isFocus) {
        scroll();
    }
    if (m_isFocus && (Input::GetMouseDeltaX() != 0 || Input::GetMouseDeltaY() != 0)) {
        m_player->move(m_screen);
    }

    // �����蔻��`�F�b�N
    // FIXME: ��������ȊO�̕��@������
    Terrain* hitTerrain = checkCollision();
    if (hitTerrain != NULL) {
        if (hitTerrain->m_type == TerrainType_wall) {
            initPosition();
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

    // �X�^�[�g�n�_����ʒ����ɗ���悤��screen��z�u
    m_screen->m_x = -1 * width / 2  + World::TILE_SIZE * 2;
    m_screen->m_y = -1 * height / 2 + World::TILE_SIZE * 2;

    // ���S�ɔz�u
    Player* player = m_player;
    int playerX;
    int playerY;
    // FIXME: ���\�b�h���ŏ���������������
    std::tie(playerX, playerY) = m_screen->screenToWorld(width / 2, height / 2);
    while (player != NULL) {
        player->setMainPinPos(playerX, playerY);
        player = player->m_child;
    }
}
