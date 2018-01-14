#include "stdafx.h"
#include "Render.h"

ID2D1HwndRenderTarget* Render::m_renderTarget = NULL;
HWND Render::m_hwnd = NULL;
ID2D1Factory* Render::m_direct2dFactory = NULL;
ID2D1SolidColorBrush* Render::m_brush = NULL;
ID2D1SolidColorBrush* Render::m_brush_white = NULL;

Render::Render()
{
}


Render::~Render()
{
}

void Render::Begin()
{
    HRESULT hr = S_OK;

    hr = CreateDeviceResources();

    if (SUCCEEDED(hr)){
        m_renderTarget->BeginDraw();
    }
}

void Render::End()
{
    m_renderTarget->EndDraw();
}

void Render::Clear()
{
    m_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Render::DrawRect(float x, float y, float w, float h, int color)
{
    D2D1_RECT_F rect = D2D1::RectF(
        x,
        y,
        x + w,
        y + h
    );

    ID2D1SolidColorBrush* brush = color == 0 ? m_brush_white : m_brush;
    m_renderTarget->FillRectangle(&rect, brush);
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
                D2D1::ColorF(D2D1::ColorF::LightGreen),
                &m_brush
            );
        }
        if (SUCCEEDED(hr))
        {
            hr = m_renderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::White),
                &m_brush_white
            );
        }
    }

    return hr;
}
