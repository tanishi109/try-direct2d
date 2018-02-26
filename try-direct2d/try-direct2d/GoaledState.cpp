#include "stdafx.h"
#include "GoaledState.h"
#include "Render.h"

GoaledState::GoaledState() :
m_stateTimer{90}
{
}

GoaledState::~GoaledState()
{
}

PlayerState* GoaledState::update(Player& player, Screen& screen)
{
    m_stateTimer--;

    if (m_stateTimer <= 0) {
        player.m_onGoal();
    }

    int width;
    int height;
    std::tie(width, height) = Render::GetClientSize();
    Render::DrawString(width / 2 - 50, height / 2 - 50, 100, 32, "Clear!");

    return nullptr;
}
