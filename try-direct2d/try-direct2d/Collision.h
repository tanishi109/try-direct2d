#pragma once
class Collision
{
public:
    Collision();
    ~Collision();
    // FIXME: Circle,Rect�Ȃǂ̍\���̂�n���悤�ɂ��āA
    // FIXME: template��CheckCollision���`���ē��������𕪂���Ƃ��悳��������
    static bool CheckCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2); 
};

