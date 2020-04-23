#include <Engine/GameWindow.h>
using namespace Tempest;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================   
S32 GameWindow::_totalWidth = 0;
S32 GameWindow::_totalHeight = 0;
GameWindow::GameWindow(void) 
    : 
    _isFullScreen(false),
    _running(false),
    _wireFrame(false),
    _right(0), 
    _left(0),
    _top(0), 
    _bottom(0),
    _wndName("A Tempest Must Be Just That")
{  }

GameWindow::~GameWindow(void)
{  }
//==========================================================================================================================
//
//GameWindow Functions
//
//==========================================================================================================================
//==========================================================================================================================
//Init
//==========================================================================================================================
void GameWindow::Update(void)
{
    v_ProcessEvents();
}
