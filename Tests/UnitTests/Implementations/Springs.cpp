#include "Boxes\Springs.h"

using namespace Boxes;

Springs::Springs()
:
_levelTitle(),
_gravity(make_shared<KP::GravityForce>()),
_box1OtherEnd(make_shared<KP::Particle>()),
_box1(make_shared<KP::Particle>()),
_box1Spring(make_shared<KP::SpringForce>()),
_box2Anchor(make_shared<KM::Point>()),
_box2(make_shared<KP::Particle>()),
_box2Spring(make_shared<KP::AnchoredSpring>()),
_box3OtherEnd(make_shared<KP::Particle>()),
_box3(make_shared<KP::Particle>()),
_box3Spring(make_shared<KP::SpringForce>()),
_box4(make_shared<KP::Particle>()),
_box4BuoyantForce(make_shared<KP::BuoyantForce>())
{  }

Springs::~Springs()
{  }

void Springs::v_Init(void)
{
	Level::SetID(SPRINGS_ID);
	Level::SetWidth(KE::GameWindow::Instance()->GetWidth());
	Level::SetHeight(KE::GameWindow::Instance()->GetHeight());
	Level::SetBackgroundColor(KE::Color(0.2f, 0.2f, 0.2f));

	F32 top = KE::GameWindow::Instance()->GetScreenTop();

	_levelTitle.SetFont(KE::FontManager::Instance()->GetFont(100));
	_levelTitle.AddText("Spring Demo");
	_levelTitle.SetPosition(KM::Point(-_levelTitle.GetWidth(), top - (top * 0.1f)));
	Level::AddTextToLevel(_levelTitle);


	_gravity->SetGravityAcceleration(KM::Vector4(0.0f, -1000.0f));

	//===== Setup GameObjects =====
	//===== Box1, standard Spring =====
	_box1OtherEnd->MakeSprite();
	_box1OtherEnd->SetMass(1.0f);
	_box1OtherEnd->SetDamping(0.999f);
	_box1OtherEnd->SetScale(10.0f, 10.0f);
	_box1OtherEnd->SetTexture(KE::TextureManager::Instance()->GetTexture(100));
	_box1OtherEnd->SetPosition(0.0f, 0.0f);
	Level::AddObjectToLevel(_box1OtherEnd);

	_box1->MakeSprite();
	_box1->SetMass(50.0f);
	//_box1->SetDamping(0.8f);
	//Fun to set, if you want to see some changes. 
	//_box1->SetAcceleration(200.0f, 0.0f);
	_box1->SetScale(10.0f, 10.0f);
	_box1->SetColor(1.0f, 0.0f, 0.0f);
	_box1->SetPosition(0.0f, 100.0f);

	_box1Spring->SetOtherEnd(_box1OtherEnd);
	_box1Spring->SetSpringConstant(2000.0f);
	_box1Spring->SetRestLength(10.0f);
	Level::AddParticleToLevel(_box1, _box1Spring);

	//===== Box2 Anchored Spring =====
	_box2Anchor->Set(400.0f, 200.0f);
	_box2->MakeSprite();
	_box2->SetMass(1.0f);
	_box2->SetDamping(0.8f);
	_box2->SetScale(10.0f, 10.0f);
	_box2->SetColor(0.0f, 1.0f, 0.0f);
	_box2->SetPosition(-100.0f, 0.0f);

	_box2Spring->SetAnchor(_box2Anchor);
	_box2Spring->SetSpringConstant(2000.0f);
	_box2Spring->SetRestLength(1.0f);
	Level::AddParticleToLevel(_box2, _box2Spring);

	//===== Box3, standard Spring =====
	_box3OtherEnd->MakeSprite();
	_box3OtherEnd->SetMass(1.0f);
	_box3OtherEnd->SetDamping(0.999f);
	_box3OtherEnd->SetScale(10.0f, 10.0f);
	_box3OtherEnd->SetColor(0.0f, 0.0f, 1.0f);
	_box3OtherEnd->SetPosition(200.0f, 0.0f);
	Level::AddObjectToLevel(_box3OtherEnd);

	_box3->MakeSprite();
	_box3->SetMass(1.0f);
	_box3->SetDamping(0.8f);
	//Fun to set, if you want to see some changes. 
	//_box3->SetAcceleration(200.0f, 0.0f);
	_box3->SetScale(10.0f, 10.0f);
	_box3->SetColor(0.0f, 0.0f, 1.0f);
	_box3->SetPosition(40.0f, 0.0f);

	_box3Spring->SetOtherEnd(shared_ptr<KP::Particle>(&_box3OtherEnd));
	_box3Spring->SetSpringConstant(2000.0f);
	_box3Spring->SetRestLength(100.0f);
	_box3Spring->MakeBungie(true);
	Level::AddParticleToLevel(_box3, _box3Spring);
	Level::RegisterParticleForce(_box3, _gravity);

	//===== Box4 Buoyant Force =====
	/*
Needs work...

	_box4->SetMass(1.0f);
	_box4->SetDamping(0.8f);
	//_box4->SetScale(10.0f, 10.0f);
	//_box4->SetColor(1.0f, 1.0f, 0.0f);
	_box4->SetPosition(800.0f, 300.0f);

	_box4BuoyantForce->SetMaxDepth(300.0f);
	_box4BuoyantForce->SetObjectVolume(10.0f);
	_box4BuoyantForce->SetLiquidHeight(600.0f);
	_box4BuoyantForce->SetLiquidDensity(10.0f);

	_forceRegistry->Add(shared_ptr<KP::Particle>(&_box4), shared_ptr<KP::ParticleBuoyantForce>(&_box4BuoyantForce));
	//_forceRegistry->Add(shared_ptr<KP::Particle>(&_box4), shared_ptr<KP::GravityForce>(&_gravity));
	//Level::AddObjectToLevel(_box4);
*/	
}

void Springs::v_Update(void)
{
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE)) 
	{ 
		KE::LevelManager::Instance()->SetActiveLevel(2); 
	}
}