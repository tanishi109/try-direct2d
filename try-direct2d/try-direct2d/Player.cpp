#include "stdafx.h"
#include "Player.h"
#include "Render.h"

Player::Player(int x, int y, int w, int h) :
m_x(x),
m_y(y),
m_width(w),
m_height(h),
m_degree(45)
{
}


Player::~Player()
{
}

void Player::render()
{
    Render::DrawRect(m_x, m_y, m_width, m_height, 2);
}
