#pragma once
#include "SceneState.h"
#include "ScrollableList.h"

class GameMenuState : public SceneState
{
public:
    GameMenuState();
    ~GameMenuState();
    void enter(Scene& scene);
    void update(Scene* scene);
private:
    static std::function<void(int)> m_onSelect;
    static ScrollableList& m_list;
};
