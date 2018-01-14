#pragma once

#include "Terrain.h"

class World
{
public:
    World();
    ~World();

    static const int WIDTH = 10;
    static const int HEIGHT = 10;
    static const int SIZE = 32;
    Terrain* m_tiles[WIDTH][HEIGHT];
private:
    Terrain m_floorTerrain;
    Terrain m_wallTerrain;
};

