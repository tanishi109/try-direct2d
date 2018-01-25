#include "stdafx.h"
#include "Player.h"
#include "Render.h"
#include "Mathtool.h"
#include "Input.h"

Player::Player(int x, int y, int w, int h) :
m_width(w),
m_height(h),
m_degree(45),
m_horizontalPinMargin(10),
m_parent(NULL),
m_child(NULL),
m_movable(true)
{
    m_x = x;
    m_y = y;
}


Player::~Player()
{
    Player* child = m_child;
    while(child != NULL) {
        Player* nextChild = child->m_child;

        delete m_child;

        child = nextChild;
    }
}

void Player::update(Screen* screen)
{
    if (m_movable) {
        move(screen);
    }
}

void Player::move(Screen* screen)
{
    if (m_parent == NULL) {
        // 親nodeがいない場合はマウスを基準に移動
        int mouseX = Input::GetMousePosX();
        int mouseY = Input::GetMousePosY();
        int mainPinX;
        int mainPinY;
        std::tie(mainPinX, mainPinY) = getMainPinPos();
        int dx = mouseX - mainPinX;
        int dy = mouseY - mainPinY;
        double radian = std::atan2(dy, dx);
        m_degree = Mathtool::radToDeg(radian);

        float subPinX;
        float subPinY;
        std::tie(subPinX, subPinY) = getSubPinPosRotated();
        float w = subPinX - m_x;
        float h = subPinY - m_y;
        m_x = mouseX - w;
        m_y = mouseY - h;
    } else {
        // 親nodeがいる場合は親の位置を基準に移動
        int parentX;
        int parentY;
        std::tie(parentX, parentY) = m_parent->getMainPinPos();
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
        // FIXME: ここの計算だけどうにかなれば親の有無で分けている処理をもっとまとめられそう
        m_x = m_parent->m_x - w + m_horizontalPinMargin;
        m_y = m_parent->m_y - h + m_height / 2;
    }

    // 子を再帰的に移動
    if (m_child != NULL) {
        m_child->move(screen);
    }
}

void Player::render(Screen* screen)
{
    int mainPinX;
    int mainPinY;
    // FIXME: []で分割代入できるはずだけど
    std::tie(mainPinX, mainPinY) = getMainPinPos();
    Render::SetRotation(m_degree, mainPinX, mainPinY);
  
    // プレイヤーの矩形
    Render::DrawRect(m_x, m_y, m_width, m_height, BrushType_black);
    // 当たり判定の円
    Render::DrawCircle(mainPinX, mainPinY, m_collisionRadius, BrushType_black);

    Render::SetRotation(0, 0, 0);

    // 子を再帰的に描画
    if (m_child != NULL) {
        m_child->render(screen);
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

// subPinが(x, y)に来るような(m_x, m_y)をセットする
void Player::setSubPinPos(int x, int y)
{
    float radian = Mathtool::degToRad(m_degree + 180); // 逆から見た時の角度にする
    int pinDistance = m_width - m_horizontalPinMargin * 2;

    float mainPinX = x + std::cos(radian) * pinDistance;
    float mainPinY = y + std::sin(radian) * pinDistance;
    setMainPinPos(mainPinX, mainPinY);
}

void Player::addChild()
{
    m_child = new Player(m_x, m_y, m_width, m_height);
    m_child->m_parent = this;
}
