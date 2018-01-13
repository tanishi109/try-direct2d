#include "stdafx.h"
#include "CanvasState.h"


CanvasState::CanvasState()
{
}


CanvasState::~CanvasState()
{
}

void CanvasState::onRender()
{
    char buf[256];
    sprintf_s(buf, "Render Canvas State! %d\n", 123);
    OutputDebugStringA(buf);
}
