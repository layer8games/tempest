/*-------------------------------------------------------------------
MovingBoxes is the whole of phase one for Killer Wave Entertainment.
MovingBoxes will move, and will be able to be toggled active. That is 
pretty much it.

This is not free to use, and cannot be used without the express permission
of Layer8Games? I don't know my own name these days. 

Written by Maxwell Miller
---------------------------------------------------------------------*/
#pragma once

//Killer1 Includes
#include <Engine/Atom.h>
#include <Engine/ErrorManager.h>
#include <Engine/LevelManager.h>
#include <Engine/Level.h>
#include <Engine/Controller.h>
#include <Engine/TextureManager.h>
#include <Engine/FontManager.h>
#include <Engine/Text.h>
#include <Engine/Vector4.h>
#include <Engine/Point.h>
#include <Engine/Color.h>
#include <Engine/Timer.h>
#include <Engine/GameObject.h>

#include <Boxes/Box.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

namespace Boxes 
{
	class MovingBoxes : public KE::Level 
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
		MovingBoxes(void);
		
		~MovingBoxes(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================
		void v_InitLevel(U32 id, S32 w, S32 h, KE::Color& c);
		
		void v_Update(void);

//==========================================================================================================================
//
//MovingBoxes functions
//
//==========================================================================================================================		
		void CheckBoxEdge(KE::GameObject& b);

	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================		
		F32 	 _left;
		F32 	 _right;
		F32 	 _bottom;
		F32 	 _top;
		Box 	 _redbox;
		Box 	 _bluebox;
		Box 	 _greenbox;
		KE::Text _levelTitle;
		Box* 	 _activeBox;
	};

}//End namespace