#include "stdafx.h"
#include "Input.h"

bool Input::m_mouseDownL = false;

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