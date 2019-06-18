#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/GameObject.h>
#include <Engine/RigidBody2D.h>
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

//===== Boxes Includes =====
#include <Boxes/Payload.h>

namespace Boxes
{
	typedef std::vector<shared_ptr<Payload>> PayloadPool;

	class Firework : public KE::GameObject
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

		void Reset(U32 rule);

		void AddPayload(shared_ptr<Payload> payload)
		{
			_pool.push_back(payload);
		}

	private:
		PayloadPool 					 _pool;
		U32					 			 _levelID;
		U32 				 			 _maxSize;
		KM::Matrix4 					 _projection;
	};//end Class
	typedef shared_ptr<Firework> p_Firework;
}//end Namespace
