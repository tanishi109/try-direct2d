#pragma once

#include "Terrain.h"
#include "GameObject.h"
#include "TileMapRecord.h"

class World : public GameObject
{
public:
    World();
    ~World();

    static const int WIDTH = 20;
    static const int HEIGHT = 20;
    static const int TILE_SIZE = 32;
    Terrain* m_tiles[WIDTH][HEIGHT];
    std::tuple<int, int> m_startPos;

    void setTileFromPos(TerrainType type, int x, int y);
    void render(Screen* screen);
    TileMapRecord<WIDTH, HEIGHT> save(std::string fileId);
    void restore(TileMapRecord<WIDTH, HEIGHT> tileMapRecord);
private:
    Terrain m_floorTerrain;
    Terrain m_wallTerrain;
    Terrain m_goalTerrain;

    bool isOuter(int x, int y);
    bool isRightBottom(int x, int y);
};

