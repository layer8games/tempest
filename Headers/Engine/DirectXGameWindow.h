#pragma once
#define WIN32_LEAN_AND_MEAN

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/GameWindow.h>

namespace Tempest
{
    class DirectXGameWindow : public GameWindow
    {
    public:
        DirectXGameWindow(void);

        ~DirectXGameWindow(void);

        TEMPEST_API void v_Init(S32 width, S32 height, string wndName, bool isFullScreen) final;

        TEMPEST_API void v_ProcessEvents(void) final;

        TEMPEST_API void v_BufferSwap(void) final;

        TEMPEST_API void v_DisplayFPS(void) final;

        TEMPEST_API void v_ToggleWireFrame(void) final;

        TEMPEST_API void v_ResetMouseCursor(void) final;

        TEMPEST_API void v_EnableMouseCursor(void) final;

        TEMPEST_API void v_DisableMouseCursor(void) final;

        TEMPEST_API void v_HideMouseCursor(void) final;

        TEMPEST_API const TM::Point2 v_GetMousePos(void) final;

        TEMPEST_API const TM::Point2 v_GetMousePosInScreen(void) final;

        TEMPEST_API F64 v_GetTime(void) final;
        
        TEMPEST_API void v_EndRunning(void) final;

        TEMPEST_API void v_SetScreenColor(const Color& color) final;

    private:  
        void _InitializeWindows(int&, int&);
    
        void _ShutdownWindows(void);

        LPCWSTR _applicationName;
        HINSTANCE _hinstance;
        HWND _hwnd;
        F64  _pcFreq;
        S64	 _counterStart;

    };//end Class
    typedef shared_ptr<DirectXGameWindow> p_DirectXGameWindow;

    static LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
    {
        switch(umessage)
        {
            // Check if the window is being destroyed.
            case WM_DESTROY:
            {
                PostQuitMessage(0);
                return 0;
            }

            // Check if the window is being closed.
            case WM_CLOSE:
            {
                PostQuitMessage(0);		
                return 0;
            }

            // All other messages pass to the message handler in the system class.
            default:
            {
                // TODO: When windows message handler is implemented, send a message like this
                //return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
                return 0;
            }
        }
    }
}
