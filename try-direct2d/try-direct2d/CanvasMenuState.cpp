#include "stdafx.h"

#include "SceneState.h"
#include "CanvasMenuState.h"
#include "CanvasState.h"
#include "GameState.h"
#include "Render.h"
#include "Input.h"

CanvasMenuState::CanvasMenuState() :
m_textPosList{{0, 0}, {30, 100}, {30, 200}},
m_textList{L"Menu", L"push 1. Canvas Mode", L"push 2. Game Mode"}
{
}


CanvasMenuState::~CanvasMenuState()
{
}

void CanvasMenuState::enter()
{
    Render::TakeScreenShot();
}

SceneState* CanvasMenuState::update()
{
    Render::Clear();

    Render::DrawScreenShot();

    static const int width = 400;
    for (auto &pos : m_textPosList) {
        int index = &pos - &m_textPosList[0];
        int x = pos[0];
        int y = pos[1];
        std::wstring text = m_textList[index];

        Render::DrawText(x, y, width, 40, text);
    }

    bool is1KeyDowned = Input::GetKey(0x31);
    bool is2KeyDowned = Input::GetKey(0x32);

    if (is1KeyDowned) {
        return new CanvasState();
    }
    if (is2KeyDowned) {
        return new GameState();
    }

    return NULL;
}

void CanvasMenuState::onMouseMove()
{
}
