#include "stdafx.h"
#include "ControllableState.h"
#include "Render.h"
#include "Input.h"
#include "Mathtool.h"
#include "Constant.h"
#include "CanvasState.h"
#include "Collision.h"
#include "MissedState.h"
#include "GoaledState.h"

ControllableState::ControllableState()
{
}

ControllableState::~ControllableState()
{
}

void ControllableState::enter(Player& player)
{
    Input::m_captureCursorMode = true;
    while(ShowCursor(false) > 0);

    RECT rc;
    GetWindowRect(Render::m_hwnd, &rc);
    ClipCursor(&rc);
}

PlayerState* ControllableState::update(Player& player, Screen& screen)
{
    Render::DrawString(0, 0, 300, 30, "Push escape key to stop game");

    scroll(player, screen);

    if (Input::GetMouseDeltaX() != 0 || Input::GetMouseDeltaY() != 0) {
        player.move(&screen);
    }

    // �����蔻��`�F�b�N
    // FIXME: ��������ȊO�̕��@������
    Terrain* hitTerrain = checkCollision(player);
    if (hitTerrain != nullptr) {
        if (hitTerrain->m_type == TerrainType_wall) {
            return new MissedState();
        }
        if (hitTerrain->m_type == TerrainType_goal) {
            return new GoaledState();
        }
    }

    return nullptr;
}

// �J�[�\�����������痣��Ă�����X�N���[��������
// TODO: �����̎�ŃX�N���[�����������Ƃ���
void ControllableState::scroll(Player& player, Screen& screen)
{
    long width;
    long height;
    std::tie(width, height) = Render::GetClientSize();
    POINT screenCenter = { width / 2, height / 2 };

    float subPinX;
    float subPinY;
    std::tie(subPinX, subPinY) = player.getSubPinPosRotated();
    std::tie(subPinX, subPinY) = screen.worldToScreen(subPinX, subPinY);

    float distance = Mathtool::getDistance(screenCenter.x, screenCenter.y, subPinX, subPinY);

    if (distance > Constant::ScrollDistance) {
        float radian = Mathtool::getRadFromPos(screenCenter.x, screenCenter.y, subPinX, subPinY);

        if (distance > Constant::FollowDistance) {
            // �傫������Ă�����X�N���[�����v���C���[���W�ƈ�v
            std::tie(subPinX, subPinY) = screen.screenToWorld(subPinX, subPinY);
            screen.m_x = subPinX - std::cos(radian) * Constant::FollowDistance - width / 2 ;
            screen.m_y = subPinY - std::sin(radian) * Constant::FollowDistance - height / 2;
            return;
        } else {
            screen.m_x += std::cos(radian) * Constant::ScrollSpeed;
            screen.m_y += std::sin(radian) * Constant::ScrollSpeed;
        }
    }
}

Terrain* ControllableState::checkCollision(Player& player)
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

            Player* focusedPlayer = &player;
            while(focusedPlayer != nullptr) {
                int mainPinX;
                int mainPinY;
                std::tie(mainPinX, mainPinY) = focusedPlayer->getMainPinPos();
                isHit = Collision::CheckCircleCollision(
                    x * size + size / 2, y * size + size / 2, size / 2,
                    mainPinX, mainPinY, focusedPlayer->m_collisionRadius
                );
                if (isHit) {
                    return tile;
                }
                // �q������΂��̓����蔻����`�F�b�N
                focusedPlayer = focusedPlayer->m_child;
            }
        }
    }

    return nullptr;
}
