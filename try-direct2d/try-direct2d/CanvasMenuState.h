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
    static std::string m_fileId;
private:
    void saveTo(std::string fileId);
    std::string getFileId();

    static std::function<void(int)> m_onSelect;
    static ScrollableList& m_list;
};

