#include "stdafx.h"
#include "World.h"
#include "Render.h"
#include "BrushType.h"

World::World() :
m_floorTerrain(TerrainType_floor, BrushType_white),
m_wallTerrain(TerrainType_wall, BrushType_green),
m_goalTerrain(TerrainType_goal, BrushType_pink)
{
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            if (isOuter(x, y)) {
                m_tiles[x][y] = &m_wallTerrain;
            } else if (isRightBottom(x, y)) {
                m_tiles[x][y] = &m_goalTerrain;
            } else {
                m_tiles[x][y] = &m_floorTerrain;
            }
        }
    }
}


World::~World()
{
}

void World::setWallFromMousePos(int mouseX, int mouseY)
{
    int x = std::floor(mouseX / SIZE);
    int y = std::floor(mouseY / SIZE);

    m_tiles[x][y] = &m_wallTerrain;
}

void World::render(int screenX, int screenY)
{
    int size = SIZE;
    int offsetX = screenX;
    int offsetY = screenY;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            Terrain* tile = m_tiles[x][y];
            Render::DrawCircle(
                x * size + offsetX,
                y * size + offsetY,
                size / 2,
                tile->m_color
            );
        }
    }
}

// äOé¸Ç©îªíË
bool World::isOuter(int x, int y)
{
    bool isLeftTopOuter = x == 0 || y == 0;
    bool isRightBottomOuter = x == WIDTH - 1 || y == HEIGHT - 1;

    return isLeftTopOuter || isRightBottomOuter;
}

// ï«ì‡ÇÃç≈Ç‡âEâ∫Ç©îªíË
bool World::isRightBottom(int x, int y)
{
    return x == WIDTH - 2 && y == HEIGHT - 2;
}
