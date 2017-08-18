/*========================================================================
The Sprite, or rendering cell is the basic Geometric perimitive that any
game object or entity that is to be rendered will have. It will be the 
OGL verticies that make up the position on the screen. While it will
never be called on its own, it will be part of the rendered game objects.

Based on which RenderAs* function is call, the cell is be rendered as the 
called primitive. The Sprite is not responsible for setting this up, the 
Renderer is. The Sprite will just need to get its position to the Renderer
and the Renderer will set up all the Vec for OGL, and will then store
them in a container until the scene is drawn. 

The Sprite will also hold the texture information, once that is added to the
system. Basically it will hold all the data that needs to be given to the
Renderer in order for the Renderer to give that information to OGL. 

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef SPRITE_H
#define SPRITE_H

//=====Killer1 inlucdes=====
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/Texture.hpp>
#include <Engine/Renderer.h>
#include <Engine/ErrorManager.h>

namespace KM = KillerMath;

//=====OGL includes=====
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/wglext.h>

//=====STD includes=====
#include <vector>

namespace KillerEngine 
{

//=====Foreward delcaration=====
	class Renderer;

	class Sprite 
	{	
		public:
//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
			void SetWidth(F32 w)  
			{ 
				width = w;
				//v_SetVertexPositions(); 
			}

			F32 GetWidth(void) { return width; }

			void SetHeight(F32 h) 
			{ 
				height = h; 
				//v_SetVertexPositions();
			}

			F32 GetHeight(void) { return height; }

			void SetDimensions(F32 w, F32 h) 
			{ 
				width = w; 
				height = h; 
				//v_SetVertexPositions();
			}			

			void SetPosition(KM::Vector2& pos) { position = pos; }

			KM::Vector2& GetPosition(void) { return position; }

			void SetColor(Col& col) { color = col; }

			Col& GetColor(void) { return color; }

			U32 GetTextureID(void) { return textureID; }

			void SetUVs(KM::Vector2& bottomTop, KM::Vector2& leftRight)
			{
				_bottomTop = bottomTop;
				_leftRight = leftRight;
			}

			KM::Vector2& GetUVBottomTop(void) { return _bottomTop; }

			KM::Vector2& GetUVLeftRight(void) { return _leftRight; }

 
//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		Sprite& operator=(Sprite& sprite) 
		{
			width = sprite.GetWidth();
			height = sprite.GetHeight();
			SetPosition(sprite.GetPosition());
			SetColor(sprite.GetColor());

			return *this;
		}
		
//==========================================================================================================================
//
//Virtual
//
//==========================================================================================================================
		virtual void v_RenderSprite(void)=0;
		
		virtual void SetTexture(U32 tID, const F32 top, const F32 bottom, const F32 right, const F32 left)
		{
			textureID = tID;
			_bottomTop = KM::Vector2(bottom, top);
			_leftRight  = KM::Vector2(left, right);
		}

		virtual GLuint v_GetShader(void)=0;

//==========================================================================================================================
//
//Sprite Functions 	 	
//
//==========================================================================================================================

	private:
		KM::Vector2 			 _bottomTop;
		KM::Vector2 			 _leftRight;
		F32				 width;
		F32				 height;
		U32				 textureID;
		KM::Vector2			 position;
		Col			 	 color;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		protected:
		Sprite(void);

		Sprite(const F32 width, const F32 height);

		Sprite(const F32 width, const F32 height, Col& col);											      

		Sprite(const F32 width, const F32 height, U32 tID);													     

		Sprite(const F32 width, const F32 height, Col& col, U32 tID);

		virtual void v_InitShader(void)=0;																   

	};
}//End namespace

#endif