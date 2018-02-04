#pragma once

#include "GameObject.h"

class ScrollableList : public GameObject
{
public:
    ScrollableList();
    ~ScrollableList();
    void render(Screen* screen);
    // rateとpxの合計値で枠の大きさが決まる
    // 順番は時計回り(top, right, bottom, left)
    int m_marginPx[4];
private:
};

