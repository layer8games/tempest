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
_activeRender(true),
_meshLoaded(false),
_position(0.0f),
_scale(1.0f),
_shader(),
_numIndices(0),
_vertices(),
_indices(),
_vao(0),
_vbo{0},
_uvList()
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
_vao(obj.GetVAO()),
_uvList(obj.GetUVList())
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
	if(_meshLoaded)
	{
		_shader.Use(true);
		BindVAO(true);

		glDrawArrays(GL_TRIANGLES, 0, _vertices.size());

		_shader.Use(false);
		BindVAO(false);
	}
	else
	{
		_shader.Use(true);
		BindVAO(true);

		glDrawElements(GL_TRIANGLES, _numIndices, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		
		_shader.Use(false);
		BindVAO(false);
	}
}

//==========================================================================================================================
//v_InitVertexData
//==========================================================================================================================
void GameObject::v_InitBuffers(void)
{
	if(_meshLoaded)
	{
		std::vector<F32> vertPosition;
		std::vector<F32> vertNormals;
		std::vector<F32> vertTexCoords;

		for(auto i : _vertices)
		{
			vertPosition.push_back(i.position[0]);
			vertPosition.push_back(i.position[1]);
			vertPosition.push_back(i.position[2]);
			vertPosition.push_back(i.position[3]);

			vertNormals.push_back(i.normal[0]);
			vertNormals.push_back(i.normal[1]);
			vertNormals.push_back(i.normal[2]);
			vertNormals.push_back(i.normal[3]);

			vertTexCoords.push_back(i.texCoord.u);
			vertTexCoords.push_back(i.texCoord.v);
		}

		glBindVertexArray(_vao);

		glBindBuffer(GL_ARRAY_BUFFER, _vbo[VERTEX_BUFFER]);
		glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertPosition.size()), &vertPosition[0], GL_STATIC_DRAW);
		glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(VERTEX_POS);

		if(vertNormals.size() > 0)
		{
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[NORMAL_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertNormals.size()), &vertNormals[0], GL_STATIC_DRAW);
			glVertexAttribPointer(NORMAL_POS, 4, GL_FLOAT, GL_FALSE, 0 , NULL);
			glEnableVertexAttribArray(NORMAL_POS);				
		}

		if(vertTexCoords.size() > 0)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEX_COORD_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertTexCoords.size()), &vertTexCoords[0], GL_STATIC_DRAW);
			glVertexAttribPointer(TEX_COORD_POS, 2, GL_FLOAT, GL_FALSE, 0 , NULL);
			glEnableVertexAttribArray(TEX_COORD_POS);	
		}

		glBindVertexArray(0);
	}
	else
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
	
				vertTexCoords.push_back(i.texCoord.u);
				vertTexCoords.push_back(i.texCoord.v);
			}
	
			glBindVertexArray(_vao);
	
			glBindBuffer(GL_ARRAY_BUFFER, _vbo[VERTEX_BUFFER]);
			glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertPosition.size()), &vertPosition[0], GL_STATIC_DRAW);
			glVertexAttribPointer(VERTEX_POS, 4, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(VERTEX_POS);
	
			if(vertTexCoords.size() > 0)
			{
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
				glBindBuffer(GL_ARRAY_BUFFER, _vbo[TEX_COORD_BUFFER]);
				glBufferData(GL_ARRAY_BUFFER, (sizeof(F32) * vertTexCoords.size()), &vertTexCoords[0], GL_STATIC_DRAW);
				glVertexAttribPointer(TEX_COORD_POS, 2, GL_FLOAT, GL_FALSE, 0 , NULL);
				glEnableVertexAttribArray(TEX_COORD_POS);	
			}
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[INDEX_BUFFER]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(U32) * _indices.size()), &_indices[0], GL_STATIC_DRAW);
	
			glBindVertexArray(0);
		}
}

//==========================================================================================================================
//
//Functions
//==========================================================================================================================
bool GameObject::LoadOBJ(string filepath)
{
	std::vector<U32> vertexIndices, uvIndices, normalIndices;
	std::vector<KM::Vector> tempVertices;
	std::vector<KM::Vector> tempNormals;
	std::vector<TexCoord> tempUVs;

	if(filepath.find(".obj") != std::string::npos)
	{
		std::ifstream file(filepath, std::ios::in);

		if(!file)
		{
			ErrorManager::Instance()->SetError(EC_Engine, "GameObject::LoadOBJ => unable to open " + filepath);
			return false;
		}

		string lineBuffer;
		while(std::getline(file, lineBuffer))
		{
			std::stringstream ss(lineBuffer);
			string command;
			ss >> command;

			if(command == "v")
			{
				KM::Vector vertex;
				S32 dimension = 0;
				
				while(dimension < 3 && ss >> vertex[dimension])
				{
					++dimension;
				}
				
				tempVertices.push_back(vertex);
			}
			else if(command == "vt")
			{
				TexCoord uv;

				ss >> uv.u;
				ss >> uv.v;

				tempUVs.push_back(uv);
			}
			else if(command == "vn")
			{
				KM::Vector normal;
				S32 dimension = 0;
				
				while(dimension < 3 && ss >> normal[dimension])
				{
					++dimension;
				}

				normal[3] = 0.0f;
				normal.Normalize();
				
				tempNormals.push_back(normal);
			}
			else if(command == "f")
			{
				string faceData;
				S32 vertexIndex, uvIndex, normalIndex;

				while(ss >> faceData)
				{
					std::vector<string> data = _SplitString(faceData, '/');

					//check for vertex data
					if(data[0].size() > 0)
					{
						sscanf_s(data[0].c_str(), "%d", &vertexIndex);
						vertexIndices.push_back(vertexIndex);
					}

					//check for texture coordinate data
					if(data.size() >= 1)
					{
						if(data[1].size() > 0)
						{
							sscanf_s(data[1].c_str(), "%d", &uvIndex);
							uvIndices.push_back(uvIndex);
						}
					}

					//check for normal data
					if(data.size() >= 2)
					{
						if(data[2].size() > 0)
						{
							sscanf_s(data[2].c_str(), "%d", &normalIndex);
							normalIndices.push_back(normalIndex);
						}
					}
				}
			}
		}

		file.close();

		for(U32 i = 0; i < vertexIndices.size(); ++i)
		{
			Vertex meshVertex;

			if(tempVertices.size() > 0)
			{
				meshVertex.position = tempVertices[vertexIndices[i] - 1];
			}

			if(tempUVs.size() > 0)
			{
				meshVertex.texCoord = tempUVs[uvIndices[i] - 1];
			}

			if(tempNormals.size() > 0)
			{
				meshVertex.normal = tempNormals[normalIndices[i] - 1];
			}

			_vertices.push_back(meshVertex);
		}		

		_meshLoaded = true;

		v_InitBuffers();

		return true;
	}

	return false;
}

/*
	This whole second has some severe issues. First, the way that uv's are set is not working at all. The geometry (vertices)
	are working pretty good, but they can't be colored at all, which is a big problem. 

	Additionally, there needs to be more checks that the xml finds what its looking for so that elements that aren't there don't
	crash the whole program. That is why the materials are commented out, if you happen to make a model that does not have any,
	an exception will be thrown, which is not desired. 

	The way that colors are used also needs to be refactored, so that colored materials can be added from blender and work. For 
	now, this method should not be used at all. 
*/
void GameObject::LoadMesh(string filepath)
{
	if(filepath.find(".dae") == std::string::npos)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "GameObject::LoadMesh => Tried to load mesh in the wrong format. " + filepath);
		return;
	}

	std::vector<F32> vertexData;
	std::vector<Vertex> vertices;
	std::vector<F32> uvData;
	std::vector<TexCoord> texCoordValues;

	std::smatch match{};
	std::regex vertexRegex (".*mesh-positions");
	std::regex uvRegex (".*mesh-map.*");

	std::ifstream file(filepath);

	if(!file)
	{
		ErrorManager::Instance()->SetError(EC_Engine, "GameObject::LoadMesh => Failed to open file: " + filepath);
		return;
	}

	std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	//xml file must be 0 terminating
	buffer.push_back('\0');

	file.close();

	rapidxml::xml_document<char> doc;
	doc.parse<0>(&buffer[0]);

	//Set root node
	rapidxml::xml_node<>* root_node = doc.first_node("COLLADA");
	
//===== TO DO =====
//Will need to be able to capture normal data. Here is the code that can do that.
//I am just not sure what to do with that code yet. 

//===== Get Data =====
	rapidxml::xml_node<>* data = root_node->first_node("library_geometries")->first_node("geometry")->first_node("mesh")->first_node("source");	

	for(rapidxml::xml_node<>* i = data; i; i = i->next_sibling("source"))
	{
		string attrib = i->first_attribute("id")->value();
		
		if(std::regex_match(attrib, match, vertexRegex))
		{
		 	rapidxml::xml_node<>* access = i->first_node("float_array"); 
		 	vertexData = _SplitF32(access->value(), ' ');

		 	for(U32 i = 0; i < vertexData.size(); i += 3)
			{
				//vertices.push_back(Vertex(KM::Vector(vertexData[i], vertexData[i+1], vertexData[i+2])));
				AddVertex(Vertex(KM::Vector(vertexData[i], vertexData[i+1], vertexData[i+2])));
			}
		}
		else if(std::regex_match(attrib, match, uvRegex))
		{
		 	rapidxml::xml_node<>* access = i->first_node("float_array"); 
		 	uvData = _SplitF32(access->value(), ' ');
	 	
		 	for(U32 i = 0; i < uvData.size(); i += 2)
		 	{
		 		texCoordValues.push_back(TexCoord(uvData[i], uvData[i+1]));
		 	}
		}
	}
	
//===== Get Materials =====
/*
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
*/
	
	//Get indices
	data = root_node->first_node("library_geometries")->first_node("geometry")->first_node("mesh")->first_node("polylist");

	for(rapidxml::xml_node<>* i = data; i; i = i->next_sibling("polylist"))
	{
/*		
		string id = i->first_attribute("material")->value();

		Color mat = materials.find(id)->second;
*/
		data = i->first_node("p");

		std::vector<U32> indices = _SplitU32(data->value(), ' ');

		std::vector<U32> vertexIndices;
		std::vector<U32> uvIndices;
		
		//count the stride
		S32 stride = 0;
		S32 vertexOffset = -1;
		S32 uvOffset = -1;

		std::regex vertexRegex ("VERTEX");
		std::regex uvRegex ("TEXCOORD");

		for(rapidxml::xml_node<>* j = i->first_node("input"); j; j = j->next_sibling("input"))
		{
			++stride;

			string attrib = j->first_attribute("semantic")->value();

			if(std::regex_match(attrib, match, vertexRegex))
			{
				vertexOffset = atoi(j->first_attribute("offset")->value());
			}
			else if(std::regex_match(attrib, match, uvRegex))
			{
				uvOffset = atoi(j->first_attribute("offset")->value());
			}
		}

		if(stride == 0)
		{
			ErrorManager::Instance()->SetError(EC_Engine, "GameObject::LoadMesh: No stride found. That means there is no input, and your xml file is wrong");
		}

		for(U32 i = 0; i < indices.size(); i+=stride)
		{
			if(vertexOffset >= 0) 
			{
				vertexIndices.push_back(indices[i + vertexOffset]);
			}
			
			if(uvOffset >= 0) 
			{
				uvIndices.push_back(indices[i + uvOffset]);
			}
		}
	
		for(U32 i = 0; i < vertexIndices.size(); ++i)
		{
			S32 index = vertexIndices[i];
			S32 uvIndex = uvIndices[i];

			TexCoord coord = texCoordValues[uvIndex];			
			_vertices[index].texCoord = coord;
		}

		for(U32 i = 0; i < uvIndices.size(); ++i)
		{
			_uvList.push_back(texCoordValues[i].u);
			_uvList.push_back(texCoordValues[i].v);
		}	

		SetIndices(vertexIndices);
	}
}//end LoadMesh

const KM::Matrix GameObject::GetModelMatrix(void)
{
	return KM::Matrix::Translate(_position) * KM::Matrix::Scale(_scale);
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

std::vector<string> GameObject::_SplitString(string text, char delim) const
{
	std::vector<string> data;
	std::stringstream stream(text);
	string item;

	while(std::getline(stream, item, delim))
	{
		data.push_back(item);
	}

	return data;
}