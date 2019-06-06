#include <Boxes/MovingBoxes.h>

using namespace Boxes;

//=============================================================================
//
//Constructor
//
//=============================================================================
MovingBoxes::MovingBoxes(void)
:
_left(0.0f),
_right(0.0f), 
_bottom(0.0f),
_top(0.0f),
_redbox(),
_bluebox(),
_greenbox(),
_levelTitle()
//_activeBox(nullptr)
{  }

MovingBoxes::~MovingBoxes(void) 
{
	//_activeBox = nullptr;
}

//=============================================================================
//
//InitLevel
//
//=============================================================================
void MovingBoxes::v_Init(void) 
{ 

	Level::SetID(MOVING_BOXES_ID);
	Level::SetWidth(KE::GameWindow::Instance()->GetWidth());
	Level::SetHeight(KE::GameWindow::Instance()->GetHeight());
	Level::SetBackgroundColor(KE::Color(0.2f, 0.2f, 0.2f));

	F32 width = static_cast<F32>(KE::GameWindow::Instance()->GetWidth());
	F32 height = static_cast<F32>(KE::GameWindow::Instance()->GetHeight());

	_left = KE::GameWindow::Instance()->GetScreenLeft();
	_right = KE::GameWindow::Instance()->GetScreenRight();
	_bottom = KE::GameWindow::Instance()->GetScreenBottom();
	_top = KE::GameWindow::Instance()->GetScreenTop();

	_levelTitle.SetFont(KE::FontManager::Instance()->GetFont(100));
	_levelTitle.AddText("Moving Boxes");
	_levelTitle.SetPosition(KM::Point(-_levelTitle.GetWidth(), _top - (_top * 0.1f)));
	Level::AddTextToLevel(_levelTitle);

	_redbox.SetPosition(0.0f, _top / 3.0f);
	_redbox.SetTexture(KE::TextureManager::Instance()->GetTexture(100));
	_redbox.SetScale(32.0f, 32.0f);
	_redbox.InitBounding();
	Level::AddObjectToLevel(shared_ptr<Box>(&_redbox));

	_greenbox.SetPosition(_left / 3.0f, 0.0f);
	_greenbox.SetTexture(KE::TextureManager::Instance()->GetTexture(101));
	_greenbox.SetScale(32.0f, 32.0f);
	_greenbox.InitBounding();
	//Level::AddObjectToLevel(_greenbox);

	_bluebox.SetPosition(_right / 3.0f, 0.0f);
	_bluebox.SetTexture(KE::TextureManager::Instance()->GetTexture(102));
	_bluebox.SetScale(32.0f, 32.0f);
	_bluebox.InitBounding();
	//Level::AddObjectToLevel(_bluebox);

	//_activeBox = &_redbox;	
}

//=============================================================================
//
//Update
//
//=============================================================================
void MovingBoxes::v_Update(void) 
{
/*	
	KE::AudioManager::Instance()->PlaySource(2);
	
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE)) 
	{ 
		KE::AudioManager::Instance()->StopSource(2);
		KE::LevelManager::Instance()->SetActiveLevel(MAIN_MENU_ID); 
	}

	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ONE)) 
	{ 
		_activeBox = &_redbox;
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::TWO)) 
	{ 
		_activeBox = &_greenbox; 
	}
	else if(KE::Controller::Instance()->GetKeyDown(KE::Keys::THREE)) 
	{ 
		_activeBox = &_bluebox;
	}

	bool up = KE::Controller::Instance()->GetKeyDown(KE::Keys::UP_ARROW);
	bool down = KE::Controller::Instance()->GetKeyDown(KE::Keys::DOWN_ARROW);
	bool left = KE::Controller::Instance()->GetKeyDown(KE::Keys::LEFT_ARROW);
	bool right = KE::Controller::Instance()->GetKeyDown(KE::Keys::RIGHT_ARROW);

	if(up)	  
	{ 
		_activeBox->SetDirection(0.0f, 1.0f);
	}
	else if(down)  
	{ 
		_activeBox->SetDirection(0.0f, -1.0f);
	}
	else if(right) 
	{ 
		_activeBox->SetDirection(1.0f, 0.0f);
	}
	else if(left)  
	{ 
		_activeBox->SetDirection(-1.0f, 0.0f);
	}
	
	if(up && right)
	{ 
		_activeBox->SetDirection(1.0f, 1.0f);	
	}
	else if(up && left)
	{
		_activeBox->SetDirection(-1.0f, 1.0f);
	}
	else if(down && right) 
	{ 
		_activeBox->SetDirection(1.0f, -1.0f);
	}
	else if(down && left)  
	{ 
		_activeBox->SetDirection(-1.0f, -1.0f);
	}
	
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::SPACE))
	{
		_activeBox->SetDirection(0.0f, 0.0f);
	}

	CheckBoxEdge(_redbox);
	CheckBoxEdge(_greenbox);
	CheckBoxEdge(_bluebox);

	CheckCollisions();
*/	
}//End update

//==========================================================================================================================
//
//MovingBoxes functions
//
//==========================================================================================================================	
void MovingBoxes::CheckBoxEdge(KE::GameObject& b)
{
	KM::Point tempPos = b.GetPosition();

	//Righ/Left check
	if(tempPos[0] >= _right) 
	{
		tempPos[0] = _left;
	}
	else if(tempPos[0] <= _left) 
	{
		tempPos[0] = _right;
	}
	
	//Top/Bottom check
	if(tempPos[1] >= _top) 
	{
		tempPos[1] = _bottom;
	}
	else if(tempPos[1] <= _bottom) 
	{
		tempPos[1] = _top;
	}

	b.SetPosition(tempPos);
}

void MovingBoxes::CheckCollisions(void)
{
/*
	if(_redbox.OverlapCheck(_greenbox) || _redbox.OverlapCheck(_bluebox))
	{
		_redbox.OnCollide();
	}

	if(_greenbox.OverlapCheck(_redbox) || _greenbox.OverlapCheck(_bluebox))
	{
		_greenbox.OnCollide();
	}

	if(_bluebox.OverlapCheck(_redbox) || _bluebox.OverlapCheck(_greenbox))
	{
		_bluebox.OnCollide();
	}
*/
}