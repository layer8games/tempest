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
_firework(nullptr),
_speed(100.0f)
{  }

FireworksDemo::~FireworksDemo(void)
{
	_pool.clear();
	_firework.reset();
}

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================	
void FireworksDemo::v_Init(void)
{
	Level::SetID(FIREWORKS_ID);
	Level::SetWidth(KE::GameWindow::Instance()->GetWidth());
	Level::SetHeight(KE::GameWindow::Instance()->GetHeight());
	Level::SetBackgroundColor(KE::Color(0.2f, 0.2f, 0.2f));

	F32 top = KE::GameWindow::Instance()->GetScreenTop();

	_levelTitle.SetFont(KE::FontManager::Instance()->GetFont(100));
	_levelTitle.AddText("FIREWORK DEMO");
	_levelTitle.SetPosition(KM::Point(-_levelTitle.GetWidth(), top - (top * 0.1f)));
	Level::AddTextToLevel(_levelTitle);

	_firework = ProjectFactory::Instance()->MakeFirework();
	_firework->SetLevelID(FIREWORKS_ID);
	_firework->SetTexture(KE::TextureManager::Instance()->GetTexture(102));
	_firework->SetScale(15.0f, 15.0f);
	_firework->SetPosition(0.0f, 0.0f);
	_firework->SetMass(1.0f);
	_firework->SetMaxSize(100);
	Level::AddRigidBody2DToLevel(_firework, nullptr);

	for(U32 i = 0; i < _firework->GetMaxSize(); ++i)
	{
		p_Payload payload = ProjectFactory::Instance()->MakePayload();
		payload->RigidBody2D.MakeSprite();
		payload->RigidBody2D.SetActive(false);
		Level::AddRigidBody2DToLevel(payload->RigidBody2D);
		_pool.push_back(payload);
	}

	_firework->SetPool(_pool);
	_firework->Reset(1);
}

void FireworksDemo::v_Update(void)
{
	//Exit check
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE)) 
	{ 
		KE::LevelManager::Instance()->SetActiveLevel(MAIN_MENU_ID);
		return; 
	}

	//Launch firework check
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ONE))
	{
		_firework->Reset(1);
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::TWO))
	{
		_firework->Reset(2);
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::THREE))
	{
		_firework->Reset(3);
	}
		
	//Move firework check
	if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::UP_ARROW))
	{
		_firework->SetVelocity(0.0f, _speed);
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::DOWN_ARROW))
	{
		_firework->SetVelocity(0.0f, -_speed);
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::RIGHT_ARROW))
	{
		_firework->SetVelocity(_speed, 0.0f);
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::LEFT_ARROW))
	{
		_firework->SetVelocity(-_speed, 0.0f);
	}
	else if(KE::Controller::Instance()->GetKeyHeld(KE::Keys::SPACE))
	{
		_firework->SetVelocity(0.0f, 0.0f);
	}
}