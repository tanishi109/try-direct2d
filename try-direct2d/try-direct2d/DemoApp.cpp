#include "stdafx.h"

#include "DemoApp.h"
#include "Input.h"
#include "Render.h"

template<class Interface>
inline void SafeRelease(
    Interface **ppInterfaceToRelease
)
{
    if (*ppInterfaceToRelease != NULL)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = NULL;
    }
}


#ifndef Assert
#if defined( DEBUG ) || defined( _DEBUG )
#define Assert(b) do {if (!(b)) {OutputDebugStringA("Assert: " #b "\n");}} while(0)
#else
#define Assert(b)
#endif //DEBUG || _DEBUG
#endif

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
    SafeRelease(&Render::m_direct2dFactory);
    SafeRelease(&Render::m_renderTarget);
    SafeRelease(&Render::m_brush);
}

void DemoApp::RunMessageLoop()
{
    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0))
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
        wcex.hbrBackground = NULL;
        wcex.lpszMenuName = NULL;
        wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
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
            NULL,
            NULL,
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

    return hr;
}

void DemoApp::DiscardDeviceResources()
{
    SafeRelease(&Render::m_renderTarget);
    SafeRelease(&Render::m_brush);
}

LRESULT CALLBACK DemoApp::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;

    if (message == WM_CREATE)
    {
        LPCREATESTRUCT pcs = (LPCREATESTRUCT)lParam;
        DemoApp *pDemoApp = (DemoApp *)pcs->lpCreateParams;

        ::SetWindowLongPtrW(
            hwnd,
            GWLP_USERDATA,
            PtrToUlong(pDemoApp)
        );

        result = 1;
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
                InvalidateRect(hwnd, NULL, FALSE);
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_PAINT:
            {
                ValidateRect(hwnd, NULL);
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
                Input::m_keyDown = wParam;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_KEYUP:
            {
                Input::m_keyDown = NULL;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_MOUSEMOVE:
            {
                const int mouseX = GET_X_LPARAM(lParam);
                const int mouseY = GET_Y_LPARAM(lParam);

                // 差分を計算してmouseDeltaに持っておく
                if (Input::m_prevMousePos[0] != NULL && Input::m_prevMousePos[1] != NULL) {
                    Input::m_mouseDelta[0] = mouseX - Input::m_prevMousePos[0];
                    Input::m_mouseDelta[1] = mouseY - Input::m_prevMousePos[1];
                }
                Input::m_prevMousePos[0] = mouseX;
                Input::m_prevMousePos[1] = mouseY;

                // 座標を保存
                Input::m_mousePos[0] = mouseX;
                Input::m_mousePos[1] = mouseY;
            }
            // mouseMoveイベントハンドラ
            pDemoApp->m_scene->onMouseMove();

            result = 0;
            wasHandled = true;
            break;

            case WM_LBUTTONDOWN:
            {
                Input::m_mouseDownL = true;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_LBUTTONUP:
            {
                Input::m_mouseDownL = false;
            }
            result = 0;
            wasHandled = true;
            break;

            }

            pDemoApp->UpdateScene();
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
    m_scene->enter();
}

void DemoApp::UpdateScene()
{
    // FIXME: でかいBegin~EndDrawで囲んでるのいいのかな?
    Render::Begin();
    m_scene->update();
    Render::End();
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





