#pragma once

#include "Terrain.h"

class World
{
public:
    World();
    ~World();

    static const int WIDTH = 20;
    static const int HEIGHT = 20;
    static const int SIZE = 32;
    Terrain* m_tiles[WIDTH][HEIGHT];

    void setWallFromMousePos(int mouseX, int mouseY);
    void render(int screenX, int screenY);
private:
    Terrain m_floorTerrain;
    Terrain m_wallTerrain;
};

