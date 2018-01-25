#include "stdafx.h"
#include "Input.h"

bool Input::m_mouseDownL = false;
bool Input::m_mouseDownR = false;
int Input::m_mousePos[2] = {0, 0}; // ç≈èâNULLÇ™Ç¢Ç¢Ç©Ç‡?
int Input::m_mouseDelta[2] = {0, 0};
int Input::m_prevMousePos[2] = {NULL, NULL};
int Input::m_keyDown = NULL;
bool Input::m_captureCursorMode = false;

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
    return m_keyDown == keyCode;
}
