#pragma once

#include "SceneState.h"

class CanvasMenuState : public SceneState
{
public:
    CanvasMenuState();
    ~CanvasMenuState();
    virtual void enter();
    virtual SceneState* update(); // FIXME: オーバーライドする側の定義でvirtual不要なのでは
    void saveCanvas();
private:
    int m_textPosList[4][2];
    std::wstring m_textList[4];
};

