#include "stdafx.h"
#include "CanvasState.h"
#include "CanvasMenuState.h"
#include "Input.h"
#include "Render.h"
#include "Stringtool.h"

World* CanvasState::m_world = new World();

CanvasState::CanvasState() :
m_grabCursor(LoadCursor(nullptr, IDC_SIZEALL)),
m_defaultCursor(LoadCursor(nullptr, IDC_ARROW))
{
}

CanvasState::~CanvasState()
{
}

void CanvasState::enter(Scene& scene)
{
    m_gameObjects.push_back(m_world);
}

void CanvasState::update(Scene* scene)
{
    // •¶Žš‚Ì•`‰æ
    std::string posText = Stringtool::GetAsString("(", m_screen->m_x, ", ", m_screen->m_y, ")");
    Render::DrawString(0, 0, 100, 40, posText);

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
        scene->push(new CanvasMenuState());
    }
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
