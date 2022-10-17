#include "Figure.h"



VOID OnPaint(HDC hdc)
{
    Gdiplus::Graphics graphics(hdc);
    Drawer *drawer = new gdiplusDrawer(&graphics);
    TopRectangle rec(100,100,300,300, DrawerColor(255,0,0,127));
    rec.draw(drawer);
    TopCircle circle(250,250,150);
    circle.draw(drawer);
    TopTriangle triang(250,100,400,400,100,400);
    triang.draw(drawer);
    std::vector<TopPoint> points{TopPoint(50,50),TopPoint(50,450),TopPoint(450,450),TopPoint(450,50)};
    TopPolygon poly(points);
    poly.draw(drawer);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style          = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc    = WndProc;
    wndClass.cbClsExtra     = 0;
    wndClass.cbWndExtra     = 0;
    wndClass.hInstance      = hInstance;
    wndClass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName   = NULL;
    wndClass.lpszClassName  = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
            TEXT("GettingStarted"),   // window class name
            TEXT("Getting Started"),  // window caption
            WS_OVERLAPPEDWINDOW,      // window style
            CW_USEDEFAULT,            // initial x position
            CW_USEDEFAULT,            // initial y position
            CW_USEDEFAULT,            // initial x size
            CW_USEDEFAULT,            // initial y size
            NULL,                     // parent window handle
            NULL,                     // window menu handle
            hInstance,                // program instance handle
            NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
                         WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch(message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            OnPaint(hdc);
            EndPaint(hWnd, &ps);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc