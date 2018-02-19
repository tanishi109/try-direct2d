#include "stdafx.h"

#include "StageSelectState.h"
#include "Render.h"
#include "Input.h"
#include "CanvasState.h"
#include "CanvasMenuState.h"
#include "TileMapRecord.h"
#include "Stringtool.h"

#include "Constant.h"

std::map<std::string, SaveFile> StageSelectState::m_saveFiles;

StageSelectState::StageSelectState()
{
    m_list.m_marginRate.assign(0.0, 0.5, 0.0, 0.0);
    m_list.m_marginPx.assign(8, 8);
    m_gameObjects.push_back(&m_list);
}


StageSelectState::~StageSelectState()
{
}

void StageSelectState::enter(Scene& scene)
{
    loadSaveFiles();

    m_onSelect = [&scene, this](int index){
        // not selected
        if (index == -1) {
            return;
        }
        // create new stage
        if (index == 0) {
            CanvasMenuState::m_fileId = "";
            CanvasState::m_world = new World();
            scene.push(new CanvasState());
            return;
        }
        // something selected
        loadTileMap(index);
        scene.push(new CanvasState());
    };
}

void StageSelectState::update(Scene* scene)
{
}

void StageSelectState::loadSaveFiles()
{
    std::string folderPath = Stringtool::GetAsString("./", Constant::DataFolderName);
    for (auto & p : std::experimental::filesystem::directory_iterator(folderPath)) {
        std::string fileName = Stringtool::GetAsString(p.path().filename());
        if (m_saveFiles.count(fileName) == 0) {
            m_saveFiles[fileName] = *new SaveFile{ fileName }; // FIXME: .datを含んでいる
            m_list.m_contents.push_back(fileName);
        }
    }

}

void StageSelectState::loadTileMap(int index)
{
    std::string folderPath = Stringtool::GetAsString("./", Constant::DataFolderName);
    std::string fileName = m_list.m_contents[index];
    std::string filePath = Stringtool::GetAsString(folderPath, "/", fileName);
    std::ifstream ifs(filePath.c_str(), std::ios::in | std::ios::binary);

    if (!ifs)
    {
        Debug::log(":err, file open");
        return;
    }

    TileMapRecord<World::WIDTH, World::HEIGHT> tileMapRecord;

    ifs.read(reinterpret_cast<char *>(&tileMapRecord), sizeof(tileMapRecord));
    ifs.close();

    // 読み込んだrecordからWorldのm_tilesを復元する
    CanvasState::m_world->restore(tileMapRecord);

    // fileIdをCanvasMenuStateに読み込んでおく
    CanvasMenuState::m_fileId = tileMapRecord.id;
}

std::function<void(int)> StageSelectState::m_onSelect = [](int index){
    // キャプチャが必要なのでsceneのenterで定義する
};

ScrollableList& StageSelectState::m_list = *new ScrollableList(
StageSelectState::m_onSelect,
{
    "create new stage"
});

