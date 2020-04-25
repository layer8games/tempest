#pragma once

//=====Tempest includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/Point2.h>
#include <Engine/Keys.h>

namespace TM = TempestMath; 

//===== STL Includes =====
#include <sstream>

namespace Tempest 
{
    class GameWindow
    {	
    public:
//==========================================================================================================================
//
//Constructors
//
//========================================================================================================================== 

        TEMPEST_API virtual ~GameWindow(void);

//==========================================================================================================================
//
//GameWindow Functions
//
//==========================================================================================================================
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
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
        
        inline bool GetRunning(void) 
        { 
            return _running;
        }
 
        inline S32 GetScreenWidth(void)
        { 
            return _screenWidth; 
        }
 
        inline S32 GetScreenHeight(void)
        { 
            return _screenHeight; 
        }
         
        inline F32 GetScreenRight(void)
        { 
            return _right; 
        }
       
        inline F32 GetScreenLeft(void)
        { 
            return _left; 
        }
        
        inline F32 GetScreenTop(void)
        { 
            return _top; 
        }
      
        inline F32 GetScreenBottom(void)
        { 
            return _bottom; 
        }

    protected:      
//==========================================================================================================================
//
//Constructor
//
//========================================================================================================================== 
        GameWindow(void);
        
        
        bool _isFullScreen;		
        bool _running;			
        bool _wireFrame;		
        TEMPEST_API static S32  _screenWidth;		
        TEMPEST_API static S32  _screenHeight;		
        F32  _right;			
        F32  _left;				
        F32  _top;				
        F32  _bottom;			
        string _wndName;			
    };
    typedef shared_ptr<GameWindow> p_GameWindow;
}//End namespace