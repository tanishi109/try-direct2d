#pragma once
class Mathtool
{
public:
    Mathtool();
    ~Mathtool();
    static float degToRad(float degree);
    static float radToDeg(float radian);
    static float getDistance(float x1, float y1, float x2, float y2);
    static float getRadFromPos(float x1, float y1, float x2, float y2);
};

