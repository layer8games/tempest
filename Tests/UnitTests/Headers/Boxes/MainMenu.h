/*==========================================================================================================================
Main Menu used to select different modes that the game can use, as well as an exit. This can be reached at any time by 
pressing the ESC key in this project.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
==========================================================================================================================*/
#ifndef MAIN_MAIN_H
#define MAIN_MAIN_H

//=====Engine includes=====
#include <Engine/Atom.h>
#include <Engine/LevelManager.h>
#include <Engine/WinProgram.h>
#include <Engine/Level.h>
#include <Engine/Controller.h>
#include <Engine/TextureManager.h>
#include <Engine/FontManager.h>
#include <Engine/Text.h>
#include <Engine/Engine.h>
#include <Engine/Point.h>
#include <Engine/Color.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

//=====Box includes=====
#include <Boxes/Box.h>

namespace Boxes
{
	class MainMenu : public KE::Level
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		MainMenu(void);

		~MainMenu(void);

//==========================================================================================================================
//
//Virtual Functions 
//
//==========================================================================================================================		
		void v_InitLevel(U32 id, S32 w, S32 h, const KE::Color& c);

		void v_Update(void);

	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================		
//==========================================================================================================================
//Menu Members. For now the menu is going to be hard coded into this level. There is a project added to make this an enigine
//feature, so when that is completed this will be replaced. 
//==========================================================================================================================				
		KM::Point   _itemPositions[10];
		U8		    _maxPosition;
		U32		    _selectorPosition;
		Box 	    _selector;
		KE::Font    _menuItemFont;
		KE::Text    _mainTitle;
		KE::Text    _menuItem_Level1;
		KE::Text    _menuItem_BallisticsDemo;
		KE::Text    _menuItem_RainDemo;
		KE::Text    _menuItem_LevelFour;
		KE::Text    _menuItem_Fireworks;
		KE::Text    _menuItem_Springs;
	};
}

#endif