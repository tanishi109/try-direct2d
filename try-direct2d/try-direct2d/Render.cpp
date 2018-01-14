#include "stdafx.h"
#include "Render.h"

ID2D1HwndRenderTarget* Render::m_renderTarget = NULL;
HWND Render::m_hwnd = NULL;
ID2D1Factory* Render::m_direct2dFactory = NULL;
ID2D1SolidColorBrush* Render::m_brush = NULL;

Render::Render()
{
}


Render::~Render()
{
}

void Render::DrawRect(float x, float y, float w, float h)
{
    HRESULT hr = S_OK;

    hr = CreateDeviceResources();

    if (SUCCEEDED(hr)){
        m_renderTarget->BeginDraw();

        D2D1_RECT_F rect = D2D1::RectF(
            x,
            y,
            x + w,
            y + h
        );

        m_renderTarget->FillRectangle(&rect, m_brush);

        m_renderTarget->EndDraw();

        // TODO: WM_PAINT‚ÉˆÚ‚µ‚½‚Ù‚¤‚ª‚¢‚¢‚©‚à?
        // InvalidateRect(m_hwnd, NULL, true);
    }
}

HRESULT Render::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    if (!m_renderTarget)
    {
        RECT rc;
        GetClientRect(m_hwnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(
            rc.right - rc.left,
            rc.bottom - rc.top
        );

        // Create a Direct2D render target.
        hr = m_direct2dFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hwnd, size),
            &m_renderTarget
        );


        if (SUCCEEDED(hr))
        {
            hr = m_renderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::LightSlateGray),
                &m_brush
            );
        }
    }

    return hr;
}
