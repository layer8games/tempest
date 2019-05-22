/*==========================================================================================================================
Opening Splash screen prototype

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
==========================================================================================================================*/
#pragma once

//Killer1 includes
#include <Engine/Atom.h>
#include <Engine/LevelManager.h>
#include <Engine/WinProgram.h>
#include <Engine/Level.h>
#include <Engine/Timer.h>
#include <Engine/TextureManager.h>
#include <Engine/FontManager.h>
#include <Engine/Text.h>
#include <Engine/Color.h>
#include <Engine/Point.h>
#include <Engine/Controller.h>
#include <Engine/Engine.h>

//===== OpenAL =====
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

namespace KE = KillerEngine;
namespace KM = KillerMath;

//=====Box includes=====
#include <Boxes/Box.h>

namespace Boxes 
{

	class SplashScreen: public KE::Level
	{
	public:
//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================		
		SplashScreen(void);
		
		~SplashScreen(void);

//==========================================================================================================================
//
//Virtual functions
//
//==========================================================================================================================		
		void v_InitLevel(U32 id, S32 w, S32 h, const KE::Color& c);
		
		void v_Update(void);
	
	private:
//==========================================================================================================================
//
//Members
//
//==========================================================================================================================		
		Box 	 _red;
		Box 	 _green;
		Box 	 _blue;
		KE::Text _mainTitle;

		ALCdevice* _device;
		ALCcontext* _context;
		ALuint _source;
		ALuint _buffer;
	};

	//returns a list of audio devices. Part of OpenAL tests
	static void list_audio_devices(const ALCchar* devices)
	{
		const ALCchar* device = devices, *next = devices + 1;
		size_t len = 0;

		fprintf(stdout, "Devices list:\n");
		fprintf(stdout, "-----------\n");

		while(device && *device != '\0' && next && *next != '\0')
		{
			fprintf(stdout, "%s\n", device);
			len = strlen(device);
			device += (len + 1);
			next += (len + 2);
		}

		fprintf(stdout, "-----------\n");
	}

}//End namespace