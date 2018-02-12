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
    // キーが押されている間ずっと
    static bool GetKey(int keyCode);
    // キーが押された瞬間のみ
    static bool GetKeyDown(int keyCode);
    // キーが押されている間frame毎(初回はfirstFrame, 初回より後はrepeatFrameでチェック)
    static bool GetKeyPerFrame(int keyCode, int firstFrame = 10, int repeatFrame = 2);
    static void InitKeyDownFrameCount(int keyCode);

    // trueの時カーソルが非表示になり、mouseDeltaは座標の差ではなくマウスの移動量を保持する
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

