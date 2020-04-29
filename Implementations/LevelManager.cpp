#include "stdafx.h"
#include <Engine/LevelManager.h>
using namespace Tempest;

LevelManager* LevelManager::_instance = nullptr;
LevelManager::LevelManager(void) 
:
_levels()
{  }

LevelManager::~LevelManager(void)
{  }


LevelManager* LevelManager::Instance(void) 
{
    if(_instance == nullptr) { _instance = new LevelManager; }
    return _instance;
}

void LevelManager::Add(p_Level level) 
{
    if(_levels.count(level->GetID()) == 0)
    {
        _levels.insert({level->GetID(), level});

        if(_levels.count(level->GetID()) == 0)
        {
            ErrorManager::Instance()->SetError(ENGINE, "Unable to AddLevel to LevelManager");
        }
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "LevelManager::Add Attempted to add Level that already exists with ID = " + level->GetID());
    }
}

void LevelManager::Remove(U32 levelID) 
{
    if(_levels.count(levelID) == 1)
    {
        _levels.erase(levelID);
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "LevelManager::Remove No level found with ID = " + levelID);
    }
}

p_Level LevelManager::GetLevel(U32 levelID)
{
    if(_levels.count(levelID) == 1)
    {
        return _levels[levelID];
    }
    else
    {
        ErrorManager::Instance()->SetError(ENGINE, "LevelManager::GetLevel Unable to find Level with ID = " + levelID);
        return nullptr;
    }
}