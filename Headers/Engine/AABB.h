#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Point.h>
#include <Engine/Vector3.h>

namespace TM = TempestMath;

namespace TempestCollisions
{
///	An Axis Alligned Bounding Box used to do rough collission detection. It used a center, half-lengths set up to compute 
///	the box. It will support many kinds of collision tests eventually, but for now it only support AABB vs AABB tests.
	class AABB
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
///	Sets all values to 0.
		TEMPEST_API AABB(void);

///	Sets the center up and the dimensions. Dimensions are sent in as full, and then halved. 
///	\param center is the location of the center of the AABB.
///	\param w is the full width of the AABB. It is divided by 2 to get the half width that is stored. 
///	\param h is the full height of the AABB. It is divided by 2 to get the half height that is stored. 
///	\param d is the full depth of the AABB. It is divided by 2 to get the half depth that is stored. 
		TEMPEST_API AABB(const TM::Point& center, F32 w, F32 h, F32 d);

		//TODO: Consider adding constructor that will combine 2 AABB's. 

///	No implemenation. 
		TEMPEST_API ~AABB(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
///	Test if this and other are colliding or not. Two AABB's must overlap on all 3 axis. This is tested by comparing the
///	difference between the position on an axis with the sum of the length of the coorespoding axis. For example, for the x axis, 
///	(a.center.x - b.center.x) > (a.halfWidth + b.halfWidth). If this is true, we can move onto the next axis. If any axis if false,
///	then they do not intersect.
///	\param other is another AABB that we are testing against.
		TEMPEST_API bool TestCollision(const AABB& other) const;

		/// Test if this and other are colliding. This uses an arbitrary point.
		/// \param other is a point in world space to test with
		TEMPEST_API bool TestCollision(const TM::Point& other) const;

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
///	Sets the location of the center of the sphere. This is the position in local space for the object it encompasses. 
///	\param c is the new center. The w component is set to 0.
		inline void SetCenter(const TM::Point& c)
		{
			_center = c;
		}

///	Sets the location of the center of the sphere. This is the position in local space for the object it encompasses. 
///	\param x is the new x value of the center. 
///	\param y is the new y value of the center. 
///	\param z is the new z value of the center. 
		inline void SetCenter(F32 x, F32 y, F32 z)
		{
			_center[0] = x;
			_center[1] = y;
			_center[2] = z;
		}

///	 Returns the center of the AABB.
		inline const TM::Point& GetCenter(void) const
		{
			return _center;
		}

///	Sets the half width extent of the AABB.
///	\param w is the new half width. 
		inline void SetHalfWidth(F32 w)
		{
			_halfScale[x] = w;
		}

///	Sets the full width extent of the AABB. Because this is internally stored as a half width, it is 
///	divided by 2 when it is set. 
///	\param w is the new full width.
		inline void SetWidth(F32 w)
		{
			_halfScale[x] = w / 2.0f;
		}

///	Returns the half width of the AABB. 
		inline F32 GetHalfWidth(void) const
		{
			return _halfScale[x];
		}

///	Returns the full width of the AABB. Because this is stored as a half width, it is multiplied by 2
///	before it is returned. 
		inline F32 GetWidth(void) const
		{
			return _halfScale[x] * 2.0f;
		}

///	Sets the half height extent of the AABB.
///	\param h is the new half height. 
		inline void SetHalfHeight(F32 h)
		{
			_halfScale[y] = h;
		}

///	Sets the full height extent of the AABB. Because this is internally stored as a half width, it is 
///	divided by 2 when it is set.
///	\param h is the new full height.
		inline void SetHeight(F32 h)
		{
			_halfScale[y] = h / 2.0f;
		}

///	Returns the half height extent of the AABB. 
		inline F32 GetHalfHeight(void) const
		{
			return _halfScale[y];
		}

///	Returns the full height extent of the AABB. Because internally it is stored as a half height, it is
///	multiplied by 2 before it is returned. 
		inline F32 GetHeight(void) const
		{
			return _halfScale[y] * 2.0f;
		}

///	Sets the half depth extent of the AABB.
///	\param d is the new half depth extent. 
		inline void SetHalfDepth(F32 d)
		{
			_halfScale[z] = d;
		}

///	Sets the full depth of the extent of the AABB. Because this is internally stored as a half depth, it is 
///	divided before it is set. 
///	\param d is the new full depth extent. 
		inline void SetDepth(F32 d)
		{
			_halfScale[z] = d / 2.0f;
		}

///	 Returns the half depth extent of the AABB. 
		inline F32 GetHalfDepth(void) const
		{
			return _halfScale[z];
		}

///	Returns the full depth extent of the AABB. Because internally this is stored as a half, it is multiplied
///	before it is returned. 
		inline F32 GetDepth(void) const
		{
			return _halfScale[z] * 2.0f;
		}

///	Sets all of the half extents of the AABB. 
///	\param w is the new half width extent. 
///	\param h is the new half height extent. 
///	\param d is the new half depth extent. 
		inline void SetHalfDimensions(F32 w, F32 h, F32 d)
		{
			_halfScale[x] = w;
			_halfScale[y] = h;
			_halfScale[z] = d;
		}

///	Sets the new half extent of the AABB 
///	\param scale is the new extent to be used. 
		inline void SetHalfDimensions(const TM::Vector3& scale)
		{
			_halfScale = scale;
		}

///	 Sets all of the full extents of the AABB. Because these are all stored as halves, each one is divided
///	 by 2 before they are set. 
///	 \param w is the new full width extent. 
///	 \param h is the new full height extent. 
///	 \param d is the new full depth extent. 
		inline void SetDimensions(F32 w, F32 h, F32 d)
		{
			_halfScale[x] = w / 2.0f;
			_halfScale[y] = h / 2.0f;
			_halfScale[z] = d / 2.0f;
		}

///	Sets the extent of the AABB. Because these are half values, the input is divided by half.
///	\param scale is the new extent.  
		inline void SetDimensions(const TM::Vector3& scale)
		{
			_halfScale = scale / 2.0f;
		}

	private:
		TM::Point   _center;		///< Center location of the AABB. This is the posistion represented in world space of the object that holds it. 
		TM::Vector3 _halfScale;		///< The half sizes of the bounding volume along the 3 axies, x, y and z.	 
		
	};//end Class
	typedef shared_ptr<AABB> p_AABB;
}//end Namespace
