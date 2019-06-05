#include <Boxes/SplashScreen.h>

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
_mainTitle()
{  }
 
SplashScreen::~SplashScreen(void) 
{

}

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

	F32 left = KE::GameWindow::Instance()->GetScreenLeft();
	F32 right = KE::GameWindow::Instance()->GetScreenRight();
	F32 bottom = KE::GameWindow::Instance()->GetScreenBottom();
	F32 top = KE::GameWindow::Instance()->GetScreenTop();

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

	
}

//=============================================================================
//
//Update
//
//=============================================================================
void SplashScreen::v_Update(void) 
{
	KE::AudioManager::Instance()->PlaySource(1);

	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE))
	{
		KE::Engine::Instance()->End();
	}

	KM::Point greenPos = _green.GetPosition();
	KM::Point bluePos  = _blue.GetPosition();
	F32 redWidth   = _red.GetScale()[1];

	if(greenPos[1] >= KE::GameWindow::Instance()->GetScreenBottom()) 
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
		KE::AudioManager::Instance()->PauseSource(1);
		KE::LevelManager::Instance()->SetActiveLevel(2);
	}
}