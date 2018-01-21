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
m_player(new Player(0, 0, 50, 10)),
m_isFocus(false)
{
}

// FIXME; ���������̂��Ȃ�resource�ɏ����ׂ�
int SCROLL_DISTANCE = 100;
int SCROLL_SPEED = 5;
int CHILD_COUNT = 3;

GameState::~GameState()
{
    delete m_player;
}

void GameState::enter()
{
    // �q��ǉ�
    Player* parent = m_player;
    for (int i = 0; i < CHILD_COUNT; i++) {
        parent->addChild();
        parent = parent->m_child;
    }

    // ���S�ɔz�u
    RECT rc;
    GetClientRect(Render::m_hwnd, &rc);

    int width = rc.right - rc.left;
    int height = rc.bottom - rc.top;

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

            Player* player = m_player;
            while(player != NULL) {
                int mainPinX;
                int mainPinY;
                std::tie(mainPinX, mainPinY) = player->getMainPinPos();
                isHit = Collision::CheckCircleCollision(
                    x * size + offsetX, y * size + offsetY, size / 2,
                    mainPinX, mainPinY, player->m_collisionRadius
                );
                if (isHit) {
                    return isHit;
                }
                // �q������΂��̓����蔻����`�F�b�N
                player = player->m_child;
            }
        }
    }

    return false;
}

SceneState* GameState::update()
{
    Render::Clear();

    // World
    // TODO: CanvasState���璼�ڎ���Ă��Ă��邪�A�O���t�@�C���Ƃ��ĕۑ����ēǂݏo���`���ɂ�����
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

        if (distance > SCROLL_DISTANCE) {
            float radian = Mathtool::getRadFromPos(screenCenter.x, screenCenter.y, cursorPos.x, cursorPos.y);
                                               
            float newCursorX = cursorPos.x - std::cos(radian) * SCROLL_SPEED;
            float newCursorY = cursorPos.y - std::sin(radian) * SCROLL_SPEED;

            // �v���C���[���X�N���[���̂��߂Ɉړ�
            POINT pt = {newCursorX, newCursorY};
            ScreenToClient(Render::m_hwnd, &pt);
            m_player->setSubPinPos(pt.x, pt.y);
            // �q���ċA�I�Ɉړ�
            Player* child = m_player->m_child;
            while(child != NULL) {
                int parentMainPinX;
                int parentMainPinY;
                std::tie(parentMainPinX, parentMainPinY) = child->m_parent->getMainPinPos();

                child->setSubPinPos(parentMainPinX, parentMainPinY);

                child = child->m_child;
            }
            // �J�[�\�����X�N���[���̂��߂Ɉړ�
            SetCursorPos(newCursorX, newCursorY);
            m_screenPos[0] -= std::cos(radian) * SCROLL_SPEED;
            m_screenPos[1] -= std::sin(radian) * SCROLL_SPEED;
        }
    }

    // �����蔻��`�F�b�N
    // FIXME: ��������ȊO�̕��@������
    bool isHit = checkCollision();
    if (isHit) {
        log("hit top = %d!\n", isHit);
    }

    return NULL;
}

void GameState::onMouseMove()
{
    // FIXME: �X�N���[���̂��߂Ƀ}�E�X�J�[�\���𓮂������Ƃ���onMouseMove���n���h�����O�����update����Ă��܂��A�����Ɉʒu���X�V����Ă���B�B�ǂ���������΂�����
    if (m_isFocus) {
        m_player->update();
    }
}