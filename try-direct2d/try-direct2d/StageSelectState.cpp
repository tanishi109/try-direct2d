#include "stdafx.h"

#include "StageSelectState.h"
#include "Render.h"
#include "Input.h"
#include "CanvasState.h"
#include "TileMapRecord.h"
#include "Stringtool.h"
#include "ScrollableList.h"

#include "Resource.h"

StageSelectState::StageSelectState()
{
}


StageSelectState::~StageSelectState()
{
}

void StageSelectState::enter()
{
    ScrollableList* list = new ScrollableList();
    list->m_marginPx[0] = 8;
    list->m_marginPx[1] = 8;
    list->m_marginPx[2] = 8;
    list->m_marginPx[3] = 8;
    m_gameObjects.push_back(list);
}

void StageSelectState::update(Scene* scene)
{
    Render::DrawText(30, 30, 200, 30, L"Press Enter to create new stage");

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
    std::string folderPath = Stringtool::GetAsString("./", DATA_FOLDER_NAME);

    std::string fileName;
    for (auto & p : std::experimental::filesystem::directory_iterator(folderPath)) {
        fileName = Stringtool::GetAsString(p.path().filename());
    }

    // FIXME: 今は最後のファイル名をfilePathに指定しているが、後で開くファイルを選択できるようにする
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

    // 読み込んだrecordからWorldのm_tilesを復元する
    CanvasState::m_world->restore(tileMapRecord);
}
