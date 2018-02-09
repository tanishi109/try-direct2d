#include "stdafx.h"

#include "SceneState.h"
#include "CanvasMenuState.h"
#include "CanvasState.h"
#include "GameState.h"
#include "Render.h"
#include "Input.h"
#include "TileMapRecord.h"
#include "Stringtool.h"

#include "Constant.h"

CanvasMenuState::CanvasMenuState() :
m_textPosList{
    {0, 0},
    {30, 100},
    {30, 200},
    {30, 300}
},
m_textList {
    "Menu",
    "push 1. Canvas Mode",
    "push 2. Game Mode",
    "push 0. Save this Canvas"
}
{
}


CanvasMenuState::~CanvasMenuState()
{
}

void CanvasMenuState::enter(Scene& scene)
{
    Render::TakeScreenShot();
}

void CanvasMenuState::update(Scene* scene)
{
    Render::Clear();

    Render::DrawScreenShot();

    static const int width = 400;
    for (auto &pos : m_textPosList) {
        int index = &pos - &m_textPosList[0];
        int x = pos[0];
        int y = pos[1];
        std::string text = m_textList[index];

        Render::DrawString(x, y, width, 40, text);
    }

    bool is1KeyDowned = Input::GetKey(0x31);
    bool is2KeyDowned = Input::GetKey(0x32);
    bool is0KeyDowned = Input::GetKey(0x30);

    if (is1KeyDowned) {
        scene->pop();
    }
    if (is2KeyDowned) {
        scene->push(new GameState());
    }
    if (is0KeyDowned) {
        saveTileMap();
    }
}

void CanvasMenuState::saveTileMap()
{

    std::string folderPath = Stringtool::GetAsString("./", Constant::DataFolderName);
    _mkdir(folderPath.c_str());

    std::time_t time = std::time(nullptr);
    std::string fileId = Stringtool::GetAsString(time);
    std::string filePath = Stringtool::GetAsString(folderPath, "/", fileId, ".dat");

    std::ofstream ofs(filePath, std::ios::out | std::ios::trunc | std::ios::binary);

    if (!ofs)
    {
        Debug::log(":err, file open");
        return;
    }

    TileMapRecord<World::WIDTH, World::HEIGHT> tileMapRecord = CanvasState::m_world->save(fileId);
    ofs.write(reinterpret_cast<char *>(&tileMapRecord), sizeof(tileMapRecord));
    ofs.close();
}
