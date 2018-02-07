#include "stdafx.h"
#include "Margin.h"

#include "Render.h"

Margin::Margin(int top, int right, int bottom, int left) :
m_style{static_cast<double>(top), static_cast<double>(right), static_cast<double>(bottom), static_cast<double>(left)},
m_unit{StyleUnit::pixel}
{
}

Margin::Margin(double top, double right, double bottom, double left) :
m_style{top, right, bottom, left},
m_unit{StyleUnit::percentage}
{
}

Margin::~Margin()
{
    delete[] m_style;
}

void Margin::assign(int vertical, int horizontal)
{
    m_style[static_cast<int>(StyleOrder::top)] = vertical;
    m_style[static_cast<int>(StyleOrder::bottom)] = vertical;
    m_style[static_cast<int>(StyleOrder::left)] = horizontal;
    m_style[static_cast<int>(StyleOrder::right)] = horizontal;
    m_unit = StyleUnit::pixel;
}

void Margin::assign(double vertical, double horizontal)
{
    m_style[static_cast<int>(StyleOrder::top)] = vertical;
    m_style[static_cast<int>(StyleOrder::bottom)] = vertical;
    m_style[static_cast<int>(StyleOrder::left)] = horizontal;
    m_style[static_cast<int>(StyleOrder::right)] = horizontal;
    m_unit = StyleUnit::percentage;
}

void Margin::assign(int top, int right, int bottom, int left)
{
    m_style[static_cast<int>(StyleOrder::top)] = top;
    m_style[static_cast<int>(StyleOrder::right)] = right;
    m_style[static_cast<int>(StyleOrder::bottom)] = bottom;
    m_style[static_cast<int>(StyleOrder::left)] = left;
    m_unit = StyleUnit::pixel;
}

void Margin::assign(double top, double right, double bottom, double left)
{
    m_style[static_cast<int>(StyleOrder::top)] = top;
    m_style[static_cast<int>(StyleOrder::right)] = right;
    m_style[static_cast<int>(StyleOrder::bottom)] = bottom;
    m_style[static_cast<int>(StyleOrder::left)] = left;
    m_unit = StyleUnit::percentage;
}

// FIXME: ここメタプログラミング的な解決方法ないか
int Margin::top()
{
    return getValue(StyleOrder::top);
}
int Margin::right()
{
    return getValue(StyleOrder::right);
}
int Margin::bottom()
{
    return getValue(StyleOrder::bottom);
}
int Margin::left()
{
    return getValue(StyleOrder::left);
}

int Margin::getValue(StyleOrder order)
{
    // ピクセル指定の場合

    if (m_unit == StyleUnit::pixel) {
        return m_style[static_cast<int>(order)];
    }

    // パーセンテージ指定の場合

    if (order == StyleOrder::left || order == StyleOrder::right) {
        int clientWidth;
        std::tie(clientWidth, std::ignore) = Render::GetClientSize();

        return m_style[static_cast<int>(order)] * clientWidth;
    }
    
    int clientHeight;
    std::tie(std::ignore, clientHeight) = Render::GetClientSize();

    return m_style[static_cast<int>(order)] * clientHeight;
}


