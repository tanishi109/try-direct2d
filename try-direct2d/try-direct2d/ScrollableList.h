#pragma once

#include "GameObject.h"

class ScrollableList : public GameObject
{
public:
    ScrollableList();
    ~ScrollableList();
    void render(Screen* screen);
    // rate‚Æpx‚Ì‡Œv’l‚Å˜g‚Ì‘å‚«‚³‚ªŒˆ‚Ü‚é
    // ‡”Ô‚ÍŒv‰ñ‚è(top, right, bottom, left)
    int m_marginPx[4];
private:
};

