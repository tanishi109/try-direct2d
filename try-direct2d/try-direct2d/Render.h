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
    static void DrawRect(int x, int y, int w, int h, int color);
    static void DrawText(int x, int y, int w, int h, std::wstring text);
//private:
    static HRESULT CreateDeviceResources();
    static HRESULT CreateDeviceIndependentResources();

    static HWND m_hwnd;
    static ID2D1Factory* m_direct2dFactory;
    static IDWriteFactory* m_dWriteFactory;
    static IDWriteTextFormat* m_textFormat;
    static ID2D1HwndRenderTarget* m_renderTarget;
    static ID2D1SolidColorBrush* m_brush; // FIXME: �u���V��e�L�X�g�̃t�H�[�}�b�g���炩���ߗp�ӂ��Ă����Ȃ��Ƃ����Ȃ��̂͂ǂ��ɂ��Ȃ�Ȃ�?
    static ID2D1SolidColorBrush* m_brush_white;
};
