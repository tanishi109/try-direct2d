#pragma once
class Collision
{
public:
    Collision();
    ~Collision();
    // FIXME: Circle,Rectなどの構造体を渡すようにして、
    // FIXME: templateでCheckCollisionを定義して内部処理を分けるとかよさそうかも
    static bool CheckCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2); 
};

