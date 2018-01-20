#pragma once
class Collision
{
public:
    Collision();
    ~Collision();
    // FIXME: Circle,Rect‚È‚Ç‚Ì\‘¢‘Ì‚ğ“n‚·‚æ‚¤‚É‚µ‚ÄA
    // FIXME: template‚ÅCheckCollision‚ğ’è‹`‚µ‚Ä“à•”ˆ—‚ğ•ª‚¯‚é‚Æ‚©‚æ‚³‚»‚¤‚©‚à
    static bool CheckCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2); 
};

