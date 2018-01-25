#include "stdafx.h"

// FIXME: ���ODemoApp����Ȃ���������
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
    // TODO Render�Ɉړ�
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

    // Scene��Enter����
    // FIXME: �����łق�Ƃɑ��v?
    EnterScene();

    return hr;
}

void DemoApp::DiscardDeviceResources()
{
    // TODO: Render�Ɉړ�
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

        // �Q�[�����[�v�p�̃^�C�}�[
        SetTimer(hwnd, 1, 16.666, NULL);
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

            // �ȉ��͒ǉ��������b�Z�[�W�n���h��
            // FIXME: result, wasHandled �����������߂��Ă�? ���Ɏg���Ă�?
            case WM_KEYDOWN:
            {
                SetCapture(hwnd);
                Input::m_keyDown = wParam;
            }
            result = 0;
            wasHandled = true;
            break;

            case WM_KEYUP:
            {
                ReleaseCapture();
                Input::m_keyDown = NULL;
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
                // �}�E�X�J�[�\�����W�Ɋւ���X�V
                POINT p;
                GetCursorPos(&p);
                ScreenToClient(hwnd, &p);
                int mouseX = p.x;
                int mouseY = p.y;

                // �������v�Z����mouseDelta�Ɏ����Ă���
                if (Input::m_prevMousePos[0] != NULL && Input::m_prevMousePos[1] != NULL) {
                    Input::m_mouseDelta[0] = mouseX - Input::m_prevMousePos[0];
                    Input::m_mouseDelta[1] = mouseY - Input::m_prevMousePos[1];
                }
                Input::m_prevMousePos[0] = mouseX;
                Input::m_prevMousePos[1] = mouseY;

                // ���W��ۑ�
                Input::m_mousePos[0] = mouseX;
                Input::m_mousePos[1] = mouseY;

                // cursorCaptureMode�p�̏���
                if (Input::m_captureCursorMode && Input::m_mouseDelta[0] == 0 && Input::m_mouseDelta[1] == 0) {
                    // �ړ��ʂ��[���Ȃ璆���ɖ߂�
                    // FIXME: �X�N���[���̒[�ɓ��B�����Ƃ��������ɖ߂�����
                    RECT windowRect;
                    GetClientRect(hwnd, &windowRect);

                    long width = windowRect.right - windowRect.left;
                    long height = windowRect.bottom - windowRect.top;

                    POINT screenCenter = { width / 2, height / 2 };
                    // �����ɖ߂����ۂ�delta�͖�����
                    // FIXME: prevMousePos���������Ȃ��Ȃ邩�炢����Ȃ��ōς܂������C������
                    Input::m_prevMousePos[0] = screenCenter.x;
                    Input::m_prevMousePos[1] = screenCenter.y;
                    // �����ɖ߂�
                    ClientToScreen(hwnd, &screenCenter);
                    SetCursorPos(screenCenter.x, screenCenter.y);
                }

                if (Input::m_mouseDelta[0] != 0 || Input::m_mouseDelta[1] != 0) {
                    // mouseMove�C�x���g�n���h��
                    pDemoApp->m_scene->onMouseMove();
                }

                // Scene���X�V
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
    m_scene->enter();
}

void DemoApp::UpdateScene()
{
    // FIXME: �ł���Begin~EndDraw�ň͂�ł�̂����̂���?
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





