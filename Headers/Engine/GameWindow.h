#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/ErrorManager.h"
#include "Engine/Color.h"
#include "Engine/Timer.h"
#include "Engine/Vector2.h"
#include "Engine/Keys.h"

namespace TM = TempestMath; 

#include <sstream>

namespace Tempest 
{
    class GameWindow
    {	
    public:
        TEMPEST_API virtual ~GameWindow(void);

        TEMPEST_API void Update(void);

        TEMPEST_API virtual void v_Init(S32 width, S32 height, string wndName, bool isFullScreen)=0;

        TEMPEST_API virtual void v_ProcessEvents(void)=0;

        TEMPEST_API virtual void v_BufferSwap(void)=0;

        TEMPEST_API virtual void v_DisplayFPS(void)=0;

        TEMPEST_API virtual void v_ToggleWireFrame(void)=0;

        TEMPEST_API virtual void v_ResetMouseCursor(void)=0;

        TEMPEST_API virtual void v_EnableMouseCursor(void)=0;

        TEMPEST_API virtual void v_DisableMouseCursor(void)=0;

        TEMPEST_API virtual void v_HideMouseCursor(void)=0;

        TEMPEST_API virtual const TM::Point2 v_GetMousePos(void)=0;

        TEMPEST_API virtual const TM::Point2 v_GetMousePosInScreen(void)=0;

        TEMPEST_API virtual F64 v_GetTime(void)=0;
        
        TEMPEST_API virtual void v_EndRunning(void)=0;

        TEMPEST_API virtual void v_SetScreenColor(const Color& color)=0;
 
        TEMPEST_API S32 GetScreenWidth(void);
 
        TEMPEST_API S32 GetScreenHeight(void);
         
        TEMPEST_API F32 GetScreenRight(void);
       
        TEMPEST_API F32 GetScreenLeft(void);

        TEMPEST_API F32 GetScreenTop(void);
      
        TEMPEST_API F32 GetScreenBottom(void);

    protected:
        GameWindow(void);

        bool _isFullScreen;
        bool _wireFrame;
        TEMPEST_API static S32 _screenWidth;
        TEMPEST_API static S32 _screenHeight;
        F32  _right;
        F32  _left;
        F32  _top;
        F32  _bottom;
        string _wndName;
    };
    typedef shared_ptr<GameWindow> p_GameWindow;
}//End namespace