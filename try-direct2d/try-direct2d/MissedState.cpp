#include "stdafx.h"
#include "MissedState.h"
#include "CanvasState.h"
#include "ControllableState.h"
#include "Render.h"

MissedState::MissedState() :
m_stateTimer{30}
{
}

MissedState::~MissedState()
{
}

PlayerState* MissedState::update(Player& player, Screen& screen)
{
    m_stateTimer--;

    Render::DrawString(0, 0, 300, 30, "Oops!");

    if (m_stateTimer <= 0) {
        // スタート地点に戻す
        int x;
        int y;
        std::tie(x, y) = CanvasState::m_world->m_startPos;
        player.setMainPinPos(x, y);
        Player* focusedPlayer = &player;
        while (focusedPlayer != nullptr) {
            focusedPlayer->setMainPinPos(x, y);
            focusedPlayer->m_degree = 45;
            focusedPlayer = focusedPlayer->m_child;
        }

        return new ControllableState();
    }

    return nullptr;
}
