#include <Boxes/Ballistics.h>

using namespace Boxes;

//=============================================================================
//
//Constructor
//
//=============================================================================
Ballistics::Ballistics(void) 
:
_poolSize(10),
_activeProjectileType(ProjectileType::BULLET),
_levelTitle(),
_cannon(nullptr),
p_gravityForce(nullptr)
{
	p_gravityForce = KP::PhysicsFactory::Instance()->MakeGravityForce();
	p_gravityForce->Set(0.0f, -100.0f, 0.0f);
}

Ballistics::~Ballistics(void)
{
	_cannon.reset();
}

//=============================================================================
//
//InitLevel
//
//=============================================================================
void Ballistics::v_Init(void)
{
	Level::SetID(BALLISTICS_ID);
	Level::SetWidth(KE::GameWindow::Instance()->GetWidth());
	Level::SetHeight(KE::GameWindow::Instance()->GetHeight());
	Level::SetBackgroundColor(KE::Color(0.2f, 0.2f, 0.2f));

	F32 width = static_cast<F32>(Level::GetWidth());
	F32 height = static_cast<F32>(Level::GetHeight());

	F32 left = -width / 2.0f;
	F32 right = width / 2.0f;
	F32 bottom = -height / 2.0f;
	F32 top = height / 2.0f;

	_levelTitle.SetFont(KE::FontManager::Instance()->GetFont(100));
	_levelTitle.AddText("BALLISTICS");
	_levelTitle.SetPosition(KM::Point(-_levelTitle.GetWidth(), top - (top * 0.1f)));
	Level::AddTextToLevel(_levelTitle);
	

	//=====Setup GameObjects=====
	_cannon = ProjectFactory::Instance()->MakeCannon();
	//minus because left and bottom are already negative
	_cannon->SetPosition(left - (left / 10.0f), bottom - (bottom / 10.0f));
	_cannon->SetScale(25.0f, 25.0f);
	_cannon->SetMovementSpeed(120.0f);
	_cannon->SetTopBoundary(top);
	_cannon->SetBottomBoundary(bottom);
	_cannon->SetTexture(KE::TextureManager::Instance()->GetTexture(300));
	Level::AddObjectToLevel(_cannon);

	
	for(U32 i = 0; i < _poolSize; ++i)
	{
		p_Projectile p = ProjectFactory::Instance()->MakeProjectile();
		p->SetScale(10.0f, 10.0f);
		_cannon->AddToPool(p);
		Level::AddObjectToLevel(p);
		Level::RegisterRigidBody2DForce(p->GetRigidBody(), p_gravityForce);
	}

	//TODO:: Once level's call init when they are set to active, this can be removed
	KE::GameWindow::Instance()->EnableMouseCursor();
}	

//=============================================================================
//
//Update
//
//=============================================================================
void Ballistics::v_Update(void)
{
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE)) 
	{ 
		KE::LevelManager::Instance()->SetActiveLevel(MAIN_MENU_ID);
		return;
	}

	//===== Get User Input =====
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ONE))
	{
		_activeProjectileType = BULLET;
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::TWO))
	{
		_activeProjectileType = ARTILLERY;
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::THREE))
	{
		_activeProjectileType = MISSILE;
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::FOUR))
	{
		_activeProjectileType = FIRE_BALL;
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::FIVE))
	{
		_activeProjectileType = LAZER;
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::SIX))
	{
		_activeProjectileType = GRENADE;
	}

	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::LEFT_MOUSE)) 
	{ 
		KM::Point input = KE::Controller::Instance()->GetMouseCoordInScreen();

		KM::Vector4 heading = KM::Vector4(input - _cannon->GetPosition());

		heading.Normalize();
				
		_cannon->Fire(heading, _activeProjectileType);
	}
}