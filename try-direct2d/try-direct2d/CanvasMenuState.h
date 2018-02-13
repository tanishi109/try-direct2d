#pragma once

#include "SceneState.h"
#include "ScrollableList.h"

class CanvasMenuState : public SceneState
{
public:
    CanvasMenuState();
    ~CanvasMenuState();
    void enter(Scene& scene);
    void update(Scene* scene);
private:
    void saveTileMap();
    static std::function<void(int)> m_onSelect;
    static ScrollableList& m_list;
};

