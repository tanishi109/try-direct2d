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
    static int GetMouseDeltaX();
    static int GetMouseDeltaY();
    static bool GetKey(int keyCode);

private:
    static bool m_mouseDownL;
    static int m_mousePos[2];
    static int m_mouseDelta[2];
    static int m_prevMousePos[2];
    static int m_keyDown;
};

