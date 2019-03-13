#include <Boxes/FireworksDemo.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors	 	
//
//==========================================================================================================================
FireworksDemo::FireworksDemo(void) 
:  
_levelTitle(),
_firework(),
_speed(100.0f)
{  }

FireworksDemo::~FireworksDemo(void)
{  }

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================	
void FireworksDemo::v_InitLevel(U32 id, S32 w, S32 h, KE::Color& c)
{
	Level::SetID(id);
	Level::SetLevelWidth(w);
	Level::SetLevelHeight(h);
	Level::SetBackgroundColor(c);

	F32 top = KE::WinProgram::Instance()->GetScreenTop();

	_levelTitle.SetFont(KE::FontManager::Instance()->GetFont(100));
	_levelTitle.AddText("FIREWORK DEMO");
	_levelTitle.SetPosition(KM::Point(-_levelTitle.GetWidth(), top - (top * 0.1f)));
	Level::AddTextToLevel(_levelTitle);

	_firework.SetLevelID(id);
	_firework.SetTexture(KE::TextureManager::Instance()->GetTexture(102));
	_firework.SetScale(15.0f, 15.0f);
	_firework.SetPosition(0.0f, 0.0f);
	_firework.SetMass(1.0f);
	_firework.SetMaxSize(100);
	Level::AddParticleToLevel(_firework);

	for(U32 i = 0; i < _firework.GetMaxSize(); ++i)
	{
		shared_ptr<Payload> payload(new Payload());
		payload->particle.MakeSprite();
		payload->particle.SetActive(false);
		Level::AddParticleToLevel(payload->particle);
		_pool.push_back(payload);
	}

	_firework.SetPool(_pool);
	_firework.Reset(1);
}

void FireworksDemo::v_Update(void)
{
	//Exit check
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE)) 
	{ 
		KE::LevelManager::Instance()->SetActiveLevel(2); 
	}

	//Launch firework check
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ONE))
	{
		_firework.Reset(1);
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::TWO))
	{
		_firework.Reset(2);
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::THREE))
	{
		_firework.Reset(3);
	}
		
	//Move firework check
	if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::UP_ARROW))
	{
		_firework.SetVelocity(0.0f, _speed);
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::DOWN_ARROW))
	{
		_firework.SetVelocity(0.0f, -_speed);
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::RIGHT_ARROW))
	{
		_firework.SetVelocity(_speed, 0.0f);
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::LEFT_ARROW))
	{
		_firework.SetVelocity(-_speed, 0.0f);
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::SPACE))
	{
		_firework.SetVelocity(0.0f, 0.0f);
	}
}