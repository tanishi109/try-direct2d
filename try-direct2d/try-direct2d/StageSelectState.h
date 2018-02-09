#pragma once

#include "SceneState.h"
#include "ScrollableList.h"

class StageSelectState : public SceneState
{
public:
    StageSelectState();
    ~StageSelectState();
    void enter(Scene& scene);
    void update(Scene* scene);
private:
    void loadSaveFiles();
    void loadTileMap();
    static std::function<void(int)> m_onSelect;
    static ScrollableList& m_list;
};

