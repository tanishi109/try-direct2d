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
    int size = m_world->SIZE;
    int offsetX = m_screenPos[0];
    int offsetY = m_screenPos[1];
    for (int x = 0; x < m_world->WIDTH; x++) {
        for (int y = 0; y < m_world->HEIGHT; y++) {
        
            Terrain* tile = m_world->m_tiles[x][y];
            Render::DrawRect(
                x * size - offsetX,
                y * size - offsetY,
                size,
                size,
                tile->m_type
            );
        }
    }

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

    if (isMouseDown) {
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
