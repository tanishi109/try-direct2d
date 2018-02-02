#pragma once

#include "TerrainType.h"

template<typename unsigned short W, typename unsigned short H>
struct TileMapRecord
{
    char id[16];
    char name[16];
    unsigned short width = W;
    unsigned short height = H;
    unsigned short tileSize;
    TerrainType terrainTypeMatrix[W][H];
    unsigned short xPos;
    unsigned short yPos;
};

