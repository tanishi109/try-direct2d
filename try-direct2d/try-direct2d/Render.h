#pragma once
#include "BrushType.h"

class Render
{
friend class DemoApp;
public:
    Render();
    ~Render();

    static void Begin();
    static void End();
    static void Clear();
    static void DrawRect(int x, int y, int w, int h, BrushType type);
    static void DrawCircle(int x, int y, int r, BrushType type);
    static void DrawText(int x, int y, int w, int h, std::wstring text);
    static void SetRotation(float degree, float centerX, float centerY);
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
};

