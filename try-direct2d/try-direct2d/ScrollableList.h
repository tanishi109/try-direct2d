#pragma once

#include "GameObject.h"
#include "Margin.h"

class ScrollableList : public GameObject
{
public:
    explicit ScrollableList(std::initializer_list<std::string> contents);
    ~ScrollableList();
    void render(Screen* screen);

    std::vector<std::string> m_contents;
    // rate��px�̍��v�l�Řg�̑傫�������܂�
    Margin& m_marginPx;
    Margin& m_marginRate;
    Margin& m_textMargin;
private:
};

