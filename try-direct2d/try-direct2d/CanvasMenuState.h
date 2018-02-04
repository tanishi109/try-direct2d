#pragma once

#include "SceneState.h"

class CanvasMenuState : public SceneState
{
public:
    CanvasMenuState();
    ~CanvasMenuState();
    void enter();
    void update(Scene* scene);
private:
    int m_textPosList[4][2];
    std::wstring m_textList[4];
    void saveTileMap();
};

