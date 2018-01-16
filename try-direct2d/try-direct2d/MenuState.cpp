#include "stdafx.h"

#include "SceneState.h"
#include "MenuState.h"
#include "CanvasState.h"
#include "Render.h"
#include "Input.h"

MenuState::MenuState() :
m_textPosList{{0, 0}, {30, 100}, {30, 200}},
m_textList{L"Menu", L"Canvas Mode", L"Game Mode"}
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

    static const int width = 400;
    for (auto &pos : m_textPosList) {
        int index = &pos - &m_textPosList[0];
        int x = pos[0];
        int y = pos[1];
        std::wstring text = m_textList[index];

        Render::DrawText(x, y, width, 40, text);
    }

    bool isMouseDown = Input::GetMouseDownL();

    if (isMouseDown) {
        return new CanvasState();
    }

    return NULL;
}

void MenuState::onMouseMove()
{
}
