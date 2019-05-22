#include <Boxes/SplashScreen.h>
#include <iostream>

using namespace Boxes;
//=============================================================================
//
//Constructor
//
//=============================================================================
SplashScreen::SplashScreen(void) 
: 
_red(),
_green(),
_blue(),
_mainTitle(),
_device(nullptr),
_context(nullptr),
_source(0),
_buffer(0)
{  }
 
SplashScreen::~SplashScreen(void) 
{  }

//=============================================================================
//
//InitLevel
//
//=============================================================================
void SplashScreen::v_InitLevel(U32 id, S32 w, S32 h, const KE::Color& c) 
{
	Level::SetID(id);
	Level::SetLevelWidth(w);
	Level::SetLevelHeight(h);
	Level::SetBackgroundColor(c);

	F32 left = KE::WinProgram::Instance()->GetScreenLeft();
	F32 right = KE::WinProgram::Instance()->GetScreenRight();
	F32 bottom = KE::WinProgram::Instance()->GetScreenBottom();
	F32 top = KE::WinProgram::Instance()->GetScreenTop();

	_red.SetPosition(0.0f, 0.0f);
	_red.SetTexture(KE::TextureManager::Instance()->GetTexture(100));
	_red.SetScale(25.0f, 25.0f);
	Level::AddObjectToLevel(_red);

	_green.SetPosition(left / 3.0f, top / 3.0f);
	_green.SetTexture(KE::TextureManager::Instance()->GetTexture(101));
	_green.SetScale(25.0f, 25.0f);
	_green.SetSpeed(400.0f);
	Level::AddObjectToLevel(_green);

	_blue.SetPosition(right / 3.0f, top / 3.0f);
	_blue.SetTexture(KE::TextureManager::Instance()->GetTexture(102));
	_blue.SetScale(25.0f, 25.0f);
	_blue.SetSpeed(400.0f);
	Level::AddObjectToLevel(_blue);
	
	_mainTitle.SetFont(KE::FontManager::Instance()->GetFont(100));
	_mainTitle.AddText("BOXES vs TRIANGLES");
	_mainTitle.SetPosition(KM::Point(-_mainTitle.GetWidth(), top - (top * 0.1f)));
	Level::AddTextToLevel(_mainTitle);

	//===== OpenAL Tests =====
	//Get a device
	ALCenum error;

	_device = alcOpenDevice(NULL);

	error = alGetError();

	if(!_device || error != AL_NO_ERROR)
	{
		std::cout << "Oops! no device found or there was an error!\n";
	}

	//Get device list
	ALboolean enumeration;
	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");

	if(enumeration == AL_FALSE)
	{
		std::cout << "enumeration not supported\n";
	}
	else
	{
		list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	}

	error = alGetError();

	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error checking for devices\n";
	}

	//Create a context and make it active
	_context = alcCreateContext(_device, NULL);

	if(!alcMakeContextCurrent(_context))
	{
		std::cout << "OOps! couldn't make context current\n";
	}

	error = alGetError();

	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error after the context was made current\n";
	}

	//Configure listener
	ALfloat listernOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	alListener3f(AL_POSITION, 0.0f, 0.0f, 1.0f);
	error = alGetError();

	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error setting the listener pos\n";
	}

	alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error setting listener velocity\n";
	}

	alListenerfv(AL_ORIENTATION, listernOri);
	
	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error setting listener orientation\n";
	}

	//generate sources
	alGenSources((ALuint)1, &_source);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error generating the source\n";
	}

	alSourcef(_source, AL_PITCH, 1.0f);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error setting source pitch\n";
	}

	alSourcef(_source, AL_GAIN, 1.0f);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error setting source gain\n";
	}

	alSource3f(_source, AL_POSITION, 0.0f, 0.0f, 0.0f);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error setting source pos\n";
	}

	alSource3f(_source, AL_VELOCITY, 0.0f, 0.0f, 0.0f);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error setting source velocity\n";
	}

	alSourcei(_source, AL_LOOPING, AL_FALSE);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error setting source looping\n";
	}

	//generate buffer
	alGenBuffers((ALuint)1, &_buffer);

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error generating the buffer\n";
	}

	//load audio into buffer
	//buffer data
	ALsizei size, freq;
	ALenum format;
	ALvoid *data;
	ALboolean loop = AL_FALSE;

	alutLoadWAVFile("../Assets/Audio/Komiku_04_Skate.wav");

	error = alGetError();
	if(error != AL_NO_ERROR)
	{
		std::cout << "Oops! There was an error loading the wav file\n";
	}
}

//=============================================================================
//
//Update
//
//=============================================================================
void SplashScreen::v_Update(void) 
{
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE))
	{
		KE::Engine::Instance()->End();
	}

	KM::Point greenPos = _green.GetPosition();
	KM::Point bluePos  = _blue.GetPosition();
	F32 redWidth   = _red.GetScale()[1];

	if(greenPos[1] >= KE::WinProgram::Instance()->GetScreenBottom()) 
	{
		_green.SetDirection(0.0f, -1.0f);

		_blue.SetDirection(0.0f, -1.0f);
	}
	else if(redWidth <= 500.0f) 
	{
		_green.SetActive(false);
		_blue.SetActive(false);

		F32 size = _red.GetScale()[1] + KM::Timer::Instance()->DeltaTime() * 250.0f;
		_red.SetScale(size, size);
	}
	
	else 
	{ 
		KE::LevelManager::Instance()->SetActiveLevel(2);
	}
}