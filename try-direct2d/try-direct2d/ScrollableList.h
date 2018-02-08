#pragma once

#include "GameObject.h"
#include "Margin.h"

class ScrollableList : public GameObject
{
public:
    explicit ScrollableList(std::initializer_list<std::string> contents);
    ~ScrollableList();
    void render(Screen* screen);
    // rateとpxの合計値で枠の大きさが決まる
    Margin& m_marginPx;
    Margin& m_marginRate;
    Margin& m_textMargin;
private:
    std::vector<std::string> m_contents;
};

