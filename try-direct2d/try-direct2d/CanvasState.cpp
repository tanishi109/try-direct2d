#include "stdafx.h"
#include "CanvasState.h"
#include "CanvasMenuState.h"
#include "Input.h"
#include "Render.h"
#include "Stringtool.h"
#include "BrushType.h"

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
    // 文字の描画
    std::string posText = Stringtool::GetAsString("(", m_screen->m_x, ", ", m_screen->m_y, ")");
    Render::DrawString(0, 0, 100, 40, posText);

    bool isMouseDownL = Input::GetMouseDownL();
    bool isGrabKeyDowned = Input::GetKey(VK_SPACE);

    if (isGrabKeyDowned) {
        SetCursor(m_grabCursor);
    } else {
        SetCursor(m_defaultCursor);
    }

    // タイルに対する操作
    int mouseX = Input::GetMousePosX();
    int mouseY = Input::GetMousePosY();
    std::tie(mouseX, mouseY) = m_screen->screenToWorld(mouseX, mouseY);
    int tileX = std::floor(mouseX / World::TILE_SIZE) * World::TILE_SIZE;
    int tileY = std::floor(mouseY / World::TILE_SIZE) * World::TILE_SIZE;
    std::tie(tileX, tileY) = m_screen->worldToScreen(tileX , tileY);
    // Show target tile
    Render::DrawRect(tileX, tileY, World::TILE_SIZE, World::TILE_SIZE, BrushType_green);

    if (isMouseDownL && !isGrabKeyDowned) {
        m_world->setTileFromPos(TerrainType_wall, mouseX, mouseY);
    }
    bool isMouseDownR = Input::GetMouseDownR();
    if (isMouseDownR && !isGrabKeyDowned) {
        m_world->setTileFromPos(TerrainType_floor, mouseX, mouseY);
    }

    // メニュー表示
    bool isMenuKeyDowned = Input::GetKeyDown(VK_ESCAPE);
    if (isMenuKeyDowned) {
        scene->push(new CanvasMenuState());
        return;
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
