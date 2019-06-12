#include <Boxes/MainMenu.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
MainMenu::MainMenu(void) 
: 
_selector(ProjectFactory::Instance()->MakeBox()),
_menu(),
_menuItemFont(),
_mainTitle()
{  }

MainMenu::~MainMenu(void) 
{  }	

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void MainMenu::v_Init(void)
{
	Level::SetID(MAIN_MENU_ID);
	Level::SetWidth(KE::GameWindow::Instance()->GetWidth());
	Level::SetHeight(KE::GameWindow::Instance()->GetHeight());
	Level::SetBackgroundColor(KE::Color(0.2f, 0.2f, 0.2f));

	F32 top = KE::GameWindow::Instance()->GetScreenTop();

	_selector->SetColor(KE::Color(1.0f, 0.0f, 0.0f));
	_selector->SetTexture(KE::TextureManager::Instance()->GetTexture(100));
	_selector->SetScale(15.0f, 15.0f);

	_mainTitle.SetFont(KE::FontManager::Instance()->GetFont(101));
	_mainTitle.AddText("BOXES vs TRIANGLES");

	_menu.SetPosition(-_mainTitle.GetWidth(), top - (top * 0.1f));
	_menu.SetTitleOffset(_mainTitle.GetWidth() / 2.0f, -top * 0.333f);
	_menu.SetItemOffset(0.0f, -60.0f);
	_menu.SetSelectorOffset(-50.0f, 0.0f);
	_menu.SetWrap(true);

	KE::MenuItem level1 { };
	level1.text = shared_ptr<KE::Text>(new KE::Text("Moving Boxes", KE::FontManager::Instance()->GetFont(100)));
	level1.Action = &MenuItem_Level1Action;

	//KE::MenuItem ballistics { };
	//ballistics.text = shared_ptr<KE::Text>(new KE::Text("Ballistic", KE::FontManager::Instance()->GetFont(100)));
	//ballistics.Action = &MenuItem_BallisticsAction;

	//KE::MenuItem firework { };
	//firework.text = shared_ptr<KE::Text>(new KE::Text("Firework Demo", KE::FontManager::Instance()->GetFont(100)));
	//firework.Action = &MenuItem_FireworkAction;

	//KE::MenuItem springs { };
	//springs.text = shared_ptr<KE::Text>(new KE::Text("Springs Demo", KE::FontManager::Instance()->GetFont(100)));
	//springs.Action = &MenuItem_SpringsAction;

	KE::MenuItem opengl { };
	opengl.text = shared_ptr<KE::Text>(new KE::Text("3D Level", KE::FontManager::Instance()->GetFont(100)));
	opengl.Action = &MenuItem_OpenglAction;


	Level::AddObjectToLevel(_selector);
	Level::AddTextToLevel(_mainTitle);
	Level::AddTextToLevel(level1.text);
	//Level::AddTextToLevel(ballistics.text);
	//Level::AddTextToLevel(firework.text);
	//Level::AddTextToLevel(springs.text);
	Level::AddTextToLevel(opengl.text);

	_menu.SetSelector(_selector);
	_menu.SetTitle(_mainTitle);
	_menu.AddItem(level1);
	//_menu.AddItem(ballistics);
	//_menu.AddItem(firework);
	//_menu.AddItem(springs);
	_menu.AddItem(opengl);

}

void MainMenu::v_Update(void)
{
	KE::AudioManager::Instance()->PlaySource(1);
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE))
	{
		KE::AudioManager::Instance()->StopSource(1);
		KE::Engine::Instance()->End();
	}

	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::UP_ARROW))
	{
		_menu.MoveSelectorUp();
	}	

	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::DOWN_ARROW))
	{
		_menu.MoveSelectorDown();
	}


	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ENTER))
	{
		KE::AudioManager::Instance()->StopSource(1);
		_menu.CallSelectedAction();
	}
}