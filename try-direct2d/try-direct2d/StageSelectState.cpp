#include "stdafx.h"

#include "StageSelectState.h"
#include "Render.h"
#include "Input.h"
#include "CanvasState.h"

StageSelectState::StageSelectState()
{
}


StageSelectState::~StageSelectState()
{
}

void StageSelectState::enter()
{
    log("Enter stage select state\n");
}

SceneState* StageSelectState::update()
{
    Render::DrawText(30, 30, 200, 30, L"Press Enter to create new stage");

    if (Input::GetKey(VK_RETURN)) {
        return new CanvasState();
    }

    return NULL;
}
