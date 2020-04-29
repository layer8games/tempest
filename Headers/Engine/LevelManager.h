#pragma once

//=====Killer1 includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Level.h>
#include <Engine/ErrorManager.h>

namespace TP = TempestPhysics;

//=====STL includes=====
#include <map>

namespace Tempest 
{ 
    class LevelManager
    {
    public:
        TEMPEST_API ~LevelManager(void);

        TEMPEST_API static LevelManager* Instance();
 
        TEMPEST_API void Add(p_Level level);
        
        TEMPEST_API void Remove(U32 levelID);

        TEMPEST_API p_Level GetLevel(U32 levelID);

    protected: 
        LevelManager(void);

    private:
        std::map<U32, p_Level> _levels;	
        static LevelManager* _instance;

    };
}//End namespace