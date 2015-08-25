#include <Engine/World.h>

//--------------------------------------------------------------
//AddObjectToWorld
//--------------------------------------------------------------
void World::AddObjectToWorld(text objId, GameObject* obj){
	_worldObjects[objId] = obj;
	
	if(_worldObjects.find(objId) == _worldObjects.end()) { _errorManager->SetError(EC_KillerEngine, "Unable to AddWorld to _worldObjects"); }
}