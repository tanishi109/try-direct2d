#include "stdafx.h"
#include "Player.h"
#include "Render.h"
#include "Mathtool.h"
#include "Input.h"

Player::Player(int x, int y, int w, int h, const int childrenCount) :
m_x(x),
m_y(y),
m_width(w),
m_height(h),
m_degree(45),
m_horizontalPinMargin(10),
m_childrenCount(childrenCount)
{
    m_children[m_childrenCount];
    for (int i = 0; i < m_childrenCount; i++) {
        m_children[i] = new Player(x, y, w, h, 0);
    }
}


Player::~Player()
{
    delete[] m_children;
}

void Player::update()
{
    // set player rotation
    int mouseX = Input::GetMousePosX();
    int mouseY = Input::GetMousePosY();
    int mainPinX;
    int mainPinY;
    std::tie(mainPinX, mainPinY) = getMainPinPos();
    int dx = mouseX - mainPinX;
    int dy = mouseY - mainPinY;
    double radian = std::atan2(dy, dx);
    m_degree = Mathtool::radToDeg(radian);

    // set player position
    float subPinX;
    float subPinY;
    std::tie(subPinX, subPinY) = getSubPinPosRotated();
    float w = subPinX - m_x;
    float h = subPinY - m_y;
    m_x = mouseX - w;
    m_y = mouseY - h;

    // children‚Ìupdate
    for (int i = 0; i < m_childrenCount; i++) {
        Player* parent = this;
        if (i > 0) {
            parent = m_children[i - 1];
        }
        m_children[i]->updateForChild(parent);
    }
}

void Player::updateForChild(Player* parent)
{
    int parentX;
    int parentY;
    std::tie(parentX, parentY) = parent->getMainPinPos();
    int childX;
    int childY;
    std::tie(childX, childY) = getMainPinPos();
    int dx = parentX - childX;
    int dy = parentY - childY;
    double radian = std::atan2(dy, dx);
    m_degree = Mathtool::radToDeg(radian);

    float childSubX;
    float childSubY;
    std::tie(childSubX, childSubY) = getSubPinPosRotated();
    float w = childSubX - m_x;
    float h = childSubY - m_y;
    m_x = parent->m_x - w + m_horizontalPinMargin;
    m_y = parent->m_y - h + m_height / 2;
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

    // children‚Ìrender
    for (int i = 0; i < m_childrenCount; i++) {
        m_children[i]->render();
    }
}

std::tuple<int, int> Player::getMainPinPos()
{
    return {m_x + m_horizontalPinMargin, m_y + m_height / 2};
}

std::tuple<float, float> Player::getSubPinPosRotated()
{
    float radian = Mathtool::degToRad(m_degree);

    int mainPinX;
    int mainPinY;
    std::tie(mainPinX, mainPinY) = getMainPinPos();

    float rx = mainPinX + std::cos(radian) * (m_width - m_horizontalPinMargin * 2);
    float ry = mainPinY + std::sin(radian) * (m_width - m_horizontalPinMargin * 2);

    return {rx, ry};
}

void Player::setMainPinPos(int x, int y)
{
    m_x = x - m_horizontalPinMargin;
    m_y = y - m_height / 2;
}

// subPin‚ª(x, y)‚É—ˆ‚é‚æ‚¤‚È(m_x, m_y)‚ðƒZƒbƒg‚·‚é
void Player::setSubPinPos(int x, int y)
{
    float radian = Mathtool::degToRad(m_degree + 180); // ‹t‚©‚çŒ©‚½Žž‚ÌŠp“x‚É‚·‚é
    int pinDistance = m_width - m_horizontalPinMargin * 2;

    float mainPinX = x + std::cos(radian) * pinDistance;
    float mainPinY = y + std::sin(radian) * pinDistance;
    setMainPinPos(mainPinX, mainPinY);
}
