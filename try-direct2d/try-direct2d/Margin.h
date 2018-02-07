#pragma once

enum class StyleUnit {
    pixel,
    percentage
};

enum class StyleOrder {
    top = 0,
    right = 1,
    bottom = 2,
    left = 3
};

class Margin
{
public:
    // 1 = 1px
    Margin(int top, int right, int bottom, int left);
    // 1 = âÊñ ÉTÉCÉYÇ…ëŒÇ∑ÇÈ100%
    Margin(double top, double right, double bottom, double left);
    ~Margin();
    void assign(int vertical, int horizontal);
    void assign(double vertical, double horizontal);
    void assign(int top, int right, int bottom, int left);
    void assign(double top, double right, double bottom, double left);
    int top();
    int right();
    int bottom();
    int left();
private:
    int getValue(StyleOrder order);
    double m_style[4];
    StyleUnit m_unit;
};
