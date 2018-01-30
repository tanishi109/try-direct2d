#include "stdafx.h"
#include "CanvasState.h"
#include "CanvasMenuState.h"
#include "Input.h"
#include "Render.h"

World* CanvasState::m_world = new World();

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
    m_gameObjects.push_back(m_world);
}

SceneState* CanvasState::update()
{
    // •¶Žš‚Ì•`‰æ
    // FIXME: ‚±‚±‚à‚Á‚Æ‚¢‚¢•û–@‚È‚¢‚Ì? ${}‚Ý‚½‚¢‚È
    std::wstring screenX = std::to_wstring(m_screen->m_x);
    std::wstring screenY = std::to_wstring(m_screen->m_y);
    std::wstring textLight = L"(";
    std::wstring textMiddle = L", ";
    std::wstring textRight = L")";
    Render::DrawText(0, 0, 100, 40, textLight + screenX + textMiddle + screenY + textRight);

    bool isMouseDownL = Input::GetMouseDownL();
    bool isGrabKeyDowned = Input::GetKey(VK_SPACE);

    if (isGrabKeyDowned) {
        SetCursor(m_grabCursor);
    } else {
        SetCursor(m_defaultCursor);
    }

    if (isMouseDownL && !isGrabKeyDowned) {
        const int mouseX = Input::GetMousePosX();
        const int mouseY = Input::GetMousePosY();
        m_world->setTileFromPos(TerrainType_wall, mouseX + m_screen->m_x, mouseY + m_screen->m_y);
    }
    bool isMouseDownR = Input::GetMouseDownR();
    if (isMouseDownR && !isGrabKeyDowned) {
        const int mouseX = Input::GetMousePosX();
        const int mouseY = Input::GetMousePosY();
        m_world->setTileFromPos(TerrainType_floor, mouseX + m_screen->m_x, mouseY + m_screen->m_y);
    }

    bool isMenuKeyDowned = Input::GetKey(VK_ESCAPE);
    if (isMenuKeyDowned) {
        return new CanvasMenuState();
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
        m_screen->m_x -= deltaX;
        m_screen->m_y -= deltaY;
    }
}
