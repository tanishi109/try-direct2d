#include "stdafx.h"
#include "CanvasState.h"
#include "MenuState.h"
#include "Input.h"
#include "Render.h"

World* CanvasState::m_world = new World();
int CanvasState::m_screenPos[2] = {0, 0};

CanvasState::CanvasState() :
m_grabCursor(LoadCursor(NULL, IDC_SIZEALL)),
m_defaultCursor(LoadCursor(NULL, IDC_ARROW))
{
}

CanvasState::~CanvasState()
{
}

void CanvasState::enter()
{
}

SceneState* CanvasState::update()
{
    Render::Clear();

    // マスの描画
    m_world->render(m_screenPos[0], m_screenPos[1]);

    // 文字の描画
    // FIXME: ここもっといい方法ないの? ${}みたいな
    std::wstring screenX = std::to_wstring(m_screenPos[0]);
    std::wstring screenY = std::to_wstring(m_screenPos[1]);
    std::wstring textLight = L"(";
    std::wstring textMiddle = L", ";
    std::wstring textRight = L")";
    Render::DrawText(0, 0, 100, 40, textLight + screenX + textMiddle + screenY + textRight);

    bool isMouseDown = Input::GetMouseDownL();
    bool isGrabKeyDowned = Input::GetKey(VK_SPACE);

    if (isGrabKeyDowned) {
        SetCursor(m_grabCursor);
    } else {
        SetCursor(m_defaultCursor);
    }

    if (isMouseDown && !isGrabKeyDowned) {
        const int mouseX = Input::GetMousePosX();
        const int mouseY = Input::GetMousePosY();
        m_world->setWallFromMousePos(mouseX, mouseY);
    }

    bool isMenuKeyDowned = Input::GetKey(VK_ESCAPE);
    if (isMenuKeyDowned) {
        return new MenuState();
    }

    return NULL;
}

void CanvasState::onMouseMove()
{
    bool isMouseDown = Input::GetMouseDownL();
    bool isGrabKeyDowned = Input::GetKey(VK_SPACE);

    if (isGrabKeyDowned && isMouseDown) {
        int deltaX = Input::GetMouseDeltaX();
        int deltaY = Input::GetMouseDeltaY();
        m_screenPos[0] -= deltaX;
        m_screenPos[1] -= deltaY;
    }
}
