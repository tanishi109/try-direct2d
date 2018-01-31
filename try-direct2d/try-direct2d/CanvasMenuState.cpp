#include "stdafx.h"

#include "SceneState.h"
#include "CanvasMenuState.h"
#include "CanvasState.h"
#include "GameState.h"
#include "Render.h"
#include "Input.h"

#include "Resource.h"

CanvasMenuState::CanvasMenuState() :
m_textPosList{
    {0, 0},
    {30, 100},
    {30, 200},
    {30, 300}
},
m_textList {
    L"Menu",
    L"push 1. Canvas Mode",
    L"push 2. Game Mode",
    L"push 0. Save this Canvas"
}
{
}


CanvasMenuState::~CanvasMenuState()
{
}

void CanvasMenuState::enter()
{
    Render::TakeScreenShot();
}

SceneState* CanvasMenuState::update()
{
    Render::Clear();

    Render::DrawScreenShot();

    static const int width = 400;
    for (auto &pos : m_textPosList) {
        int index = &pos - &m_textPosList[0];
        int x = pos[0];
        int y = pos[1];
        std::wstring text = m_textList[index];

        Render::DrawText(x, y, width, 40, text);
    }

    bool is1KeyDowned = Input::GetKey(0x31);
    bool is2KeyDowned = Input::GetKey(0x32);
    bool is0KeyDowned = Input::GetKey(0x30);

    if (is1KeyDowned) {
        return new CanvasState();
    }
    if (is2KeyDowned) {
        return new GameState();
    }
    if (is0KeyDowned) {
        saveCanvas();
    }

    return NULL;
}

void CanvasMenuState::saveCanvas()
{
    std::ostringstream oss;
    oss << "./" << DATA_FOLDER_NAME;
    _mkdir(oss.str().c_str());

    oss.clear();
    oss.str("");

    oss << "./" << DATA_FOLDER_NAME << "/test.dat";
    std::ofstream ofs(oss.str().c_str(), std::ios::out | std::ios::trunc | std::ios::binary);

    if (!ofs)
    {
        log(":err, file open\n");
        return;
    }

    ofs.write(reinterpret_cast<char *>(CanvasState::m_world), sizeof(World));

    log(":ok, file wrote\n");
}
