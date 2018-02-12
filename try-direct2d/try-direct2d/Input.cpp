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
    return CompareWithFrameCount(keyCode, [](int count){
        return count != INIT_KEY_DOWN_FRAME_COUNT;
    });
}

bool Input::GetKeyDown(int keyCode)
{
    return CompareWithFrameCount(keyCode, [](int count){
        return count == INIT_KEY_DOWN_FRAME_COUNT + 1;
    });
}

bool Input::GetKeyPerFrame(int keyCode, int firstFrame, int repeatFrame)
{
    return CompareWithFrameCount(keyCode, [&firstFrame, &repeatFrame](int count){
        // èââÒÇÕfirstFrameåoâﬂéû
        if (count <= firstFrame) {
            return count % firstFrame == 0;
        }
        // èââÒÇÊÇËå„ÇÕrepeatFrameñà
        return count % repeatFrame == 0;
    });
}

void Input::InitKeyDownFrameCount(int keyCode)
{
    m_keyDownFrameCount[keyCode] = INIT_KEY_DOWN_FRAME_COUNT;
}

bool Input::CompareWithFrameCount(int keyCode, std::function<bool(int)> fn)
{
    // éÊìæÇ∑ÇÈframeCountÇ™Ç»Ç¢
    if (m_keyDownFrameCount.count(keyCode) == 0) {
        return false;
    }

    return fn(m_keyDownFrameCount[keyCode]);
}
