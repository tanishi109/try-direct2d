#include "stdafx.h"
#include "ScrollableList.h"

#include "Render.h"

ScrollableList::ScrollableList() :
m_marginPx{0, 0, 0, 0}
{
}

ScrollableList::~ScrollableList()
{
}

void ScrollableList::render(Screen* screen)
{
    long width;
    long height;
    std::tie(width, height) = Render::GetClientSize();

    Render::DrawRect(
        m_x + m_marginPx[0],
        m_y + m_marginPx[1],
        width - m_marginPx[0] - m_marginPx[2],
        height - m_marginPx[1] - m_marginPx[2],
        BrushType_black
    );
}
