#include "stdafx.h"
#include "ScrollableList.h"

#include "Render.h"
#include "Input.h"

int INITIAL_INDEX = -1;

ScrollableList::ScrollableList(std::function<void(int)>& onSelect, std::initializer_list<std::string> contents) :
m_marginPx{*new Margin(0, 0, 0, 0)},
m_marginRate{*new Margin(0, 0, 0, 0)},
m_textMargin{*new Margin(0, 0, 8, 0)},
m_contents(contents),
m_pointedIndex(INITIAL_INDEX),
m_onSelect(onSelect)
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
        // TODO: 右のtextMarginは反映してない
        Render::DrawString(x, y, textWidth, textHeight, m_contents[i]);
        offsetY += m_textMargin.top() + m_textMargin.bottom();

        if (m_pointedIndex == i) {
            Render::DrawRect(x, y, textWidth, textHeight, BrushType_pink);
        }
    }

    // FIXME: inputはrender()じゃなくてupdate()的な関数で処理したい
    if (Input::GetKeyDown(VK_RETURN)) {
        m_onSelect(m_pointedIndex);
    }
    if (Input::GetKeyPerFrame(static_cast<int>(VK_UP))) {
        incrementPointer(-1);
    }
    if (Input::GetKeyPerFrame(static_cast<int>(VK_DOWN))) {
        incrementPointer(1);
    }
}

void ScrollableList::incrementPointer(int n)
{
    int size = static_cast<int>(m_contents.size());

    if (m_pointedIndex + n == INITIAL_INDEX - 1) {
        // pointedIndexが-1のときに-1進めたら
        // 一番後ろを指す
        m_pointedIndex = size - 1;
        return;
    }

    m_pointedIndex = (m_pointedIndex + n + size) % size; // マイナス方向にループさせるためsizeを一回足している
}
