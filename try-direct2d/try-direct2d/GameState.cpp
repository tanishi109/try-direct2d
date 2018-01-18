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
    // TODO: CanvasState���璼�ڎ���Ă��Ă��邪�A�O���t�@�C���Ƃ��ĕۑ����ēǂݏo���`���ɂ�����
    World* world = CanvasState::m_world;
    int size = world->SIZE;
    int offsetX = 0; // ��������[��
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

    // FIXME: m_isFocus���`�F�b�N���Ȃ��Ɖ��x��ShowCursor(false)���Ă΂�āA��x��ShowCursor(true)�̌Ăяo�������ł͉����ł��Ȃ��Ȃ�
    if (Input::GetMouseDownL() && m_isFocus != true) {
        // �J�[�\���̉��͈͂��Œ�
        RECT rc;
        GetWindowRect(Render::m_hwnd, &rc);
        ClipCursor(&rc);
        // �J�[�\����s����
        ShowCursor(false);
        // �J�[�\�����v���C���[�̍��W�Ɉړ�
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