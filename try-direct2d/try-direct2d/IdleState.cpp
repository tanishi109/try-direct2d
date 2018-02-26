#include "stdafx.h"
#include "IdleState.h"
#include "Render.h"
#include "Input.h"
#include "ControllableState.h"

IdleState::IdleState()
{
}

IdleState::~IdleState()
{
}

PlayerState* IdleState::update(Player& player, Screen& screen)
{
    Render::DrawString(0, 0, 300, 30, "Click to start playing");

    if (Input::GetMouseDownL()) {
        return new ControllableState();
    }

    return nullptr;
}
