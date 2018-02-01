#pragma once

#include "SceneState.h"

class CanvasMenuState : public SceneState
{
public:
    CanvasMenuState();
    ~CanvasMenuState();
    virtual void enter();
    virtual SceneState* update(); // FIXME: �I�[�o�[���C�h���鑤�̒�`��virtual�s�v�Ȃ̂ł�
private:
    int m_textPosList[4][2];
    std::wstring m_textList[4];
    void saveCanvas();
};

