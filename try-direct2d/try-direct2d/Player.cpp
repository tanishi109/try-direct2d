#include "stdafx.h"
#include "Player.h"
#include "Render.h"

Player::Player(int x, int y, int w, int h) :
m_x(x),
m_y(y),
m_width(w),
m_height(h),
m_degree(45),
m_verticalPinMargin(10)
{
}


Player::~Player()
{
}

void Player::render()
{
    int mainPinX;
    int mainPinY;
    std::tie(mainPinX, mainPinY) = getMainPinPos();
    Render::SetRotation(m_degree, mainPinX, mainPinY);
  
    Render::DrawRect(m_x, m_y, m_width, m_height, 2);

    Render::SetRotation(0, 0, 0);
}

std::tuple<int, int> Player::getMainPinPos()
{
    return {m_x + m_verticalPinMargin, m_y + m_height / 2};
}