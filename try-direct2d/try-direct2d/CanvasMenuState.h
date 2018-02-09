#pragma once

#include "SceneState.h"

class CanvasMenuState : public SceneState
{
public:
    CanvasMenuState();
    ~CanvasMenuState();
    void enter(Scene& scene);
    void update(Scene* scene);
private:
    int m_textPosList[4][2];
    std::string m_textList[4];
    void saveTileMap();
};

