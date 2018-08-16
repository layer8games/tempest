#include <Engine/GameObject.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Static Member
//
//==========================================================================================================================
U32 GameObject::_nextID = 1;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
GameObject::GameObject(void)
:
_ID(_nextID),
_active(true),
_position(0.0f),
_shader(),
_numIndices(0),
_vertices(),
_indices(),
_vao(0),
_vbo{0}
{
	++_nextID;

	glGenVertexArrays(1, &_vao);
	glGenBuffers(NUM_VBO, _vbo);
}

GameObject::GameObject(const GameObject& obj)
:
_ID(obj.GetID()),
_active(obj.GetActive()),
_position(obj.GetPosition()),
_shader(obj.GetShader()),
_vertices(obj.GetVertices()),
_indices(obj.GetIndices()),
_vao(obj.GetVAO())
{
	glGenBuffers(NUM_VBO, _vbo);
}

GameObject::~GameObject(void)
{
	glDeleteBuffers(NUM_VBO, _vbo);
	glDeleteVertexArrays(1, &_vao);
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
//==========================================================================================================================
//v_Render
//==========================================================================================================================
void GameObject::v_Render(void)
{
	_shader.Use();
	BindVAO();

	glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

//==========================================================================================================================
//v_InitVertexData
//==========================================================================================================================
void GameObject::v_InitVertexData(void)
{
	if(_vertices.size() <= 0)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "GameObject::v_InitVertexData. No Vertices added to GameObject before init was called.");
	}
	else if(_indices.size() <= 0)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "GameObject::v_InitVertexData. No indices added to GameObject before init was called.");
	}

	std::vector<F32> vertPosition;
	std::vector<F32> vertTexCoords;

	for(auto i : _vertices)
	{
		vertPosition.push_back(i.position[0]);
		vertPosition.push_back(i.position[1]);
		vertPosition.push_back(i.position[2]);
		vertPosition.push_back(i.position[3]);

		vertTexCoords.push_back(i.uCoord);
		vertTexCoords.push_back(i.vCoord);
	}

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[VERTEX_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertPosition.size()), &vertPosition[0], GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(VERTEX_POS);

/*	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEX_COORD_BUFFER]);
	glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertTexCoords.size()), &vertTexCoords[0], GL_STATIC_DRAW);
	glVertexAttribPointer(TEX_COORD_POS, 2, GL_FLOAT, GL_FALSE, 0 , NULL);
	glEnableVertexAttribArray(TEX_COORD_POS);
*/

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[INDEX_BUFFER]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(U32) * _indices.size()), &_indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
void GameObject::LoadMesh(string filepath)
{
	std::ifstream file(filepath);
	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	//xml file must be 0 terminating
	buffer.push_back('\0');

	file.close();

	rapidxml::xml_document<char> doc;
	doc.parse<0>(&buffer[0]);

	//Set root node
	rapidxml::xml_node<>* root_node = doc.first_node("COLLADA");

	//Get to geomtery data node
	rapidxml::xml_node<>* data = root_node->first_node("library_geometries")->first_node("geometry")->first_node("mesh")->first_node("source")->first_node("float_array");

	//capture data
	std::vector<F32> vertexData = _SplitF32(data->value(), ' ');
	std::vector<KM::Vector> vertexPositions;

	for(U32 i = 0; i < vertexData.size(); i += 3)
	{
		vertexPositions.push_back(KM::Vector(vertexData[i], vertexData[i+1], vertexData[i+2]));
	}

//===== TO DO =====
//Will need to be able to capture normal data. Here is the code that can do that.
//I am just not sure what to do with that code yet. 
/*
	data = root_node->first_node("library_geometries")->first_node("geometry")->first_node("mesh")->first_node("source")->
		   next_sibling("source")->first_node("float_array");

	std::vector<F32> normals = _SplitF32(data->value(), ' ');
*/
	
	//Get Materials
	std::map<string, Color&> materials;

	data = root_node->first_node("library_effects")->first_node("effect");
	rapidxml::xml_node<>* mat_id = root_node->first_node("library_materials")->first_node("material");

	for(rapidxml::xml_node<>* i = data; i; i = i->next_sibling("effect"))
	{
		data = i->first_node("profile_COMMON")->first_node("technique")->first_node("phong")->first_node("diffuse")->first_node("color");

		std::vector<F32> values = _SplitF32(data->value(), ' ');

		string id = mat_id->first_attribute("id")->value();
		mat_id = mat_id->next_sibling("material");

		materials.insert({id, Color(values[0], values[1], values[2], values[3])});

		if(materials.find(id) == materials.end())
		{
			ErrorManager::Instance()->SetError(EC_Engine, "GameObject::LoadMesh, unable to load color from matrial");
		}
	}
	
	//Get indices
	data = root_node->first_node("library_geometries")->first_node("geometry")->first_node("mesh")->first_node("polylist");

	for(rapidxml::xml_node<>* i = data; i; i = i->next_sibling("polylist"))
	{
		string id = i->first_attribute("material")->value();

		Color mat = materials.find(id)->second;
		data = i->first_node("p");

		std::vector<U32> indices = _SplitU32(data->value(), ' ');

		std::vector<U32> vertexIndices;
		//std::vector<U32> normalIndices;
		//split up the data
		for(U32 i = 0; i < indices.size(); i+=2)
		{
			vertexIndices.push_back(indices[i]);
			//normalIndices.push_back(indices[i+1]);
		}

		//Get only unique values for vertex creation
		std::vector<U32> vertexNeeded = vertexIndices;
		std::sort(vertexNeeded.begin(), vertexNeeded.end());
		auto it = std::unique(vertexNeeded.begin(), vertexNeeded.end());
		vertexNeeded.resize(std::distance(vertexNeeded.begin(), it));

		for(auto i : vertexNeeded)
		{
			Vertex vert;
			vert.position = vertexPositions[i];
			vert.color = mat;

			AddVertex(vert);
		}

		SetIndices(vertexIndices);
	}
}

//==========================================================================================================================
//Private
//==========================================================================================================================
std::vector<U32> GameObject::_SplitU32(string text, char delim) const
{
	std::vector<U32> data;
	std::stringstream stream(text);
	string item;

	while(std::getline(stream, item, delim))
	{
		data.push_back(static_cast<U32>(std::stoi(item.c_str())));
	}

	return data;
}

std::vector<F32> GameObject::_SplitF32(string text, char delim) const
{
	std::vector<F32> data;
	std::stringstream stream(text);
	string item;

	while(std::getline(stream, item, delim))
	{
		data.push_back(strtof(item.c_str(), nullptr));
	}

	return data;
}