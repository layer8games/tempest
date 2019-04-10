#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>

namespace KillerCollisions 
{
	template<class PhysicsObject>
	struct PotentailParticleContact
	{
		PhysicsObject* obj[2];
	};

	template<class BoundingVolume, class PhysicsObject>
	class BVHNode
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		BVHNode(void)
		:
		_volume(),
		_children{nullptr, nullptr},
		_obj(nullptr)
		{  }

		~BVHNode(void)
		{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		inline bool IsLeaf(void) const
		{
			return (_obj != nullptr);
		}

	private:
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================
		BoundingVolume  			_volume;
		BVHNode* 					_children[2];
		PhysicsObject* 				_obj;
		
	};//end Class
}//end Namespace
