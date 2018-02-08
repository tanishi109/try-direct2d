#include "stdafx.h"

#include "StageSelectState.h"
#include "Render.h"
#include "Input.h"
#include "CanvasState.h"
#include "TileMapRecord.h"
#include "Stringtool.h"
#include "ScrollableList.h"

#include "Constant.h"

StageSelectState::StageSelectState()
{
}


StageSelectState::~StageSelectState()
{
}

void StageSelectState::enter()
{
    ScrollableList* list = new ScrollableList({
        "ham",
        "spam",
        "create new stage"
    });
    list->m_marginRate.assign(0.0, 0.5, 0.0, 0.0);
    list->m_marginPx.assign(8, 8);
    m_gameObjects.push_back(list);
}

void StageSelectState::update(Scene* scene)
{
    if (Input::GetKey(VK_RETURN)) {
        scene->push(new CanvasState());
        return;
    }

    bool is0KeyDowned = Input::GetKey(0x30);

    if (is0KeyDowned) {
        loadTileMap();
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
        log(":err, file open\n");
        return;
    }

    TileMapRecord<World::WIDTH, World::HEIGHT> tileMapRecord;

    ifs.read(reinterpret_cast<char *>(&tileMapRecord), sizeof(tileMapRecord));
    ifs.close();

    // �ǂݍ���record����World��m_tiles�𕜌�����
    CanvasState::m_world->restore(tileMapRecord);
}
