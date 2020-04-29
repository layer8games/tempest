#pragma once

//=====Engine Includes=====
#include "stdafx.h"
#include <Engine/Atom.h>
#include <Engine/Shader.h>
#include <Engine/ErrorManager.h>

//===== STL Includes =====
#include <map>
#include <vector>

namespace Tempest
{
/// Global ID for default shaders that the engine provides. Some projects (most projects) will want to create their own
/// Shaders, based on the graphical needs of each project. These default shaders are provided by the Engine by these
/// ID's. 
    enum TEMPEST_API DefaultShaderID
    {
        SPRITE = 0, ///< ID for a standard sprite. No special affects.
        GLYPH = 1   ///< ID for text glyphs. Differs from the sprite in a few key ways. 
    };

/// A global manager for Shaders that are compiled for use. The idea behind this manager is that you can use it to re-use
/// shaders. These are passed as pointers, so they can be shared and reused. Before a shader can be used, it has to be 
/// made active. That can be done on the Shader itself, this is more of a bank for all the shaders that have been created
/// thus far.
    class ShaderManager
    {
    public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================		
/// No implementation
        TEMPEST_API ~ShaderManager(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
/// Singleton function. Returns the global instance of the ShaderManager.
        TEMPEST_API static shared_ptr<ShaderManager> Instance(void);

/// Registers a previously created Shader with the Manager. 
/// \param id is used to recall the Shader when it is needed. 
/// \param shader is a pointer to the shader that is to be registered.
        TEMPEST_API void AddShader(U32 id, shared_ptr<Shader> shader);

/// Creates and registers a new Shader into the manager.
/// \param id is used to recall the Shader.
/// \param data is an array of data needed to create a new shader. See ShaderData for details of what is required.
        TEMPEST_API void LoadShader(U32 id, std::vector<ShaderData> data);

/// Recalls a previously registered Shader for use. A pointer is returned.
/// \param id must map to a shader that has previously been created. If a bad ID is passed, an error is thrown.
        TEMPEST_API shared_ptr<Shader> GetShader(U32 id);

    protected:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
/// No implementation		
        ShaderManager(void);

    private:
//==========================================================================================================================
//
//Private Functions
//
//==========================================================================================================================
/// Internal function that loads a series of default Shaders. These are then registered with the the id in DefaultShaderID.
/// The code for these default Shaders are stored in the Tempest directory, located in /Assets/Shaders/Default/.
        void _LoadDefaultShaders(void);
//==========================================================================================================================
//
//Data
//
//==========================================================================================================================		
        static shared_ptr<ShaderManager>  _instance;		///< Internal, global instance of the manager.
        std::map<U32, shared_ptr<Shader>> _loadedShaders;	///< Map used to track regsitered Shaders. Key = ID, Value = Shader pointer.
    };//end Class
}//end Namespace
