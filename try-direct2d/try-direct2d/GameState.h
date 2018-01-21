#pragma once

#include "SceneState.h"
#include "Player.h"
#include "Terrain.h"

class GameState : public SceneState
{
public:
    GameState();
    ~GameState();
    virtual void enter();
    virtual SceneState* update();
    virtual void onMouseMove();
private:
    static int m_screenPos[2]; // component�p�^�[���Ƃ���CanvasState�Ƌ��ʉ��ł��Ȃ�����
    Player* m_player;
    bool m_isFocus;

    void scroll();
    Terrain* checkCollision();
    void initPosition();
    void setCursorOnPlayer();
};

