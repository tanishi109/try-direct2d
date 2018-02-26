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

void GoaledState::update(Player& player, Screen& screen, Scene& scene)
{
    m_stateTimer--;

    if (m_stateTimer <= 0) {
        scene.pop(2);
    }

    int width;
    int height;
    std::tie(width, height) = Render::GetClientSize();
    Render::DrawString(width / 2 - 50, height / 2 - 50, 100, 32, "Clear!");
}
