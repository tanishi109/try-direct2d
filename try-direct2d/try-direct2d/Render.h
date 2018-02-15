#pragma once
#include "BrushType.h"

class Render
{
friend class DemoApp;
public:
    Render();
    ~Render();

    static void Begin();
    static HRESULT End();
    static void Clear();
    // 描画用関数
    static void DrawRect(int x, int y, int w, int h, BrushType type);
    static void DrawCircle(int x, int y, int r, BrushType type);
    static void DrawString(int x, int y, int w, int h, std::string string);
    static void SetRotation(float degree, float centerX, float centerY);
    static void TakeScreenShot();
    static void DrawScreenShot(int zIndex);
    // 描画用関数ここまで
    static std::tuple<long, long> GetClientSize();
    static HRESULT CreateDeviceResources();
    static HRESULT CreateDeviceIndependentResources();

    static HWND m_hwnd;

private:
    static ID2D1SolidColorBrush* getBrush(BrushType type);

    static ID2D1Factory* m_direct2dFactory;
    static IDWriteFactory* m_dWriteFactory;
    static IDWriteTextFormat* m_textFormat;
    static ID2D1HwndRenderTarget* m_renderTarget;
    // FIXME: ブラシやテキストのフォーマットあらかじめ用意しておかないといけないのはどうにかならない?
    // FIXME: スネークケースになってるの直す
    static ID2D1SolidColorBrush* m_brush; 
    static ID2D1SolidColorBrush* m_brush_white;
    static ID2D1SolidColorBrush* m_brush_black;
    static ID2D1SolidColorBrush* m_brush_pink;
    static ID2D1SolidColorBrush* m_bBrush;
    
    static IWICBitmap* m_wicBmp;
    static ID2D1Bitmap* m_direct2dBmp;
    static ID2D1RenderTarget* m_bmpRenderTarget;
    static IWICImagingFactory* m_wicImagingFactory;

    // 描画準備: m_zIndex番目のlistに描画用関数を追加していく
    // 描画: 0番目のlistから順に要素として持つ関数を実行
    static std::list<std::function<void()>> m_renderQueue[3];
    static int m_zIndex;
};

