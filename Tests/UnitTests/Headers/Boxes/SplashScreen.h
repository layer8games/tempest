/*==========================================================================================================================
Opening Splash screen prototype

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
==========================================================================================================================*/
#pragma once

//Killer1 includes
#include <Engine/Atom.h>
#include <Engine/LevelManager.h>
#include <Engine/GameWindow.h>
#include <Engine/Level.h>
#include <Engine/Timer.h>
#include <Engine/TextureManager.h>
#include <Engine/FontManager.h>
#include <Engine/Text.h>
#include <Engine/Color.h>
#include <Engine/Point.h>
#include <Engine/Controller.h>
#include <Engine/Engine.h>
#include <Engine/AudioManager.h>
#include <Engine/ErrorManager.h>


namespace KE = KillerEngine;
namespace KM = KillerMath;

//=====Box includes=====
#include <Boxes/Box.h>
#include <Boxes/DataBases.h>

namespace Boxes 
{

	class SplashScreen: public KE::Level
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		SplashScreen(void);
		
		~SplashScreen(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
		void v_Init() final;
		
		void v_Update(void) final;
	
	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================		
		p_Box 	 _red;
		p_Box 	 _green;
		p_Box 	 _blue;
		KE::Text _mainTitle;
	};//End Class
}