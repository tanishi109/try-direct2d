#pragma once
class Player
{
public:
    Player(int x, int y, int w, int h);
    ~Player();
    void render();
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    float m_degree;
};

