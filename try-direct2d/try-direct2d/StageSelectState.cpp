#include "stdafx.h"

#include "StageSelectState.h"
#include "Render.h"
#include "Input.h"
#include "CanvasState.h"
#include "TileMapRecord.h"
#include "Stringtool.h"

#include "Constant.h"

StageSelectState::StageSelectState()
{
}


StageSelectState::~StageSelectState()
{
}

void StageSelectState::enter(Scene& scene)
{
    loadSaveFiles();
    m_list.m_marginRate.assign(0.0, 0.5, 0.0, 0.0);
    m_list.m_marginPx.assign(8, 8);
    m_gameObjects.push_back(&m_list);
}

void StageSelectState::update(Scene* scene)
{
    //if (Input::GetKey(VK_RETURN)) {
    //    scene->push(new CanvasState());
    //    return;
    //}

    bool is0KeyDowned = Input::GetKey(0x30);

    if (is0KeyDowned) {
        loadTileMap();
    }

    if (Input::GetKey(VK_UP)) {
        m_list.incrementPointer(-1);
    }
    if (Input::GetKey(VK_DOWN)) {
        m_list.incrementPointer(1);
    }
}

void StageSelectState::loadSaveFiles()
{
    std::string folderPath = Stringtool::GetAsString("./", Constant::DataFolderName);
    for (auto & p : std::experimental::filesystem::directory_iterator(folderPath)) {
        std::string fileName = Stringtool::GetAsString(p.path().filename());
        m_list.m_contents.push_back(fileName);
    }
}

void StageSelectState::loadTileMap()
{
    std::string folderPath = Stringtool::GetAsString("./", Constant::DataFolderName);

    std::string fileName;
    for (auto & p : std::experimental::filesystem::directory_iterator(folderPath)) {
        fileName = Stringtool::GetAsString(p.path().filename());
    }

    // FIXME: ���͍Ō�̃t�@�C������filePath�Ɏw�肵�Ă��邪�A��ŊJ���t�@�C����I���ł���悤�ɂ���
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

    // �ǂݍ���record����World��m_tiles�𕜌�����
    CanvasState::m_world->restore(tileMapRecord);
}

std::function<void(int)> StageSelectState::m_onSelect = [](int index){
    Debug::log("called!");
};

ScrollableList& StageSelectState::m_list = *new ScrollableList(
StageSelectState::m_onSelect,
{
    "create new stage"
});

