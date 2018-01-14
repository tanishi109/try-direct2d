#pragma once

class DemoApp;

class Input
{
friend class DemoApp;
public:
    Input();
    ~Input();

    static bool GetMouseDownL();
    static int GetMousePosX();
    static int GetMousePosY();

private:
    static bool m_mouseDownL;
    static int m_mousePos[2];
};

