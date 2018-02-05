#include "stdafx.h"
#include "ScrollableList.h"

#include "Render.h"

ScrollableList::ScrollableList() :
m_marginPx{0, 0, 0, 0},
m_marginRate{0, 0, 0, 0}
{
}

ScrollableList::~ScrollableList()
{
}

void ScrollableList::render(Screen* screen)
{
    long windowWidth;
    long windowHeight;
    std::tie(windowWidth, windowHeight) = Render::GetClientSize();

    int leftTopX = m_x + m_marginPx[0] + windowWidth * m_marginRate[0];
    int leftTopY = m_y + m_marginPx[3] + windowHeight * m_marginRate[3];
    int rightBottomX = windowWidth - m_marginPx[1] - windowWidth * m_marginRate[1] - leftTopX;
    int rightBottomY = windowHeight - m_marginPx[2] - windowWidth * m_marginRate[2] - leftTopY;

    Render::DrawRect(
        leftTopX,
        leftTopY,
        rightBottomX,
        rightBottomY,
        BrushType_black
    );
}
