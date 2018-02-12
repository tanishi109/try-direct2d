#include "stdafx.h"
#include "Input.h"

bool Input::m_mouseDownL = false;
bool Input::m_mouseDownR = false;
int Input::m_mousePos[2] = {0, 0};
int Input::m_mouseDelta[2] = {0, 0};
int Input::m_prevMousePos[2] = {0, 0};
bool Input::m_captureCursorMode = false;
std::map<int, bool> Input::m_isKeyDownFrame;
std::map<int, int> Input::m_keyDownFrameCount;
int Input::INIT_KEY_DOWN_FRAME_COUNT = -1;

Input::Input()
{
}


Input::~Input()
{
}

bool Input::GetMouseDownL()
{
    return m_mouseDownL;
}

bool Input::GetMouseDownR()
{
    return m_mouseDownR;
}

int Input::GetMousePosX()
{
    return m_mousePos[0];
}

int Input::GetMousePosY()
{
    return m_mousePos[1];
}

int Input::GetMouseDeltaX()
{
    return m_mouseDelta[0];
}

int Input::GetMouseDeltaY()
{
    return m_mouseDelta[1];
}

bool Input::GetKey(int keyCode)
{
    // TODO: ここのチェックまとめられないかな
    if (Input::m_keyDownFrameCount.count(keyCode) == 0) {
        return false;
    }
    return m_keyDownFrameCount[keyCode] != INIT_KEY_DOWN_FRAME_COUNT;
}

bool Input::GetKeyDown(int keyCode)
{
    if (Input::m_keyDownFrameCount.count(keyCode) == 0) {
        return false;
    }
    return m_keyDownFrameCount[keyCode] == INIT_KEY_DOWN_FRAME_COUNT + 1;
}

bool Input::GetKeyPerFrame(int keyCode, int firstFrame, int repeatFrame)
{
    if (Input::m_keyDownFrameCount.count(keyCode) == 0) {
        return false;
    }

    // 初回はfirstFrame経過時
    if (m_keyDownFrameCount[keyCode] <= firstFrame) {
        return m_keyDownFrameCount[keyCode] % firstFrame == 0;
    }

    // 初回より後はrepeatFrame毎
    return m_keyDownFrameCount[keyCode] % repeatFrame == 0;
}

void Input::InitKeyDownFrameCount(int keyCode)
{
    m_keyDownFrameCount[keyCode] = INIT_KEY_DOWN_FRAME_COUNT;
}
