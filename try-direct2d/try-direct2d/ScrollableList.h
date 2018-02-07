#pragma once

#include "GameObject.h"
#include "Margin.h"

class ScrollableList : public GameObject
{
public:
    ScrollableList(std::initializer_list<std::string> contents);
    ~ScrollableList();
    void render(Screen* screen);
    // rate‚Æpx‚Ì‡Œv’l‚Å˜g‚Ì‘å‚«‚³‚ªŒˆ‚Ü‚é
    Margin& m_marginPx;
    Margin& m_marginRate;
    Margin& m_textMargin;
private:
    std::vector<std::string> m_contents;
};

