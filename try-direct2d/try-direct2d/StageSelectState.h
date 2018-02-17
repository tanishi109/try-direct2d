#pragma once

#include "SceneState.h"
#include "ScrollableList.h"

struct SaveFile {
    std::string id;
};

class StageSelectState : public SceneState
{
public:
    StageSelectState();
    ~StageSelectState();
    void enter(Scene& scene);
    void update(Scene* scene);
private:
    void loadSaveFiles();
    void loadTileMap(int index);
    static std::function<void(int)> m_onSelect;
    static ScrollableList& m_list;
    static std::map<std::string, SaveFile> m_saveFiles;
};

