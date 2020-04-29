#pragma once

//===== Killer1 includes =====
#include "stdafx.h"
#include <Engine/Atom.h>

//===== STL includes =====
#include <cassert>

namespace Tempest
{
    class Color 
    {
    public:
        TEMPEST_API Color(void);

        TEMPEST_API explicit Color(F32 col);

        TEMPEST_API Color(F32 red, F32 green, F32 blue);

        TEMPEST_API Color(F32 red, F32 green, F32 blue, F32 alpha);

        TEMPEST_API Color(const Color& c);

        TEMPEST_API ~Color(void);

        inline const F32& operator[](int i) const
        {
            return _data[i];
        }

        inline F32& operator[](int i)
        {
            return _data[i];
        }

        inline Color& operator=(const Color& c) 
        {
            _data[0] = c[0];
            _data[1] = c[1];
            _data[2] = c[2];
            _data[3] = c[3];

            return *this;
        }
        
        inline bool HasAlpha(void) const
        {
            return _alpha;
        }

        inline void UseAlpha(bool state)
        {
            _alpha = state;
        }

        inline const F32* GetPointer(void) const 
        { 
            return _data; 
        }

        inline void Set(F32 val)
        {
            _data[0] = val;
            _data[1] = val;
            _data[2] = val;
        }

    private:
        bool _alpha;
        F32 _data[4];
    };
    typedef shared_ptr<Color> p_Color;
}//End namespace