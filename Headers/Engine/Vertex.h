#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Vector4.h>
#include <Engine/Point3.h>
#include <Engine/Color.h>

namespace TM = TempestMath;

namespace Tempest
{
///	Helper struct to keep track of UV coordinates for a texture. 
    struct TexCoord
    {
        F32 u;	///< U coordinate. Should only be between 0 and 1. Matches to the x in a texture.
        F32 v;	///< V coordinate. Should only be between 0 and 1. Matches to the y in a texture.

///	Sets u and v to 0.
        TexCoord(void)
        : u(0.0f), v(0.0f)
        {  }

///	Sets up the start values for the coords. 
///	\param s is the value for u.
///	\param t is the value for v. 
        TexCoord(F32 s, F32 t)
        : u(s), v(t)
        {  }
    };

///	Helper structure to keep track of all the value OpenGL needs for a vertex for rendering.
    struct Vertex
    {
        TM::Point3 position;	///< Position of the vertex, in model space.
        TM::Vector4 normal;		///< The normal of the vertext in model space.
        TexCoord   texCoord;	///< If there is an attached texture, this holds its information.
        Color 	   color;		///< Color values for the vertext.

///	Sets all values to 0. 
        Vertex(void)
        : position(0.0f), normal(0.0f), texCoord(0.0f, 0.0f), color()
        {  }

///	Sets up the position, everything else is set to 0. 
///	\param pos is the starting position for the vertext. Should be in model space. 
        Vertex(TM::Point3 pos)
        : position(pos), normal(0.0f), texCoord(0.0f, 0.0f), color()
        {  }

///	Sets up the starting position and color. Everything else is set to 0. 
///	\param pos is the starting position in model space. 
///	\param color is the starting color. 
        Vertex(const TM::Point3& pos, Color col)
        : position(pos), normal(0.0f), texCoord(0.0f, 0.0f), color(col)
        {  }

///	Sets the position, and texture coords. Everything else is set to 0. 
///	\param pos is the starting position, in model space. 
///	\param u sets the u value in a texture coord.
///	\param v sets the v value in a texture coord. 
        Vertex(const TM::Point3& pos, F32 u, F32 v)
        : position(pos), normal(0.0f), texCoord(u, v), color()
        {  }

///	Sets the position and surface normal, in model space. 
///	\param pos is the starting position in model space. 
///	\param norm is the surface normal. Should be normalized, in model space.  
        Vertex(const TM::Point3& pos, const TM::Vector4& norm)
        : position(pos), normal(norm), texCoord(0.0f, 0.0f), color()
        {  }

///	Sets the position, surface normal, and texture coords. Color is set to default. 
///	\param pos is the starting position in model space. 
///	\param norm is the surface normal. Should be normalized, in model space. 
///	\param u sets the u value in a texture coord. 
///	\param v sets the v values in a texture coord.  
        Vertex(const TM::Point3& pos, const TM::Vector4& norm, F32 u, F32 v)
        : position(pos), normal(norm), texCoord(u, v), color()
        {  }	
    };
}//end Namespace