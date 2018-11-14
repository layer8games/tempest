#pragma once

//=====Engine Includes=====
#include <Engine/Atom.h>
#include <Engine/Font.h>
#include <Engine/ErrorManager.h>

//===== STL includes =====
#include <map>

namespace KillerEngine
{
	class FontManager
	{
	public:
//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
		~FontManager(void);

//==========================================================================================================================
//
//Fucntions
//
//==========================================================================================================================
		static shared_ptr<FontManager> Instance(void);

		void LoadFont(U32 id, string fontName, string filePath, U32 size);

		void AddFont(U32 id, shared_ptr<Font> font);

		void AddFont(U32 id, Font& font);

		shared_ptr<Font> GetFont(U32 id);

	protected:
//==========================================================================================================================
//Constructor
//==========================================================================================================================
		FontManager(void);
//==========================================================================================================================
//
//Functions
//
//==========================================================================================================================
	private:
		static shared_ptr<FontManager>  _instance;
		std::map<U32, shared_ptr<Font>> _loadedFonts;
		
	};//end Class
}//end Namespace
