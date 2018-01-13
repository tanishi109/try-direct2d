#include "stdafx.h"
#include "CanvasState.h"
#include "Input.h"

CanvasState::CanvasState()
{
}


CanvasState::~CanvasState()
{
}

void CanvasState::update()
{
    bool mouseState = Input::GetMouseDownL();

    char buf[256];
    sprintf_s(buf, "Render Canvas State! mouse is %d\n", mouseState);
    OutputDebugStringA(buf);
}
