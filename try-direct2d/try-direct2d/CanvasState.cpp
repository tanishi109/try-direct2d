#include "stdafx.h"
#include "CanvasState.h"
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

void CanvasState::update()
{
    Render::Clear();
    for (int x = 0; x < m_world->WIDTH; x++) {
        for (int y = 0; y < m_world->HEIGHT; y++) {
            Terrain* tile = m_world->m_tiles[x][y];

            //char buf[256];
            //sprintf_s(buf, "Tile type = %d\n", tile->m_type);
            //OutputDebugStringA(buf);

            Render::DrawRect(
                static_cast<float>(x * m_world->SIZE),
                static_cast<float>(y * m_world->SIZE),
                static_cast<float>(m_world->SIZE),
                static_cast<float>(m_world->SIZE),
                tile->m_type
            );
        }
    }


    bool isMouseDown = Input::GetMouseDownL();
    bool isGrabKeyDowned = Input::GetKey(VK_SPACE);

    if (isGrabKeyDowned) {
        SetCursor(m_grabCursor);
    } else {
        SetCursor(m_defaultCursor);
    }

    if (isGrabKeyDowned && isMouseDown) {
        int deltaX = Input::GetMouseDeltaX();
        int deltaY = Input::GetMouseDeltaY();
        char buf[256];
        sprintf_s(buf, "delta = %d, %d\n", deltaX, deltaY);
        OutputDebugStringA(buf);
        return;
    }

    if (isMouseDown) {
        const int mouseX = Input::GetMousePosX();
        const int mouseY = Input::GetMousePosY();
        m_world->setWallFromMousePos(mouseX, mouseY);
    }
}
