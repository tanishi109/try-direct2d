#include "stdafx.h"

#include "SceneState.h"
#include "MenuState.h"
#include "CanvasState.h"
#include "Render.h";
#include "Input.h";

MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::enter()
{
}

SceneState* MenuState::update()
{
    Render::Clear();

    std::wstring text = L"This is Menu state!";
    Render::DrawText(0, 0, 100, 40, text);

    bool isMenuKeyDowned = Input::GetKey(VK_ESCAPE);
    if (isMenuKeyDowned) {
        return new CanvasState();
    }

    return NULL;
}

