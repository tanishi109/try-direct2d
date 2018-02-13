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

std::function<void(int)> CanvasMenuState::m_onSelect = [](int index){
};


ScrollableList& CanvasMenuState::m_list = *new ScrollableList(m_onSelect, {
    "Try to play", 
    "Save as new", 
    "Save this file (WIP)",
    "Back to Stage Select"
});

CanvasMenuState::CanvasMenuState()
{
    m_list.m_marginPx.assign(8, 80);
    m_gameObjects.push_back(&m_list);
}


CanvasMenuState::~CanvasMenuState()
{
}

void CanvasMenuState::enter(Scene& scene)
{
    Render::TakeScreenShot();

    m_onSelect = [&scene, this](int index){
        if (index == 0) {
            scene.push(new GameState());
            return;
        }
        if (index == 1) {
            saveTileMap();
            return;
        }
        if (index == 2) {
            // TODO: ã‘‚«•Û‘¶‚Å‚«‚é‚æ‚¤‚É‚·‚é
            saveTileMap();
            return;
        }
        if (index == 3) {
            scene.pop();
            scene.pop();
            return;
        }
    };
}

void CanvasMenuState::update(Scene* scene)
{
    Render::DrawScreenShot();

    if (Input::GetKeyDown(VK_ESCAPE)) {
        scene->pop();
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
