#include "stdafx.h"
#include "Player.h"
#include "Render.h"
#include "Mathtool.h"

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
    // FIXME: []‚Å•ªŠ„‘ã“ü‚Å‚«‚é‚Í‚¸‚¾‚¯‚Ç
    std::tie(mainPinX, mainPinY) = getMainPinPos();
    Render::SetRotation(m_degree, mainPinX, mainPinY);
  
    Render::DrawRect(m_x, m_y, m_width, m_height, 2);

    Render::SetRotation(0, 0, 0);
}

std::tuple<int, int> Player::getMainPinPos()
{
    return {m_x + m_verticalPinMargin, m_y + m_height / 2};
}

std::tuple<float, float> Player::getSubPinPosRotated() {
    float radian = Mathtool::degToRad(m_degree);

    int mainPinX;
    int mainPinY;
    std::tie(mainPinX, mainPinY) = getMainPinPos();

    float rx = mainPinX + std::cos(radian) * (m_width - m_verticalPinMargin * 2);
    float ry = mainPinY + std::sin(radian) * (m_width - m_verticalPinMargin * 2);

    return {rx, ry};
}
