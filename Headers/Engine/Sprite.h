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
#pragma once

//=====Killer1 inlucdes=====
#include <Engine/Atom.h>
#include <Engine/Vector2.h>
#include <Engine/Texture.h>
#include <Engine/TextureManager.h>
#include <Engine/ErrorManager.h>
#include <Engine/Color.h>
#include <Engine/CharacterData.h>
#include <Engine/Shader.h>

namespace KM = KillerMath;

//=====STL Includes=====
#include <vector>

namespace KillerEngine 
{	
	class Sprite 
	{	
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		Sprite(void);

		~Sprite(void);

//==========================================================================================================================
//
//Accessors
//
//==========================================================================================================================
		const U32 GetTextureID(void)  const
		{ 
			return _textureID; 
		}

		void SetUVs(const KM::Vector2& bottomTop, const KM::Vector2& leftRight)
		{
			_bottomTop = bottomTop;
			_leftRight = leftRight;
		}

		inline const KM::Vector2& GetUVBottomTop(void) const
		{ 
			return _bottomTop; 
		}

		inline const KM::Vector2& GetUVLeftRight(void) const
		{ 
			return _leftRight; 
		}

		void SetCharData(CharacterData data);

		inline const CharacterData& GetCharData(void) const
		{
			return _characterData;
		}

		inline const Color& GetColor(void) const
		{
			return _color;
		}

		void SetColor(const Color& col);

		void SetColor(F32 red, F32 green, F32 blue, F32 alpha=1.0f);

		inline const GLuint GetShader(void) const
		{
			return _shaderProgram;
		}

		inline void SetShader(GLuint shader)
		{
			_shaderProgram = shader;
		}

		inline void SetVAO(GLuint vao)
		{
			_vao = vao;
		}

		inline GLuint GetVAO(void)
		{
			return _vao;
		}

		inline U32 GetVertexCount(void)
		{
			return _vertexCount;
		}
 
//==========================================================================================================================
//
//Operator Overloads
//
//==========================================================================================================================
		Sprite& operator=(const Sprite& S);

		Sprite& operator=(const Sprite* S);

		Sprite& operator=(shared_ptr<Sprite> S);
		
//==========================================================================================================================
//
//Sprite Functions 	 	
//
//==========================================================================================================================
		void SetTexture(U32 tID, const F32 top, const F32 bottom, const F32 right, const F32 left);

		//void Render(const KM::Vector2& pos, F32 w, F32 h, const Color& col);

		//static void StaticDraw(S32 count, std::vector<F32> vertices, std::vector<F32> colors, std::vector<F32> dimensions, std::vector<F32> bottomTop, std::vector<F32>leftRight);

	private:
		KM::Vector2 		 _bottomTop;
		KM::Vector2 		 _leftRight;
		U32					 _textureID;
		CharacterData   	 _characterData;
		Color 				 _color;
		GLuint 		 		 _shaderProgram;
		GLuint				 _vao;
		GLuint				 _vbo;
		U32 				 _vertexCount;

//==========================================================================================================================
//
//Private functions
//
//==========================================================================================================================
		void _InitShader(void);

	};
}//End namespace