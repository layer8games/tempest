#pragma once

#include "stdafx.h"
#include "Engine/Atom.h"
#include "Engine/ErrorManager.h"
#include "Engine/Font.h"
#include "Engine/Vector2.h"
#include "Engine/Glyph.h"
#include "Engine/Color.h"

namespace TM = TempestMath;

#include <vector>

namespace Tempest
{
    class Text
    {
    public:
        TEMPEST_API Text(void);

        TEMPEST_API explicit Text(string text);

        TEMPEST_API Text(string text, p_Font font);

        TEMPEST_API Text(string text, Font& font);

        TEMPEST_API ~Text(void);
        
        inline void SetPosition(const TM::Point2& pos)
        {
            _pos = pos;
            _UpdatePositions();
        }
 
        inline void SetPosition(F32 x, F32 y)
        {
            _pos.Set(x, y);
            _UpdatePositions();
        }
 
        TEMPEST_API void AddText(string text);

        TEMPEST_API void SetTextColor(const Color& col);

        inline string GetText(void)
        {
            return _text;
        }

        inline void SetActive(bool state)
        {
            _active = state;
            _UpdateActive();
        }

        inline void SetActive(void)
        {
            _active = true;
            _UpdateActive();
        }

        inline void SetInactive(void)
        {
            _active = false;
            _UpdateActive();
        }

        inline bool GetActive(void) const
        {
            return _active;
        }
 
        inline F32 GetWidth(void)
        {
            return _screenWidth;
        }

        TEMPEST_API void SetFont(p_Font font);

        inline void SetFont(Font& font) 
        { 
            _font = p_Font(&font); 

            // TODO: Need to update each glyph. Bug to fix later.
        }

        inline const p_Font GetFont(void)
        {
            return _font;
        }

        std::vector<shared_ptr<Glyph>> GetCharacterList(void) const
        {
            return _characterList;
        }
 
        inline void SetScale(const TM::Vector2& s)
        {
            _scale = s;
            _UpdateScales();
        }

        inline void SetScale(F32 xScale, F32 yScale)
        {
            _scale.Set(xScale, yScale);
            _UpdateScales();
        }

        inline const TM::Vector2& GetScale(void)
        {
            return _scale;
        }

        inline void SetColor(const Color& c)
        {
            _color = c;
            _UpdateColors();
        }
 
        inline void SetColor(F32 r, F32 g, F32 b)
        {
            _color[0] = r;
            _color[1] = g;
            _color[2] = b;

            _UpdateColors();
        }

        inline const Color& GetColor(void)
        {
            return _color;
        }

    private:
        TEMPEST_API void _UpdatePositions(void);
 
        TEMPEST_API void _UpdateActive(void);

        TEMPEST_API void _UpdateScales(void);

        TEMPEST_API void _UpdateColors(void);

        TEMPEST_API void _UpdateGlyphData(U32 index);

        void _CreateCharacterList(void);

        bool _active;	
        F32 _screenWidth;
        TM::Point2 _pos;		
        string _text;		
        p_Font _font;		
        std::vector<shared_ptr<Glyph>> _characterList;
        TM::Vector2 _scale;		
        Color _color;		
    };//End class
    typedef shared_ptr<Text> p_Text;
}//End namespace