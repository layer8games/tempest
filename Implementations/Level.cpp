#include <Engine/Level.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
Level::Level(void) 
: 
_width(0),
_height(0),
_topBorder(0),
_bottomBorder(0),
_rightBorder(0),
_leftBorder(0),
_depth(0),
_nearBorder(0),
_farBorder(0),
_bgColor(),
_ID(0),
_camera(new Camera()),
_gameObjects(),
_particles(),
_forceRegistry()
{
	_camera->SetOrthographic();
}

Level::~Level(void)
{
	delete _camera;
	_gameObjects.clear();
	_particles.clear();
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void Level::v_Integrate(void)
{
	_forceRegistry.UpdateForces();

	for(auto i : _particles)
	{
		if(i.second->GetActive())
		{
			i.second->Integrate();
		}
	}
}

void Level::v_Render(void)
{ 
	RenderObjects(); 
}

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================

void Level::UpdateLevel(void)
{
	_camera->v_Update();
}

void Level::AddObjectToLevel(const GameObject& obj)
{
	_gameObjects.insert({ obj.GetID(), shared_ptr<GameObject>(const_cast<GameObject*>(&obj)) });
	_gameObjects[obj.GetID()]->SetUniform("projection", _camera->GetProjectionMatrix4());

	if(_gameObjects.find(obj.GetID()) == _gameObjects.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject to level.");
	}
}

void Level::AddObjectToLevel(shared_ptr<GameObject> obj)
{
	obj->SetUniform("projection", _camera->GetProjectionMatrix4());

	_gameObjects.insert({obj->GetID(), obj});

	if(_gameObjects.find(obj->GetID()) == _gameObjects.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddObjectToLevel Unable to add GameObject to level.");
	}
}

void Level::AddParticleToLevel(const KP::Particle& particle)
{
	_particles.insert({ particle.GetID(), shared_ptr<KP::Particle>(const_cast<KP::Particle*>(&particle)) });
	_particles[particle.GetID()]->SetUniform("projection", _camera->GetProjectionMatrix4());

	if(_particles.find(particle.GetID()) == _particles.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddParticleToLevel Unable to add Particle to level.");
	}
}

void Level::AddParticleToLevel(shared_ptr<KP::Particle> particle)
{
	particle->SetUniform("projection", _camera->GetProjectionMatrix4());

	_particles.insert({particle->GetID(), particle});

	if(_particles.find(particle->GetID()) == _particles.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::AddParticleToLevel Unable to add Particle to level.");	
	}
}

void Level::AddParticleToLevel(shared_ptr<KP::Particle> particle, shared_ptr<KP::ForceGenerator> generator)
{
	particle->SetUniform("projection", _camera->GetProjectionMatrix4());

	_particles.insert({particle->GetID(), particle});

	if(_particles.find(particle->GetID()) == _particles.end())
	{
		ErrorManager::Instance()->SetError(ENGINE, "Unable to Add Particle to Level. Level.h line 80");
	}

	if(generator != nullptr)
	{
		_forceRegistry.Add(particle, generator);
	}
}

void Level::AddTextToLevel(const Text& text)
{
	//text->SetUniforms("projection", _camera->GetProjectionMatrix4());

	//_textList.push_back(text);
	std::vector<shared_ptr<Glyph>> v = text.GetCharacterList();
	for(auto i : v)
	{
		AddObjectToLevel(i);
	}
}

void Level::AddTextToLevel(shared_ptr<Text> text)
{
	std::vector<shared_ptr<Glyph>> v = text->GetCharacterList();
	for(auto i : v)
	{
		AddObjectToLevel(i);
	}
}

//=============================================================================
//
//RemoveObjectFromLevel
//
//=============================================================================
void Level::RemoveObjectFromLevel(U32 id)
{
	//Assume that if an ID is not a GameObject, then it could be derived type.
	if(_gameObjects.find(id) != _gameObjects.end())
	{
		_gameObjects.erase(id);
	}
	else if(_particles.find(id) != _particles.end())
	{
		_particles.erase(id);
	}
	else
	{
		ErrorManager::Instance()->SetError(ENGINE, "Level::RemoveObjectFromLevel, ln 163, no object found with id " + id);
	}
}

//==========================================================================================================================
//
//Update and Render all objects
//
//==========================================================================================================================	
void Level::UpdateObjects(void)
{
	for(auto i : _gameObjects)
	{
		if(i.second->GetActiveUpdate())
		{
			i.second->UpdateInternals();
			i.second->v_Update();
		}
	}

	for(auto i : _particles)
	{
		if(i.second->GetActiveUpdate())
		{
			i.second->UpdateInternals();
			i.second->v_Update();
		}
	}
}

void Level::RenderObjects(void)
{
//==========================================================================================================================
//Render Sprites
//==========================================================================================================================	
	for(auto i : _gameObjects)
	{
		if(i.second->GetActiveRender())
		{
			i.second->SetUniform("view", _camera->GetViewMatrix4());
			i.second->v_Render();
		}
	}

	for(auto i : _particles)
	{
		if(i.second->GetActiveRender())
		{
			i.second->SetUniform("view", _camera->GetViewMatrix4());
			i.second->v_Render();
		}
	}	
}

//==========================================================================================================================
//GetObjects
//==========================================================================================================================

shared_ptr<GameObject> Level::GetGameObject(U32 id)
{
	shared_ptr<GameObject> obj = _gameObjects[id];

	if(obj == nullptr)
	{
		//ErrorManager::Instance()->SetError(ENGINE, "Level::GetGameObject ln 233, unable to find object with id " + id);
		return nullptr;
	}

	return obj;
}

shared_ptr<KP::Particle> Level::GetParticle(U32 id)
{
	shared_ptr<KP::Particle> obj = _particles[id];

	if(obj == nullptr)
	{
		//ErrorManager::Instance()->SetError(ENGINE, "Level::GetGameObject ln 233, unable to find object with id " + id);
		return nullptr;
	}

	return obj;
}