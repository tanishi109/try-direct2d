#pragma once

#include "SceneState.h"

class CanvasMenuState : public SceneState
{
public:
    CanvasMenuState();
    ~CanvasMenuState();
    virtual void enter();
    virtual SceneState* update();
    virtual void onMouseMove();
private:
    int m_textPosList[3][2];
    std::wstring m_textList[3];
};

