#pragma once

#include "SceneState.h"

class MenuState : public SceneState
{
public:
    MenuState();
    ~MenuState();
    virtual void enter();
    virtual SceneState* update();
    virtual void onMouseMove();
private:
    int m_textPosList[3][2];
    std::wstring m_textList[3];
};

