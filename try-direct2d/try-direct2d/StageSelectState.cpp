#include "stdafx.h"

#include "StageSelectState.h"
#include "Render.h"
#include "Input.h"
#include "CanvasState.h"

#include "Resource.h"

StageSelectState::StageSelectState()
{
}


StageSelectState::~StageSelectState()
{
}

void StageSelectState::enter()
{
    log("Enter stage select state\n");
}

SceneState* StageSelectState::update()
{
    Render::DrawText(30, 30, 200, 30, L"Press Enter to create new stage");

    if (Input::GetKey(VK_RETURN)) {
        return new CanvasState();
    }

    bool is0KeyDowned = Input::GetKey(0x30);

    if (is0KeyDowned) {
        log("load here\n");
        loadStage();
    }

    return NULL;
}

void StageSelectState::loadStage()
{
    std::ostringstream oss;
    oss << "./" << DATA_FOLDER_NAME << "/test.dat";
    std::ifstream ifs(oss.str().c_str(), std::ios::in | std::ios::binary);

    if (!ifs)
    {
        log(":err, file open\n");
        return;
    }

    World readWorld;

    ifs.read((char *)&readWorld, sizeof(World));
    CanvasState::m_world = &readWorld;
}
