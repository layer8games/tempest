#include "stdafx.h"
#include <Engine/GameWindow.h>
using namespace Tempest;

S32 GameWindow::_screenWidth = 0;
S32 GameWindow::_screenHeight = 0;
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

void GameWindow::Update(void)
{
    v_ProcessEvents();
}
