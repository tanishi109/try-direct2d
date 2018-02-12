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
    // �L�[��������Ă���Ԃ�����
    static bool GetKey(int keyCode);
    // �L�[�������ꂽ�u�Ԃ̂�
    static bool GetKeyDown(int keyCode);
    // �L�[��������Ă����frame��(�����firstFrame, ��������repeatFrame�Ń`�F�b�N)
    static bool GetKeyPerFrame(int keyCode, int firstFrame = 10, int repeatFrame = 2);
    static void InitKeyDownFrameCount(int keyCode);

    // true�̎��J�[�\������\���ɂȂ�AmouseDelta�͍��W�̍��ł͂Ȃ��}�E�X�̈ړ��ʂ�ێ�����
    static bool m_captureCursorMode;
private:
    static bool m_mouseDownL;
    static bool m_mouseDownR;
    static int m_mousePos[2];
    static int m_mouseDelta[2];
    static int m_prevMousePos[2];
    static std::map<int, bool> m_isKeyDownFrame;
    static std::map<int, int> m_keyDownFrameCount;
    static int INIT_KEY_DOWN_FRAME_COUNT;
};

