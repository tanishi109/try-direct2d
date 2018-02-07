#include "stdafx.h"
#include "ScrollableList.h"

#include "Render.h"

ScrollableList::ScrollableList(std::initializer_list<std::string> contents) :
m_marginPx{*new Margin(0, 0, 0, 0)},
m_marginRate{*new Margin(0, 0, 0, 0)},
m_textMargin{*new Margin(0, 0, 8, 0)},
m_contents(contents)
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

    int leftTopX = m_x + m_marginPx.left() + m_marginRate.left();
    int leftTopY = m_y + m_marginPx.top() + m_marginRate.top();
    int listWidth = windowWidth - m_marginPx.right() - m_marginRate.right() - leftTopX;
    int listHeight = windowHeight - m_marginPx.bottom() - m_marginRate.bottom() - leftTopY;

    Render::DrawRect(
        leftTopX,
        leftTopY,
        listWidth,
        listHeight,
        BrushType_black
    );

    int textWidth = listWidth;
    int textHeight = 30;
    int offsetY = m_textMargin.top();
    for (int i = 0; i < m_contents.size(); ++i) {
        int x = leftTopX + m_textMargin.left();
        int y = leftTopY + textHeight * i + offsetY;
        // TODO: ‰E‚ÌtextMargin‚Í”½‰f‚µ‚Ä‚È‚¢
        Render::DrawString(x, y, textWidth, textHeight, m_contents[i]);
        offsetY += m_textMargin.top() + m_textMargin.bottom();
    }
}
