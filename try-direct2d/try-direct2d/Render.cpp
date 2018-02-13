#include "stdafx.h"
#include "Render.h"
#include "Stringtool.h"

// FIXME: SafeReleaseしてないやつある
ID2D1HwndRenderTarget* Render::m_renderTarget = nullptr;
HWND Render::m_hwnd = nullptr;
ID2D1Factory* Render::m_direct2dFactory = nullptr;
IDWriteFactory* Render::m_dWriteFactory = nullptr;
IDWriteTextFormat* Render::m_textFormat = nullptr;
ID2D1SolidColorBrush* Render::m_brush = nullptr;
ID2D1SolidColorBrush* Render::m_brush_white = nullptr;
ID2D1SolidColorBrush* Render::m_brush_black = nullptr;
ID2D1SolidColorBrush* Render::m_brush_pink = nullptr;
ID2D1SolidColorBrush* Render::m_bBrush = nullptr;
IWICBitmap* Render::m_wicBmp = nullptr;
ID2D1Bitmap* Render::m_direct2dBmp = nullptr;
ID2D1RenderTarget* Render::m_bmpRenderTarget = nullptr;
IWICImagingFactory* Render::m_wicImagingFactory = nullptr;

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
        m_bmpRenderTarget->BeginDraw();
    }
}

HRESULT Render::End()
{
    HRESULT hr = S_OK;
    hr = m_renderTarget->EndDraw();
    hr = m_bmpRenderTarget->EndDraw();

    return hr;
}

void Render::Clear()
{
    m_renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
    m_bmpRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Render::DrawRect(int x, int y, int w, int h, BrushType type)
{
    // FIXME: floatにcastしたい,引数もfloatにしたい
    D2D1_RECT_F rect = D2D1::RectF(
        x,
        y,
        x + w,
        y + h
    );

    ID2D1SolidColorBrush* brush = getBrush(type);
    m_renderTarget->DrawRectangle(&rect, brush);
    m_bmpRenderTarget->DrawRectangle(&rect, m_bBrush);
}

void Render::DrawCircle(int x, int y, int r, BrushType type)
{
    D2D1_ELLIPSE ellipse = D2D1::Ellipse(
        D2D1::Point2F(x, y),
        r,
        r
    );

    ID2D1SolidColorBrush* brush = getBrush(type);
    m_renderTarget->FillEllipse(ellipse, brush);
    m_bmpRenderTarget->FillEllipse(ellipse, m_bBrush);
}

void Render::DrawString(int x, int y, int w, int h, std::string string)
{
    // ID2D1HwndRenderTarget::DrawTextはWCHARを引数に取るのでwstringに変換
    std::wstring wstring = Stringtool::ToWString(string);
    // Retrieve the size of the render target.
    D2D1_SIZE_F renderTargetSize = m_renderTarget->GetSize();

    m_renderTarget->DrawText(
        wstring.c_str(),
        wstring.size(),
        m_textFormat,
        D2D1::RectF(x, y, x + w, y + h), // FIXME: ここもfloatにcast
        m_brush_black
    );

    // いまは文字はスクショに含めていないが、引数で設定できてもいいかも
    // m_bmpRenderTarget->DrawText();
}

void Render::SetRotation(float degree, float centerX, float centerY)
{
    D2D1::Matrix3x2F matrix = D2D1::Matrix3x2F::Rotation(degree, D2D1::Point2F(centerX, centerY));
    m_renderTarget->SetTransform(matrix);
    m_bmpRenderTarget->SetTransform(matrix);
}

void Render::TakeScreenShot()
{
    End();
    HRESULT r = m_renderTarget->CreateBitmapFromWicBitmap(m_wicBmp, &m_direct2dBmp);
    Begin();
}

void Render::DrawScreenShot()
{
    if (m_direct2dBmp != nullptr) {
        m_renderTarget->DrawBitmap(m_direct2dBmp, nullptr, 0.5); // TODO: opacityをベタ打ちしない
    }
}

std::tuple<long, long> Render::GetClientSize()
{
    RECT windowRect;
    GetClientRect(m_hwnd, &windowRect);

    long width = windowRect.right - windowRect.left;
    long height = windowRect.bottom - windowRect.top;

    return {width, height};
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

        // bitmap描画用のrenderTarget
        // FIXME: ここのサイズwindowサイズの変更に対応
        m_wicImagingFactory->CreateBitmap(size.width, size.height, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnDemand, &m_wicBmp);

        m_direct2dFactory->CreateWicBitmapRenderTarget(
            m_wicBmp,
            D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_DEFAULT,
                D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
                96.0f, 96.0f
            ),
            &m_bmpRenderTarget);

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
        if (SUCCEEDED(hr))
        {
            hr = m_renderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::LightPink),
                &m_brush_pink
            );
        }
        if (SUCCEEDED(hr))
        {
            hr = m_bmpRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::LightGray),
                &m_bBrush
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

    // bitmap書き出しのため
    CoInitialize(nullptr);

    CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        (LPVOID*)&m_wicImagingFactory
    );

    // 文字描画のため
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
            nullptr,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            msc_fontSize,
            L"en-us", //locale
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

ID2D1SolidColorBrush* Render::getBrush(BrushType type)
{
    if (type == BrushType_white) {
        return m_brush_white;
    }
    if (type == BrushType_black){
        return m_brush_black;
    }
    if (type == BrushType_green) {
        return m_brush;
    }
    if (type == BrushType_pink){
        return m_brush_pink;
    }

    return nullptr;
}
