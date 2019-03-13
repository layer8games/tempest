/*========================================================================
A basic Object that will demo fireworks that are created procedurally though
the logic of the physics engine. The bulk of this code came from teh book
Game Physics Engine Development by Ian Millington. I have altered the 
code to fit my engine, but this is the example given in chapter 4

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/
#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/GameObject.h>
#include <Engine/Particle.h>
#include <Engine/Random.h>
#include <Engine/LevelManager.h>
#include <Engine/Level.h>
#include <Engine/Timer.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>
#include <Engine/Matrix4.h>

namespace KE = KillerEngine;
namespace KP = KillerPhysics;

//===== STL includes =====
#include <vector>

namespace Boxes
{
	struct Payload
	{
		KP::Particle particle;
		F32 timeAlive;
		U32 spawnNewRule;
		bool spawnNew;
	};

	typedef std::vector<shared_ptr<Payload>> PayloadPool;

	class Firework : public KP::Particle
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		Firework(void);

		Firework(U32 levelID, U32 size);

		~Firework(void);
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
		inline void SetPool(PayloadPool pool)
		{
			_pool = pool;
		}

		inline void SetMaxSize(U32 size)
		{
			_maxSize = size;
		}

		inline U32 GetMaxSize(void)
		{
			return _maxSize;
		}

		inline void SetLevelID(U32 id)
		{
			_levelID = id;
		}

		inline U32 GetLevelID(void)
		{
			return _levelID;
		}

		inline void SetProjection(const KM::Matrix4 projection)
		{
			_projection = projection;
		}

		void InitPayload(U32 rule, KM::Point pos);

		void Reset(U32 rule);

	private:
		PayloadPool 					 _pool;
		U32					 			 _levelID;
		U32 				 			 _maxSize;
		KM::Matrix4 					 _projection;
	};//end Class
}//end Namespace
