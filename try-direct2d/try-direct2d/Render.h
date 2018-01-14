#pragma once
class Render
{
friend class DemoApp;
public:
    Render();
    ~Render();

    static void Begin();
    static void End();
    static void Clear();
    static void DrawRect(float x, float y, float w, float h);
//private:
    static HRESULT CreateDeviceResources();

    static HWND m_hwnd;
    static ID2D1Factory* m_direct2dFactory;
    static ID2D1HwndRenderTarget* m_renderTarget;
    static ID2D1SolidColorBrush* m_brush;
    static ID2D1SolidColorBrush* m_brush_white;
};

