#include <Boxes/Cube.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Cube::Cube(void)
:
_rotateRight(true),
_rotateLeft(false),
_rotateUp(false),
_rotateDown(false),
_angle(0),
_defaultShaderID(101)
{
	std::vector<KE::ShaderData> shaderData;

	KE::ShaderData vs;
	vs.filePath = "../Assets/Shaders/lighting_directional_vertex.glsl";
	vs.type = KE::ShaderType::VERTEX;
	shaderData.push_back(vs);

	KE::ShaderData fs;
	fs.filePath = "../Assets/Shaders/lighting_directional_fragment.glsl";
	fs.type = KE::ShaderType::FRAGMENT;
	shaderData.push_back(fs);

	KE::ShaderManager::Instance()->LoadShader(_defaultShaderID, shaderData);
}

Cube::~Cube(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Cube::v_Update(void)
{  }

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void Cube::InitCube(string filePath)
{
	GameObject::SetShader(KE::ShaderManager::Instance()->GetShader(_defaultShaderID));	

	GameObject::LoadOBJ(filePath);
}

void Cube::InitCube(string meshFilePath, U32 shaderID)
{
	GameObject::SetShader(KE::ShaderManager::Instance()->GetShader(shaderID));

	GameObject::LoadOBJ(meshFilePath);
}

void Cube::InitCube(void)
{
	GameObject::SetShader(KE::ShaderManager::Instance()->GetShader(_defaultShaderID));	

	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, 1.0f, 1.0f), 0.0f, 1.0f)); 	//Front Top Left        0
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, 1.0f, 1.0f), 1.0f, 1.0f)); 	//Front Top Right 		1 
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, -1.0f, 1.0f), 1.0f, 0.0f));	//Front Bottom Right	2
	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, -1.0f, 1.0f), 0.0f, 0.0f));	//Front Bottom Left		3

	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, 1.0f, -1.0f), 0.0f, 1.0f)); 	//Back Top Left        	4
	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, 1.0f, -1.0f), 1.0f, 1.0f)); 	//Back Top Right 		5 
	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, -1.0f, -1.0f), 1.0f, 0.0f));	//Back Bottom Right		6
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, -1.0f, -1.0f), 0.0f, 0.0f));	//Back Bottom Left		7

	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, 1.0f, 1.0f), 0.0f, 1.0f)); 	//Right Top Left        8
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, 1.0f, -1.0f), 1.0f, 1.0f)); 	//Right Top Right 		9 
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, -1.0f, -1.0f), 1.0f, 0.0f));	//Right Bottom Right	10
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, -1.0f, 1.0f), 0.0f, 0.0f));	//Right Bottom Left		11

	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, 1.0f, -1.0f), 0.0f, 1.0f)); 	//Left Top Left        	12
	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, 1.0f, 1.0f), 1.0f, 1.0f)); 	//Left Top Right 		13
	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, -1.0f, 1.0f), 1.0f, 0.0f));	//Left Bottom Right		14
	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, -1.0f, -1.0f), 0.0f, 0.0f));	//Left Bottom Left		15

	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, -1.0f, 1.0f), 0.0f, 1.0f)); 	//Bottom Top Left       16
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, -1.0f, 1.0f), 1.0f, 1.0f)); 	//Bottom Top Right 		17 
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, -1.0f, -1.0f), 1.0f, 0.0f));	//Bottomn Bottom Right	18
	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, -1.0f, -1.0f), 0.0f, 0.0f));	//Bottomn Bottom Left	19

	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, 1.0f, -1.0f), 0.0f, 1.0f)); 	//Top Top Left        	20
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, 1.0f, -1.0f), 1.0f, 1.0f)); 	//Top Top Right 		21
	GameObject::AddVertex(KE::Vertex(KM::Point(1.0f, 1.0f, 1.0f), 1.0f, 0.0f));	//Top Bottom Right		22
	GameObject::AddVertex(KE::Vertex(KM::Point(-1.0f, 1.0f, 1.0f), 0.0f, 0.0f));	//Top Bottom Left		23

	GameObject::SetIndices(std::vector<U32>
	{
		0, 1, 2, //Front
		0, 2, 3,
		4, 5, 6, //Back
		4, 6, 7,
		8, 9, 10, //Right
		8, 10, 11,
		12, 13, 14, //Left
		12, 14, 15,
		16, 17, 18, //Bottom
		16, 18, 19,
		20, 21, 22, //Top
		20, 22, 23
	});

	v_InitBuffers();	
}