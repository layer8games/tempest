#include <Boxes/MainMenu.h>

using namespace Boxes;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================
MainMenu::MainMenu(void) 
: 
_maxPosition(0),
_selectorPosition(0),
_selector(),
_menuItemFont(),
_mainTitle(),
_menuItem_Level1(),
_menuItem_BallisticsDemo(),
_menuItem_RainDemo(),
_menuItem_LevelFour(),
_menuItem_Fireworks(),
_menuItem_Springs()
{  }

MainMenu::~MainMenu(void) {  }	

//==========================================================================================================================
//
//Virtual Functions
//
//==========================================================================================================================
void MainMenu::v_InitLevel(U32 id, S32 w, S32 h, KE::Color& c)
{
	Level::SetID(id);
	Level::SetLevelWidth(w);
	Level::SetLevelHeight(h);
	Level::SetBackgroundColor(c);

	F32 menuPosX = 0.0f;
	F32 menuPosY = 0.0f;
	F32 nextMenuSpace = menuPosY;
	F32 menuSpacing = 40.0f;
	F32 boxOffest = 50.0f;

	_selector.SetPosition(KM::Point(menuPosX - boxOffest, menuPosY));
	_selector.SetColor(KE::Color(1.0f, 0.0f, 0.0f));
	_selector.SetTexture(KE::TextureManager::Instance()->GetTexture(100));
	_selector.SetScale(25.0f, 25.0f);
	Level::AddObjectToLevel(_selector);

	F32 top = KE::WinProgram::Instance()->GetScreenTop();

	_mainTitle.SetFont(KE::FontManager::Instance()->GetFont(101));
	_mainTitle.AddText("BOXES vs TRIANGLES");
	_mainTitle.SetPosition(KM::Point(-_mainTitle.GetWidth(), top - (top * 0.1f)));
	Level::AddTextToLevel(_mainTitle);

	//Set with title font for now.
	//test with an alternate font later
	//Level One Menu Item
	_menuItem_Level1.SetFont(KE::FontManager::Instance()->GetFont(100));
	_menuItem_Level1.AddText("Moving Boxes");
	_menuItem_Level1.SetPosition(KM::Point(menuPosX, nextMenuSpace));
	Level::AddTextToLevel(_menuItem_Level1);

	_itemPositions[0] = KM::Point(menuPosX - boxOffest, nextMenuSpace);
	nextMenuSpace -= menuSpacing;
	
	//Ballistic Demo menu item
	++_maxPosition;
	_menuItem_BallisticsDemo.SetFont(KE::FontManager::Instance()->GetFont(100));
	_menuItem_BallisticsDemo.AddText("Ballistic");
	_menuItem_BallisticsDemo.SetPosition(KM::Point(menuPosX, nextMenuSpace));
	Level::AddTextToLevel(_menuItem_BallisticsDemo);

	_itemPositions[1] = KM::Point(menuPosX - boxOffest, nextMenuSpace);
	nextMenuSpace -= menuSpacing;

	//Fireworks menu item
	++_maxPosition;
	_menuItem_Fireworks.SetFont(KE::FontManager::Instance()->GetFont(100));
	_menuItem_Fireworks.AddText("Firework Demo");
	_menuItem_Fireworks.SetPosition(KM::Point(menuPosX, nextMenuSpace));
	Level::AddTextToLevel(_menuItem_Fireworks);

	_itemPositions[2] = KM::Point(menuPosX - boxOffest, nextMenuSpace);
	nextMenuSpace -= menuSpacing;

	//Springs menu item
	++_maxPosition;
	_menuItem_Springs.SetFont(KE::FontManager::Instance()->GetFont(100));
	_menuItem_Springs.AddText("Springs Demo");
	_menuItem_Springs.SetPosition(KM::Point(menuPosX, nextMenuSpace));
	Level::AddTextToLevel(_menuItem_Springs);

	_itemPositions[3] = KM::Point(menuPosX - boxOffest, nextMenuSpace);
	nextMenuSpace -= menuSpacing;

	//Springs menu item
	++_maxPosition;
	_menuItem_Springs.SetFont(KE::FontManager::Instance()->GetFont(100));
	_menuItem_Springs.AddText("3D Level");
	_menuItem_Springs.SetPosition(KM::Point(menuPosX, nextMenuSpace));
	Level::AddTextToLevel(_menuItem_Springs);

	_itemPositions[4] = KM::Point(menuPosX - boxOffest, nextMenuSpace);
	nextMenuSpace -= menuSpacing;
}

void MainMenu::v_Update(void)
{
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE))
	{
		KE::Engine::Instance()->End();
	}


	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::UP_ARROW))
	{
		if(_selectorPosition != 0) 
		{
			--_selectorPosition;
		}
	}	

	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::DOWN_ARROW))
	{
		if(_selectorPosition != _maxPosition) 
		{
			++_selectorPosition;
		}
	}

	switch(_selectorPosition)
	{
		case 0: _selector.SetPosition(_itemPositions[0]);
		break;
		case 1: _selector.SetPosition(_itemPositions[1]);
		break;
		case 2: _selector.SetPosition(_itemPositions[2]);
		break;
		case 3: _selector.SetPosition(_itemPositions[3]);
		break;
		case 4: _selector.SetPosition(_itemPositions[4]);
		break;
		//case 5: _selector.SetPosition(_itemPositions[5]);
		//break;
		default: 
		break;
	}

	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ENTER))
	{
		switch(_selectorPosition)
		{
			case 0: KE::Engine::Instance()->SetActiveLevel(3);
			break;
			case 1: KE::Engine::Instance()->SetActiveLevel(4);
			break;
			case 2: KE::Engine::Instance()->SetActiveLevel(5);
			break;
			case 3: KE::Engine::Instance()->SetActiveLevel(6);
			break;
			case 4: KE::Engine::Instance()->SetActiveLevel(7);
			break;
			//case 5: KE::Engine::Instance()->SetActiveLevel(8);
			//break;
			default:
			break;
		}
	}
}