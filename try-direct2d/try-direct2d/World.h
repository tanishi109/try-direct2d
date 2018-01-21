#pragma once

#include "Terrain.h"

class World
{
public:
    World();
    ~World();

    static const int WIDTH = 20;
    static const int HEIGHT = 20;
    static const int TILE_SIZE = 32;
    Terrain* m_tiles[WIDTH][HEIGHT];

    void setTileFromPos(TerrainType type, int x, int y);
    void render(int screenX, int screenY);
private:
    Terrain m_floorTerrain;
    Terrain m_wallTerrain;
    Terrain m_goalTerrain;

    bool isOuter(int x, int y);
    bool isRightBottom(int x, int y);
};

