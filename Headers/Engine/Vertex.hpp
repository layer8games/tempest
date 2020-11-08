#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/Vector4.h"
#include "Engine/Color.h"

namespace TM = TempestMath;

namespace Tempest
{
    struct TexCoord
    {
        F32 u;
        F32 v;

        TexCoord(void)
        : u(0.0f), v(0.0f)
        {  }

        TexCoord(F32 s, F32 t)
        : u(s), v(t)
        {  }
    };

    struct Vertex
    {
        TM::Point4 position;
        TM::Vector4 normal;	
        TexCoord   texCoord;
        Color 	   color;	

        Vertex(void)
        : position(0.0f), normal(0.0f), texCoord(0.0f, 0.0f), color()
        {  }

        Vertex(TM::Point4 pos)
        : position(pos), normal(0.0f), texCoord(0.0f, 0.0f), color()
        {  }

        Vertex(const TM::Point4& pos, Color col)
        : position(pos), normal(0.0f), texCoord(0.0f, 0.0f), color(col)
        {  }

        Vertex(const TM::Point4& pos, F32 u, F32 v)
        : position(pos), normal(0.0f), texCoord(u, v), color()
        {  }

        Vertex(const TM::Point4& pos, const TM::Vector4& norm)
        : position(pos), normal(norm), texCoord(0.0f, 0.0f), color()
        {  }

        Vertex(const TM::Point4& pos, const TM::Vector4& norm, F32 u, F32 v)
        : position(pos), normal(norm), texCoord(u, v), color()
        {  }	
    };
}//end Namespace