#include "stdafx.h"

// FIXME: 名前DemoAppじゃなくしたいな
#include "DemoApp.h"
#include "Input.h"
#include "Render.h"

template<class Interface>
inline void SafeRelease(
    Interface **ppInterfaceToRelease
)
{
    if (*ppInterfaceToRelease != nullptr)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = nullptr;
    }
}

#ifndef HINST_THISCOMPONENT
EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)
#endif

DemoApp::DemoApp():
m_scene(new Scene())
{
}

DemoApp::~DemoApp()
{
    // TODO Renderに移動
    SafeRelease(&Render::m_direct2dFactory);
    SafeRelease(&Render::m_renderTarget);
    SafeRelease(&Render::m_brush);
}

void DemoApp::RunMessageLoop()
{
    MSG msg;

    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

HRESULT DemoApp::Initialize()
{
    HRESULT hr;

    // Initialize device-indpendent resources, such
    // as the Direct2D factory.
    hr = Render::CreateDeviceIndependentResources();

    if (SUCCEEDED(hr))
    {
        // Register the window class.
        WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = DemoApp::WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = sizeof(LONG_PTR);
        wcex.hInstance = HINST_THISCOMPONENT;
        wcex.hbrBackground = nullptr;
        wcex.lpszMenuName = nullptr;
        wcex.hCursor = LoadCursor(nullptr, IDI_APPLICATION);
        wcex.lpszClassName = L"D2DDemoApp";

        RegisterClassEx(&wcex);


        // Because the CreateWindow function takes its size in pixels,
        // obtain the system DPI and use it to scale the window size.
        FLOAT dpiX, dpiY;

        // The factory returns the current system DPI. This is also the value it will use
        // to create its own windows.
        Render::m_direct2dFactory->GetDesktopDpi(&dpiX, &dpiY);


        // Create the window.
        Render::m_hwnd = CreateWindow(
            L"D2DDemoApp",
            L"Direct2D Demo App",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            static_cast<UINT>(ceil(640.f * dpiX / 96.f)),
            static_cast<UINT>(ceil(480.f * dpiY / 96.f)),
            nullptr,
            nullptr,
            HINST_THISCOMPONENT,
            this
        );
        hr = Render::m_hwnd ? S_OK : E_FAIL;
        if (SUCCEEDED(hr))
        {
            ShowWindow(Render::m_hwnd, SW_SHOWNORMAL);
            UpdateWindow(Render::m_hwnd);
        }
    }

    // SceneのEnter処理
    // FIXME: ここでほんとに大丈夫?
    EnterScene();

    return hr;
}

void DemoApp::DiscardDeviceResources()
{
    // TODO: Renderに移動
    SafeRelease(&Render::m_renderTarget);
    SafeRelease(&Render::m_brush);
}

LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        DemoApp *pDemoApp = static_cast<DemoApp*>(pcs->lpCreateParams);

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            PtrToUlong(pDemoApp)
        );

        result = 1;

        // ゲームループ用のタイマー
        SetTimer(hwnd, 1, 16.666, nullptr);
    }
    else
    {
        DemoApp *pDemoApp = reinterpret_cast<DemoApp *>(static_cast<LONG_PTR>(
            ::GetWindowLongPtrW(
                hwnd,
                GWLP_USERDATA
            )));

        bool wasHandled = false;

        if (pDemoApp)
        {
            switch (message)
            {
            case WM_SIZE:
            {
                UINT width = LOWORD(lParam);
                UINT height = HIWORD(lParam);
                pDemoApp->OnResize(width, height);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DISPLAYCHANGE:
            {
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_PAINT:
            {
                PAINTSTRUCT ps;
                BeginPaint(hwnd, &ps);
                pDemoApp->Paint();
                EndPaint(hwnd, &ps);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_DESTROY:
            {
                PostQuitMessage(0);
            }
            result = 1;
            wasHandled = true;
            break;

            // 以下は追加したメッセージハンドラ
            // FIXME: result, wasHandled が正しく決められてる? 何に使ってる?
            case WM_KEYDOWN:
            {
                SetCapture(hwnd);

                int k = static_cast<int>(wParam);
                Input::m_isKeyDownFrame[k] = true;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_KEYUP:
            {
                ReleaseCapture();

                int k = static_cast<int>(wParam);
                Input::m_isKeyDownFrame[k] = false;
                Input::InitKeyDownFrameCount(k);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_LBUTTONDOWN:
            {
                SetCapture(hwnd);
                Input::m_mouseDownL = true;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_LBUTTONUP:
            {
                ReleaseCapture();
                Input::m_mouseDownL = false;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_RBUTTONDOWN:
            {
                SetCapture(hwnd);
                Input::m_mouseDownR = true;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_RBUTTONUP:
            {
                ReleaseCapture();
                Input::m_mouseDownR = false;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_TIMER:
            {
                for (auto p : Input::m_isKeyDownFrame) {
                    if (p.second == true) {
                        int k = p.first;
                        if (Input::m_keyDownFrameCount.count(k) == 0) {
                            Input::InitKeyDownFrameCount(k);
                        }
                        Input::m_keyDownFrameCount[k] += 1;
                    }
                }

                // マウスカーソル座標に関する更新
                POINT p;
                GetCursorPos(&p);
                ScreenToClient(hwnd, &p);
                int mouseX = p.x;
                int mouseY = p.y;

                // 差分を計算してmouseDeltaに持っておく
                Input::m_mouseDelta[0] = mouseX - Input::m_prevMousePos[0];
                Input::m_mouseDelta[1] = mouseY - Input::m_prevMousePos[1];

                Input::m_prevMousePos[0] = mouseX;
                Input::m_prevMousePos[1] = mouseY;

                // 座標を保存
                Input::m_mousePos[0] = mouseX;
                Input::m_mousePos[1] = mouseY;

                // cursorCaptureMode用の処理
                if (Input::m_captureCursorMode && Input::m_mouseDelta[0] == 0 && Input::m_mouseDelta[1] == 0) {
                    // 移動量がゼロなら中央に戻す
                    // FIXME: スクリーンの端に到達したときも中央に戻したい
                    long width;
                    long height;
                    std::tie(width, height) = Render::GetClientSize();
                    POINT screenCenter = { width / 2, height / 2 };

                    // 中央に戻した際のdeltaは無効化
                    // FIXME: prevMousePosが正しくなくなるからいじらないで済ませたい気がする
                    Input::m_prevMousePos[0] = screenCenter.x;
                    Input::m_prevMousePos[1] = screenCenter.y;
                    // 中央に戻す
                    ClientToScreen(hwnd, &screenCenter);
                    SetCursorPos(screenCenter.x, screenCenter.y);
                }

                if (Input::m_mouseDelta[0] != 0 || Input::m_mouseDelta[1] != 0) {
                    // mouseMoveイベントハンドラ
                    pDemoApp->m_scene->onMouseMove();
                }

                // Sceneを更新
                pDemoApp->UpdateScene();
            }
            result = 0;
            wasHandled = true;
            break;

            }
        }

        if (!wasHandled)
        {
            result = DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

    return result;
}

void DemoApp::EnterScene()
{
    // FIXME: Begin~EndDrawが必要っぽい
    m_scene->enter();
}

void DemoApp::UpdateScene()
{
    m_scene->update();
    InvalidateRect(Render::m_hwnd, nullptr, true);
}

void DemoApp::Paint()
{
    Render::Begin();
    Render::Clear();
    for (auto queue : Render::m_renderQueue) {
        for (auto renderFn : queue) {
            renderFn();
        }
    }
    HRESULT hr = Render::End();

    if (hr == D2DERR_RECREATE_TARGET) {
        hr = S_OK;
        DiscardDeviceResources();
    }
}

void DemoApp::OnResize(UINT width, UINT height)
{
    if (Render::m_renderTarget)
    {
        // Note: This method can fail, but it's okay to ignore the
        // error here, because the error will be returned again
        // the next time EndDraw is called.
        Render::m_renderTarget->Resize(D2D1::SizeU(width, height));
    }
}





