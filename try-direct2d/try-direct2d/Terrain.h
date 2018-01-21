#pragma once
#include "TerrainType.h"
#include "BrushType.h"

class Terrain
{
public:
    Terrain(TerrainType type, BrushType color);
    ~Terrain();
    TerrainType m_type;
    BrushType m_color;
};
