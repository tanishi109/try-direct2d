#include "stdafx.h"
#include "Input.h"

bool Input::m_mouseDownL = false;
int Input::m_mousePos[2] = {0, 0};

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

int Input::GetMousePosX()
{
    return m_mousePos[0];
}

int Input::GetMousePosY()
{
    return m_mousePos[1];
}