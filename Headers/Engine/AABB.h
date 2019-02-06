#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector.h>

namespace KM = KillerMath;

namespace KillerCollisions
{
	class AABB
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		AABB(void);

		~AABB(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		inline void SetCenter(const KM::Vector& c)
		{
			_center = c;
			//Temporary code. Needs to be removed when an offical Point class is created. 
			_center[3] = 0.0f;
		}

		inline void SetCenter(F32 x, F32 y, F32 z)
		{
			_center[0] = x;
			_center[1] = y;
			_center[2] = z;
		}

		inline const KM::Vector& GetCenter(void)
		{
			return _center;
		}

		inline void SetHalfWidth(F32 w)
		{
			_halfWidth = w;
		}

		inline void SetWidth(F32 w)
		{
			_halfWidth = w / 2.0f;
		}

		inline void SetHalfHeight(F32 h)
		{
			_halfHeight = h;
		}

		inline void SetHeight(F32 h)
		{
			_halfHeight = h / 2.0f;
		}

		inline void SetHalfDepth(F32 d)
		{
			_halfDepth = d;
		}

		inline void SetDepth(F32 d)
		{
			_halfDepth = d / 2.0f;
		}

		inline void SetHalfDimensions(F32 w, F32 h, F32 d)
		{
			_halfWidth = w;
			_halfHeight = h;
			_halfDepth = d;
		}

		inline void SetDimensions(F32 w, F32 h, F32 d)
		{
			_halfWidth = w / 2.0f;
			_halfHeight = h / 2.0f;
			_halfDepth = d / 2.0f;
		}

		inline F32 GetHalfWidth(void)
		{
			return _halfWidth;
		}

		inline F32 GetWidth(void)
		{
			return _halfWidth * 2.0f;
		}

		inline F32 GetHalfHeight(void)
		{
			return _halfHeight;
		}

		inline F32 GetHeight(void)
		{
			return _halfHeight * 2.0f;
		}

		inline F32 GetHalfDepth(void)
		{
			return _halfDepth;
		}

		inline F32 GetDepth(void)
		{
			return _halfDepth * 2.0f;
		}

	private:
		KM::Vector _center;
		F32		   _halfWidth;
		F32 	   _halfHeight;
		F32 	   _halfDepth;
		
	};//end Class
}//end Namespace
