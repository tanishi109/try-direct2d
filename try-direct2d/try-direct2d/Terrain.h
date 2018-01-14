#pragma once
class Terrain
{
public:
    Terrain(int type);
    ~Terrain();
    // 0 = floor, 1 = wall
    // TODO: use Enum
    int m_type;
};
