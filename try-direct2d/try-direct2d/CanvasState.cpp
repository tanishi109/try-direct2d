#include "stdafx.h"
#include "CanvasState.h"
#include "Input.h"
#include "Render.h"

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
    //OutputDebugStringA(buf);

    Render::DrawRect(
        50.0f,
        50.0f,
        100.0f,
        100.0f
    );

    Render::DrawRect(
        150.0f,
        150.0f,
        50.0f,
        50.0f
    );
}
