#include "stdafx.h"
#include "World.h"


World::World() :
m_floorTerrain(0),
m_wallTerrain(1)
{
    // init all tile by floorTerrain
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            m_tiles[x][y] = &m_floorTerrain;
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