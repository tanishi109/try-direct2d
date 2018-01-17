#include "stdafx.h"
#include "Render.h"

ID2D1HwndRenderTarget* Render::m_renderTarget = NULL;
HWND Render::m_hwnd = NULL;
ID2D1Factory* Render::m_direct2dFactory = NULL;
IDWriteFactory* Render::m_dWriteFactory = NULL;
IDWriteTextFormat* Render::m_textFormat = NULL;
ID2D1SolidColorBrush* Render::m_brush = NULL;
ID2D1SolidColorBrush* Render::m_brush_white = NULL;
ID2D1SolidColorBrush* Render::m_brush_black = NULL;

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

void Render::DrawRect(int x, int y, int w, int h, int color)
{
    // FIXME: float‚Écast‚µ‚½‚¢,ˆø”‚àfloat‚É‚µ‚½‚¢
    D2D1_RECT_F rect = D2D1::RectF(
        x,
        y,
        x + w,
        y + h
    );

    ID2D1SolidColorBrush* brush = color == 0 ? m_brush_white : m_brush;
    if (color == 0) {
        brush = m_brush_white;
    } else if (color == 1) {
        brush = m_brush;
    } else {
        brush = m_brush_black;
    }
    m_renderTarget->DrawRectangle(&rect, brush);
}

// FIXME: •¶Žš—ñ‚Ü‚í‚è‚¢‚ë‚ñ‚ÈŒ^‚ª‚ ‚è‚»‚¤‚È‚Ì‚Å‚±‚ê‚ª“K“–‚©’²‚×‚Ä
void Render::DrawText(int x, int y, int w, int h, std::wstring text)
{
    // Retrieve the size of the render target.
    D2D1_SIZE_F renderTargetSize = m_renderTarget->GetSize();

    m_renderTarget->DrawText(
        text.c_str(),
        text.size(),
        m_textFormat,
        D2D1::RectF(x, y, w, h), // FIXME: ‚±‚±‚àfloat‚Écast
        m_brush_black
    );
}

void Render::SetRotation(float degree, float centerX, float centerY)
{
    D2D1::Matrix3x2F matrix = D2D1::Matrix3x2F::Rotation(degree, D2D1::Point2F(centerX, centerY));
    m_renderTarget->SetTransform(matrix);
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
        if (SUCCEEDED(hr))
        {
            hr = m_renderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Black),
                &m_brush_black
            );
        }
    }

    return hr;
}

HRESULT Render::CreateDeviceIndependentResources()
{
    HRESULT hr = S_OK;

    // Create a Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_direct2dFactory);

    // •¶Žš•`‰æ‚Ì‚½‚ß
    static const WCHAR msc_fontName[] = L"Verdana";
    static const FLOAT msc_fontSize = 16;

    if (SUCCEEDED(hr))
    {
        // Create a DirectWrite factory.
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_dWriteFactory),
            reinterpret_cast<IUnknown **>(&m_dWriteFactory)
        );
    }
    if (SUCCEEDED(hr))
    {
        // Create a DirectWrite text format object.
        hr = m_dWriteFactory->CreateTextFormat(
            msc_fontName,
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            msc_fontSize,
            L"", //locale
            &m_textFormat
        );
    }
    if (SUCCEEDED(hr))
    {
        // Center the text horizontally and vertically.
        m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

        m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    return hr;
}
