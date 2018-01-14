#include "stdafx.h"
#include "CanvasState.h"
#include "Input.h"
#include "Render.h"

World* CanvasState::m_world = new World();

CanvasState::CanvasState()
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
                static_cast<float>(m_world->SIZE)
            );
        }
    }
}
