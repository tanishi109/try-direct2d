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

    int width;
    int height;
    std::tie(width, height) = Render::GetClientSize();
    m_startPos = std::make_tuple(TILE_SIZE * 2, TILE_SIZE * 2);
}


World::~World()
{
}

void World::setTileFromPos(TerrainType type, int x, int y)
{
    if (x < 0 || y < 0) {
        // TODO: マイナス方向にタイル置けるようにしたい
        return;
    }
    int tileX = std::floor(x / TILE_SIZE);
    int tileY = std::floor(y / TILE_SIZE);

    if (type == TerrainType_floor) {
        m_tiles[tileX][tileY] = &m_floorTerrain;
        return;
    }

    if (type == TerrainType_wall) {
        m_tiles[tileX][tileY] = &m_wallTerrain;
        return;
    }
}

void World::render(Screen* screen)
{
    int size = TILE_SIZE;
    int offsetX = screen->m_x;
    int offsetY = screen->m_y;
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {

            Terrain* tile = m_tiles[x][y];
            if (tile->m_type == TerrainType_floor) {
                continue;
            }
            Render::DrawCircle(
                x * size - offsetX + size / 2, // Tileに収まるように調整
                y * size - offsetY + size / 2,
                size / 2,
                tile->m_color
            );
        }
    }
}

// m_tilesからTileMapRecordを返す
TileMapRecord<World::WIDTH, World::HEIGHT> World::save(std::string fileId)
{
    TileMapRecord<WIDTH, HEIGHT> tileMapRecord;

    tileMapRecord.tileSize = World::TILE_SIZE;
    tileMapRecord.xPos = 0;
    tileMapRecord.yPos = 0;

    strcpy_s(tileMapRecord.name, 16, "1st stage");
    strcpy_s(tileMapRecord.id, 16, fileId.c_str());

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            Terrain* tile = m_tiles[x][y];
            tileMapRecord.terrainTypeMatrix[x][y] = tile->m_type;
        }
    }
    return tileMapRecord;
}

void World::restore(TileMapRecord<WIDTH, HEIGHT> tileMapRecord)
{
    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            TerrainType type = tileMapRecord.terrainTypeMatrix[x][y];
            if (type == TerrainType_floor) {
                m_tiles[x][y] = &m_floorTerrain;
            }
            if (type == TerrainType_wall) {
                m_tiles[x][y] = &m_wallTerrain;
            }
            if (type == TerrainType_goal) {
                m_tiles[x][y] = &m_goalTerrain;
            }
        }
    }
}

// 外周か判定
bool World::isOuter(int x, int y)
{
    bool isLeftTopOuter = x == 0 || y == 0;
    bool isRightBottomOuter = x == WIDTH - 1 || y == HEIGHT - 1;

    return isLeftTopOuter || isRightBottomOuter;
}

// 壁内の最も右下か判定
bool World::isRightBottom(int x, int y)
{
    return x == WIDTH - 2 && y == HEIGHT - 2;
}
