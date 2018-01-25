#pragma once

class DemoApp;

class Input
{
friend class DemoApp;
public:
    Input();
    ~Input();

    static bool GetMouseDownL();
    static bool GetMouseDownR();
    static int GetMousePosX();
    static int GetMousePosY();
    static int GetMouseDeltaX();
    static int GetMouseDeltaY();
    static bool GetKey(int keyCode);

    // true�̎��J�[�\������\���ɂȂ�AmouseDelta�͍��W�̍��ł͂Ȃ��}�E�X�̈ړ��ʂ�ێ�����
    static bool m_captureCursorMode;

private:
    static bool m_mouseDownL;
    static bool m_mouseDownR;
    static int m_mousePos[2];
    static int m_mouseDelta[2];
    static int m_prevMousePos[2];
    static int m_keyDown;
};

