#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/Controller.h>
#include <Engine/Engine.h>
#include <Engine/GameObject.h>
#include <Engine/Timer.h>
#include <Engine/Texture.h>
#include <Engine/OrbitCamera.h>
#include <Engine/FPSCamera.h>
#include <Engine/Font.h>
#include <Engine/ShaderManager.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

#include <Boxes/Cube.h>

namespace Boxes
{
//==========================================================================================================================
//
//Level
//
//==========================================================================================================================

	class Demo3D : public KE::Level
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Demo3D(void);

		~Demo3D(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void v_InitLevel(U32 id, S32 w, S32 h, const KE::Color& c) final;

		void v_Update(void) final;

	private:
		bool			_useOrbit;
		Cube   			_crate1;
		Cube 			_crate2;
		Cube 			_floor;
		Cube 			_robot;
		Cube 			_bowlingPin;
		Cube 			_bunny;
		Cube 			_light;
		F32 			_lightMovAngle;
		KE::OrbitCamera _orbitCamera;
		KE::FPSCamera   _fpsCamera;
		
	};//end Class
}//end Namespace
