#include <Engine/Sprite.h>

using namespace Tempest;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Sprite::Sprite(void)
{  }

Sprite::~Sprite(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Sprite::v_Render(const TM::Matrix4& worldTransform)
{
	/*
		TODO:: I do not know if you need to keep setting uniforms, of if they are premanent. This will affect how the GameObject
		stores color, or who should store the color. Research and implement with Tempest issue #64

		if(_isSprite)
		{
			SetUniform("sprite_color", _color);
		}
	*/
	DefaultRender(worldTransform);
}

void Sprite::v_InitBuffers(void)
{
	_vertices.clear();

	TM::Point topRight(1.0f, 1.0f, 0.0f);
	TM::Point topLeft(-1.0f, 1.0f, 0.0f);
	TM::Point bottomRight(1.0f, -1.0f, 0.0f);
	TM::Point bottomLeft(-1.0f, -1.0f, 0.0);

	TM::Point top(0.0f, 0.5f);

	AddVertex(Vertex(topLeft, 0.0f, 0.0f));
	AddVertex(Vertex(topRight, 1.0f, 0.0f));
	AddVertex(Vertex(bottomRight, 1.0f, 1.0f));

	AddVertex(Vertex(topLeft, 0.0f, 0.0f));
	AddVertex(Vertex(bottomRight, 1.0f, 1.0f));
	AddVertex(Vertex(bottomLeft, 0.0f, 1.0f));

	DefaultInitBuffers();

	_shader = ShaderManager::Instance()->GetShader(SPRITE);
}