#pragma once

#include "GameObject.h"

class ScrollableList : public GameObject
{
public:
    ScrollableList();
    ~ScrollableList();
    void render(Screen* screen);
    // rate��px�̍��v�l�Řg�̑傫�������܂�
    // ���Ԃ͎��v���(top, right, bottom, left)
    int m_marginPx[4];
private:
};

