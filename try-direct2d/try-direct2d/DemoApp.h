#pragma once

#include "Scene.h"
#include "Input.h"

class DemoApp
{
public:
    DemoApp();
    ~DemoApp();
    DemoApp(const DemoApp&) = delete;
    DemoApp& operator=(const DemoApp&) = delete;

    // Register the window class and call methods for instantiating drawing resources
    HRESULT Initialize();

    // Process and dispatch messages
    void RunMessageLoop();
private:
    // Initialize device-independent resources.
    HRESULT CreateDeviceIndependentResources();

    // Release device-dependent resource.
    void DiscardDeviceResources();

    void EnterScene();
    void UpdateScene();

    // Resize the render target.
    void OnResize(
        UINT width,
        UINT height
    );

    // The windows procedure.
    static LRESULT CALLBACK WndProc(
        HWND hWnd,
        UINT message,
        WPARAM wParam,
        LPARAM lParam
    );

    Scene* m_scene;
};

