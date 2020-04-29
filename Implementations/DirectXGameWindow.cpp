#include "stdafx.h"
#include <Engine/DirectXGameWindow.h>
using namespace Tempest;

DirectXGameWindow::DirectXGameWindow(void)
    :
    _applicationName(),
    _hinstance(),
    _hwnd(),
    _pcFreq(0.0),
    _counterStart(0)
{
    LARGE_INTEGER li;
    if(!QueryPerformanceFrequency(&li))
    {
        TE::ErrorManager::Instance()->SetError(TE::MATH, "Timer::_QueryCounter:: Call to QueryPerformanceFrequency failed. This is a really bad thing!");
    }

    _pcFreq = static_cast<F64>(li.QuadPart) / 1000.0;

    QueryPerformanceCounter(&li);
    _counterStart = li.QuadPart;
}

DirectXGameWindow::~DirectXGameWindow(void)
{  }

void DirectXGameWindow::v_Init(S32 width, S32 height, string wndName, bool isFullScreen)
{
    WNDCLASSEX wc;
    DEVMODE dmScreenSettings;
    S32 posX;
    S32 posY;

    _hinstance = GetModuleHandle(NULL);

    wc.style         = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = _hinstance;
    wc.hIcon         = LoadIcon(NULL, IDI_WINLOGO);
    wc.hIconSm       = wc.hIcon;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = wndName.c_str();
    wc.cbSize        = sizeof(WNDCLASSEX);
    
    RegisterClassEx(&wc);

    if(isFullScreen)
    {
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth  = (unsigned long)_screenWidth;
        dmScreenSettings.dmPelsHeight = (unsigned long)_screenHeight;
        dmScreenSettings.dmBitsPerPel = 32;			
        dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // Change the display settings to full screen.
        ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

        // Set the position of the window to the top left corner.
        posX = posY = 0;
    }
    else
    {
        // If windowed then set it to 800x600 resolution.
        _screenWidth  = 800;
        _screenHeight = 600;

        // Place the window in the middle of the screen.
        posX = (GetSystemMetrics(SM_CXSCREEN) - _screenWidth)  / 2;
        posY = (GetSystemMetrics(SM_CYSCREEN) - _screenHeight) / 2;
    }

    // Create the window with the screen settings and get the handle to it.
    _hwnd = CreateWindowEx(WS_EX_APPWINDOW, wndName.c_str(), wndName.c_str(), 
                WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
                posX, posY, _screenWidth, _screenHeight, NULL, NULL, _hinstance, NULL);

    // Bring the window up on the screen and set it as main focus.
    ShowWindow(_hwnd, SW_SHOW);
    SetForegroundWindow(_hwnd);
    SetFocus(_hwnd);

    // Hide the mouse cursor.
    ShowCursor(false);

    return;
}

void DirectXGameWindow::v_ProcessEvents(void)
{

}

void DirectXGameWindow::v_BufferSwap(void)
{

}

void DirectXGameWindow::v_DisplayFPS(void)
{

}

void DirectXGameWindow::v_ToggleWireFrame(void)
{

}

void DirectXGameWindow::v_ResetMouseCursor(void)
{

}

void DirectXGameWindow::v_EnableMouseCursor(void)
{

}

void DirectXGameWindow::v_DisableMouseCursor(void)
{

}

void DirectXGameWindow::v_HideMouseCursor(void)
{

}

// TODO:: this may have to move to a different place.
const TM::Point2 DirectXGameWindow::v_GetMousePos(void)
{
    return TM::Point2();
}

const TM::Point2 DirectXGameWindow::v_GetMousePosInScreen(void)
{
    return TM::Point2();
}

F64 DirectXGameWindow::v_GetTime(void)
{
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return static_cast<F64>(li.QuadPart - _counterStart) / _pcFreq;
}
        
void DirectXGameWindow::v_EndRunning(void)
{
    
}

void DirectXGameWindow::v_SetScreenColor(const Color& color)
{

}

void DirectXGameWindow::_InitializeWindows(int&, int&)
{

}
    
void DirectXGameWindow::_ShutdownWindows(void)
{

}