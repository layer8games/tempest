/*------------------------------------------------------------
This file will test the functionality of the Vector4 class which
will be used in the Killer1 Engine. Most of the examples and all
of the equations are from 3D Math Primer for Graphics and Game
Development by Dunn and Parberry (awesome book for those who 
wish to learn). 

Uses the boost test library.

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.


Written by Maxwell Miller
-------------------------------------------------------------*/
//==========================================================================================================================
//
//Non-required file. Here to set up global helper functions to be used throughout the testing framework. 
//
//==========================================================================================================================
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Engine.h>

#include <iostream>

namespace KE = KillerEngine;

//==========================================================================================================================
//
//Setup2D will initialize OpenGL and allow for sprites and other graphic's related tests to be able to compile and run.
//
//==========================================================================================================================
static bool SETUP_2D_CALLED = false; 

void inline Setup(void)
{
	if(!SETUP_2D_CALLED)
	{
		//=====Window Parameter Constants=====
		const S32    wndWidth  	   = 1024;
		const S32    wndHeight 	   = 768;
		const string wndTitle	   = "Killer Unit Tests";
		const S32    wndFullScreen = false;
	
	
		KE::Engine::Instance()->Init(wndWidth, wndHeight, wndTitle, wndFullScreen);
		KE::ErrorManager::Instance()->DisplayErrors();
	}
}

void inline ShutDown(void)
{
	KE::Engine::Instance()->ShutDown();
}

F32 inline RoundFloat(F32 n)
{
	return floor(n * 100000 + 0.5f) / 100000;
}

real inline RoundReal(real n)
{
	return floor(n * 100000 + 0.5f) / 100000;
}
