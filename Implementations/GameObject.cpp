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
	std::vector<U32> vertexIndices, uvIndices;
	std::vector<KM::Vector> tempVertices;
	std::vector<TexCoord> tempUVs;

	if(filepath.find(".obj") != std::string::npos)
	{
		std::ifstream file(filepath, std::ios::in);

		if(!file)
		{
			ErrorManager::Instance()->SetError(EC_Engine, "GameObject::LoadOBJ => unable to open " + filepath);
			return false;
		}

		//remove later
		std::cout << "Loading OBJ file " << filepath << " ...\n";

		string lineBuffer;
		while(std::getline(file, lineBuffer))
		{
			if(lineBuffer.substr(0, 2) == "v ")
			{
				std::istringstream v(lineBuffer.substr(2));
				KM::Vector vertex;
				
				v >> vertex[0];
				v >> vertex[1];
				v >> vertex[2];
				
				tempVertices.push_back(vertex);
			}
			else if(lineBuffer.substr(0, 2) == "vt")
			{
				std::istringstream vt(lineBuffer.substr(3));
				TexCoord uv;

				vt >> uv.u;
				vt >> uv.v;

				tempUVs.push_back(uv);
			}
			else if(lineBuffer.substr(0, 2) == "f ")
			{
				S32 p1, p2, p3; //store mesh index
				S32 t1, t2, t3; //store texture index
				S32 n1, n2, n3; //store normal index

				const char* face = lineBuffer.c_str();

				S32 match = sscanf_s(
					face, "f %i/%i/%i %i/%i/%i %i/%i/%i",
					&p1, &t1, &n1,  
					&p2, &t2, &n2,
					&p3, &t3, &n3 );

				if(match != 9)
				{
					ErrorManager::Instance()->SetError(EC_Engine, "GameObject::LoadOBJ => didn't find enough indices. Found " + match);
					return false;
				}

				vertexIndices.push_back(p1);
				vertexIndices.push_back(p2);
				vertexIndices.push_back(p3);

				uvIndices.push_back(t1);
				uvIndices.push_back(t2);
				uvIndices.push_back(t3);

				//Add normals here
			}
		}

		file.close();

		for(U32 i = 0; i < vertexIndices.size(); ++i)
		{
			KM::Vector vertex = tempVertices[vertexIndices[i] -1];
			TexCoord uv = tempUVs[uvIndices[i] - 1];

			Vertex meshVertex;
			meshVertex.position = vertex;
			meshVertex.texCoord = uv;

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