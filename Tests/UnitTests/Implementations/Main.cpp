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
//Required file. Simply here to get the test framework set up.
//
//==========================================================================================================================

#define BOOST_TEST_MAIN KillerUnitTests

#include <boost/test/unit_test.hpp>
#include <boost/test/debug.hpp>
//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/Timer.h>
#include <Engine/LevelManager.h>
#include <Engine/Controller.h>
#include <Engine/WinProgram.h>
#include <Engine/TextureManager.h>
#include <Engine/FontManager.h>
#include <Engine/Engine.h>
#include <Engine/Color.h>
#include <Engine/Shader.h>
namespace KE = KillerEngine;

//=====Game Includes=====
#include <Boxes/MainMenu.h>
#include <Boxes/SplashScreen.h>
#include <Boxes/MovingBoxes.h>
#include <Boxes/Ballistics.h>
#include <Boxes/FireworksDemo.h>
#include <Boxes/Springs.h>
#include <Boxes/Demo3D.h>
#include <Boxes/Box.h>

using namespace Boxes;

//void 

BOOST_AUTO_TEST_CASE(UITests)
{
	//Disables memory leak detection. There are a lot... like... a lot a lot of memory leaks. This should be fixed someday. 
	boost::debug::detect_memory_leaks(false);

//=====Window Parameter Constants=====
	const S32    wndWidth  	   = 1024;
	const S32    wndHeight 	   = 768;
	const string wndTitle	   = "Killer Engine UI Tests v0.1";
	const S32    wndFullScreen = false;


	KE::Engine::Instance()->Init(wndWidth, wndHeight, wndTitle, wndFullScreen);

//=====Pre-Load Assets=====	
	KE::TextureManager::Instance()->LoadTexture(100, "../Assets/Textures/Boxes/RedBox.png");
	KE::TextureManager::Instance()->LoadTexture(101, "../Assets/Textures/Boxes/GreenBox.png");
	KE::TextureManager::Instance()->LoadTexture(102, "../Assets/Textures/Boxes/BlueBox.png");
	KE::TextureManager::Instance()->LoadTexture(300, "../Assets/Textures/Ballistics/cannon.png");
	KE::TextureManager::Instance()->LoadTexture(301, "../Assets/Textures/Ballistics/bullet_v2.png");
	KE::TextureManager::Instance()->LoadTexture(302, "../Assets/Textures/Ballistics/artillery_v1.png");
	KE::TextureManager::Instance()->LoadTexture(303, "../Assets/Textures/Ballistics/missile_v1.png");
	KE::TextureManager::Instance()->LoadTexture(304, "../Assets/Textures/Ballistics/fireball_v1.png");
	KE::TextureManager::Instance()->LoadTexture(305, "../Assets/Textures/Ballistics/lazer_v1.png");
	KE::TextureManager::Instance()->LoadTexture(306, "../Assets/Textures/Ballistics/grenade_v1.png");
	KE::TextureManager::Instance()->LoadTexture(500, "../Assets/Textures/Course/crate.jpg");
	KE::TextureManager::Instance()->LoadTexture(501, "../Assets/Textures/Course/woodcrate_diffuse.jpg");
	KE::TextureManager::Instance()->LoadTexture(502, "../Assets/Textures/Course/robot_diffuse.jpg");
	KE::TextureManager::Instance()->LoadTexture(503, "../Assets/Textures/Course/bunny_diffuse.jpg");
	KE::TextureManager::Instance()->LoadTexture(504, "../Assets/Textures/Course/tile_floor.jpg");

	KE::FontManager::Instance()->LoadFont(100, "ariel", "../Assets/Fonts/arial.ttf", 18);
	KE::FontManager::Instance()->LoadFont(101, "bank_gothic", "../Assets/Fonts/bank_gothic.ttf", 18);
	
	//continue adding textures for glfw tests

	KE::ErrorManager::Instance()->DisplayErrors();


	//=====Add Levels=====
	shared_ptr<SplashScreen> splashScreen { new SplashScreen() };
	splashScreen->v_InitLevel(1, wndWidth, wndHeight, KE::Color(0.0f, 0.0f, 0.0f));
	KE::Engine::Instance()->AddLevelToManager(splashScreen);
	
	shared_ptr<MainMenu> mainMenu { new MainMenu() };
	mainMenu->v_InitLevel(2, wndWidth, wndHeight, KE::Color(0.2f, 0.2f, 0.2f));
	KE::Engine::Instance()->AddLevelToManager(mainMenu);

	shared_ptr<MovingBoxes> movingBoxes { new MovingBoxes() };
	movingBoxes->v_InitLevel(3, wndWidth, wndHeight, KE::Color(0.2f, 0.2f, 0.2f));
	KE::Engine::Instance()->AddLevelToManager(movingBoxes);

	shared_ptr<Ballistics> levelBallistics { new Ballistics() };
	levelBallistics->v_InitLevel(4, wndWidth, wndHeight, KE::Color(0.2f, 0.2f, 0.2f));
	KE::Engine::Instance()->AddLevelToManager(levelBallistics);

	shared_ptr<FireworksDemo> fireworks { new FireworksDemo() };
	fireworks->v_InitLevel(5, wndWidth, wndHeight, KE::Color(0.2f, 0.2f, 0.2f));
	KE::Engine::Instance()->AddLevelToManager(fireworks);

	shared_ptr<Springs> springs { new Springs() };
	springs->v_InitLevel(6, wndWidth, wndHeight, KE::Color(0.2f, 0.2f, 0.2f));
	KE::Engine::Instance()->AddLevelToManager(springs);

	shared_ptr<Demo3D> demo3D { new Demo3D() };
	demo3D->v_InitLevel(7, wndWidth, wndHeight, KE::Color(0.2f, 0.4f, 0.5f));
	KE::Engine::Instance()->AddLevelToManager(demo3D);
	
	KE::Engine::Instance()->SetActiveLevel(1);

	KE::ErrorManager::Instance()->DisplayErrors();

	while (KE::Engine::Instance()->Running()) 
	{
		KE::Engine::Instance()->Update();
		KE::ErrorManager::Instance()->DisplayErrors();
		KE::Engine::Instance()->Render();
		KE::ErrorManager::Instance()->DisplayErrors();

		KE::WinProgram::Instance()->DisplayFPS();
	}
}
