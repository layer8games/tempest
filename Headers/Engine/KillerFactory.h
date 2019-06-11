#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Glyph.h>

namespace KillerEngine
{
	class KillerFactory;
	typedef shared_ptr<KillerFactory> P_KillerFactory;

	class KillerFactory
	{
	public:
//==========================================================================================================================
//
//Destructor	 	
//
//==========================================================================================================================
		~KillerFactory(void);

//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
		inline P_Glyph MakeGlyph(void)
		{
			return make_shared<Glyph>();
		}

//==========================================================================================================================
//
//Singleton Functions
//
//==========================================================================================================================
		static P_KillerFactory Instance(void);

	protected:
//==========================================================================================================================
//
//Constructor
//
//==========================================================================================================================
		KillerFactory(void);

	private:
		static P_KillerFactory _instance;
		
	};//end Class

	
}//end Namespace