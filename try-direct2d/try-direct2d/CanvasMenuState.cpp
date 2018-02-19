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

std::string CanvasMenuState::m_fileId;

std::function<void(int)> CanvasMenuState::m_onSelect = [](int index){
};


ScrollableList& CanvasMenuState::m_list = *new ScrollableList(m_onSelect, {
    "Try to play", 
    "Save", 
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
            m_fileId = getFileId();
            saveTo(m_fileId);
            return;
        }
        if (index == 2) {
            scene.pop(2);
            return;
        }
    };
}

void CanvasMenuState::update(Scene* scene)
{
    Render::DrawScreenShot(0);

    if (Input::GetKeyDown(VK_ESCAPE)) {
        scene->pop();
    }
}

std::string CanvasMenuState::getFileId()
{
    if (!m_fileId.empty()) {
        return m_fileId;
    }
    std::time_t time = std::time(nullptr);
    std::string fileId = Stringtool::GetAsString(time);

    return fileId;
}

void CanvasMenuState::saveTo(std::string fileId)
{
    std::string folderPath = Stringtool::GetAsString("./", Constant::DataFolderName);
    _mkdir(folderPath.c_str());

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
