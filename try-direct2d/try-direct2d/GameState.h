#pragma once

#include "SceneState.h"
#include "Player.h"

class GameState : public SceneState
{
public:
    GameState();
    ~GameState();
    virtual void enter();
    virtual SceneState* update();
    virtual void onMouseMove();
private:
    static int m_screenPos[2]; // componentパターンとかでCanvasStateと共通化できないかな
    Player* m_player;
    bool m_isFocus;

    void scroll();
    bool checkCollision();
};

