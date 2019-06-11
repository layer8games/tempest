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
#include <Boxes/DataBases.h>
#include <Boxes/ProjectFactory.h>

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
		void v_Init(void) final;

		void v_Update(void) final;

	private:
		bool			_useOrbit;
		p_Cube   		_crate1;
		p_Cube 			_crate2;
		p_Cube 			_floor;
		p_Cube 			_robot;
		p_Cube 			_bowlingPin;
		p_Cube 			_bunny;
		p_Cube 			_light;
		F32 			_lightMovAngle;
		KE::OrbitCamera _orbitCamera;
		KE::FPSCamera   _fpsCamera;
		
	};//end Class
}//end Namespace
