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
_cannon(),
_gravityForce(KM::Vector4(0.0f, -100.0f)),
_projectilePool()
{  }

Ballistics::~Ballistics(void) {  }

//=============================================================================
//
//InitLevel
//
//=============================================================================
void Ballistics::v_InitLevel(U32 id, S32 w, S32 h, KE::Color& c)
{
	Level::SetID(id);
	Level::SetLevelWidth(w);
	Level::SetLevelHeight(h);
	Level::SetBackgroundColor(c);

	F32 width = static_cast<F32>(w);
	F32 height = static_cast<F32>(h);

	F32 left = -width / 2.0f;
	F32 right = width / 2.0f;
	F32 bottom = -height / 2.0f;
	F32 top = height / 2.0f;

	_levelTitle.SetFont(KE::FontManager::Instance()->GetFont(100));
	_levelTitle.AddText("BALLISTICS");
	_levelTitle.SetPosition(KM::Point(-_levelTitle.GetWidth(), top - (top * 0.1f)));
	Level::AddTextToLevel(_levelTitle);
	

	//=====Setup GameObjects=====
	//minus because left and bottom are already negative
	_cannon.SetPosition(left - (left / 10.0f), bottom - (bottom / 10.0f));
	_cannon.SetScale(25.0f, 25.0f);
	_cannon.SetMovementSpeed(120.0f);
	_cannon.SetTopBoundary(top);
	_cannon.SetBottomBoundary(bottom);
	_cannon.SetTexture(KE::TextureManager::Instance()->GetTexture(300));
	Level::AddObjectToLevel(_cannon);

	shared_ptr<KP::GravityForce> gravity{&_gravityForce};
	for(U32 i = 0; i < _poolSize; ++i)
	{
		shared_ptr<Projectile> p{new Projectile()};
		p->SetScale(10.0f, 10.0f);
		_projectilePool.push_back(p);
		Level::AddParticleToLevel(p, gravity);
	}

	//TODO:: Once level's call init when they are set to active, this can be removed
	KE::WinProgram::Instance()->EnableMouseCursor();
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
		KE::LevelManager::Instance()->SetActiveLevel(2); 
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

		KM::Vector4 heading = KM::Vector4(input - _cannon.GetPosition());

		heading.Normalize();
		
		for(auto i : _projectilePool)
		{
			if(!i->GetActive())
			{
				_cannon.Fire(heading, i, _activeProjectileType);
				break;
			}
		}
	}
}