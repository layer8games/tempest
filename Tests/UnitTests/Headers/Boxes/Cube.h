#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/GameObject.h>
#include <Engine/Vector4.h>
#include <Engine/Vertex.h>
#include <Engine/Color.h>
#include <Engine/Vertex.h>
#include <Engine/Timer.h>
#include <Engine/GameWindow.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

namespace Boxes
{
	class Cube : public KE::GameObject
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Cube(void);

		~Cube(void);
//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
		void v_Update(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		void InitCube(string meshFilePath);

		void InitCube(string meshFilePath, U32 shaderID);

		void InitCube(void);


	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		bool		_rotateRight;
		bool 		_rotateLeft;
		bool 		_rotateUp;
		bool 		_rotateDown;
		F32 		_angle;
		U32 		_defaultShaderID;
	};//end Class
}//end Namespace