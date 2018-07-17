#include <Engine/Model.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
Model::Model(void) 
: 
_numVertices(0), 
_vertices(),
_indices(),
_shaderProgram(0),
_scale(1.0f, 1.0f, 1.0f)
{  }

Model::Model(const Model& m)
:
_numVertices(m.VertexCount()),
_vertices(m.GetVertices()),
_indices(m.GetIndices()),
_scale(m.GetScale()),
_shaderProgram(m.GetShader())
{  }

Model::Model(std::vector<Vertex3D> vertices, std::vector<U16> indices) 
: 
_numVertices(0), 
_vertices(vertices),
_indices(indices),
_shaderProgram(0)
{  }

Model::~Model(void)
{  }

//==========================================================================================================================
//
//Model Functions
//
//==========================================================================================================================
void Model::AddIndex(std::vector<U16> i)
{
	_indices.insert(_indices.end(), i.begin(), i.end());
	_numVertices += i.size();
}

void Model::LoadModel(string filepath)
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
	std::vector<KM::Vector3> vertexPositions;

	for(int i = 0; i < vertexData.size(); i += 3)
	{
		vertexPositions.push_back(KM::Vector3(vertexData[i], vertexData[i+1], vertexData[i+2]));
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
			ErrorManager::Instance()->SetError(EC_Engine, "Model::LoadModel, unable to load color from matrial");
		}
	}
	
	//Get indices
	data = root_node->first_node("library_geometries")->first_node("geometry")->first_node("mesh")->first_node("polylist");

	for(rapidxml::xml_node<>* i = data; i; i = i->next_sibling("polylist"))
	{
		string id = i->first_attribute("material")->value();

		Color mat = materials.find(id)->second;
		data = i->first_node("p");

		std::vector<U16> indices = _SplitU16(data->value(), ' ');

		std::vector<U16> vertexIndices;
		//std::vector<U16> normalIndices;
		//split up the data
		for(int i = 0; i < indices.size(); i+=2)
		{
			vertexIndices.push_back(indices[i]);
			//normalIndices.push_back(indices[i+1]);
		}

		//Get only unique values for vertex creation
		std::vector<U16> vertexNeeded = vertexIndices;
		std::sort(vertexNeeded.begin(), vertexNeeded.end());
		auto it = std::unique(vertexNeeded.begin(), vertexNeeded.end());
		vertexNeeded.resize(std::distance(vertexNeeded.begin(), it));

		for(auto i : vertexNeeded)
		{
			Vertex3D vert;
			vert.position = vertexPositions[i];
			vert.color = mat;

			_vertices.push_back(vert);
		}

		AddIndex(vertexIndices);
	}
}

void Model::AddIndex(U16 index)
{
	_indices.push_back(index);
	++_numVertices;
}

void Model::ClearIndices(void)
{
	_indices.clear();
}

void Model::AddVertex(const Vertex3D& vert)
{
	_vertices.push_back(vert);
}

void Model::AddVertex(const KM::Vector3& pos, const Color& color)
{
	Vertex3D vert;
	vert.position = pos; 
	vert.color = color;

	_vertices.push_back(vert);
}

//==========================================================================================================================
//Private
//==========================================================================================================================
std::vector<U16> Model::_SplitU16(string text, char delim) const
{
	std::vector<U16> data;
	std::stringstream stream(text);
	string item;

	while(std::getline(stream, item, delim))
	{
		data.push_back(static_cast<U16>(std::stoi(item.c_str())));
	}

	return data;
}

std::vector<F32> Model::_SplitF32(string text, char delim) const
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