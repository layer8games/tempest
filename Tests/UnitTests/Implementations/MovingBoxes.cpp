#include <Boxes/MovingBoxes.h>
#include <iostream>

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
_levelTitle(),
_activeBox(nullptr)
{  }

MovingBoxes::~MovingBoxes(void) {  }

//=============================================================================
//
//InitLevel
//
//=============================================================================
void MovingBoxes::v_InitLevel(U32 id, S32 w, S32 h, const KE::Color& c) 
{ 
	Level::SetID(id);
	Level::SetLevelWidth(w);
	Level::SetLevelHeight(h);
	Level::SetBackgroundColor(c);

	F32 width = static_cast<F32>(w);
	F32 height = static_cast<F32>(h);

	_left = KE::WinProgram::Instance()->GetScreenLeft();
	_right = KE::WinProgram::Instance()->GetScreenRight();
	_bottom = KE::WinProgram::Instance()->GetScreenBottom();
	_top = KE::WinProgram::Instance()->GetScreenTop();

	_levelTitle.SetFont(KE::FontManager::Instance()->GetFont(100));
	_levelTitle.AddText("Moving Boxes");
	_levelTitle.SetPosition(KM::Point(-_levelTitle.GetWidth(), _top - (_top * 0.1f)));
	Level::AddTextToLevel(_levelTitle);

	_redbox.SetPosition(0.0f, _top / 3.0f);
	_redbox.SetTexture(KE::TextureManager::Instance()->GetTexture(100));
	_redbox.SetScale(25.0f, 25.0f);
	_redbox.InitBounding();
	Level::AddObjectToLevel(_redbox);

	_greenbox.SetPosition(_left / 3.0f, 0.0f);
	_greenbox.SetTexture(KE::TextureManager::Instance()->GetTexture(101));
	_greenbox.SetScale(25.0f, 25.0f);
	_greenbox.InitBounding();
	Level::AddObjectToLevel(_greenbox);

	_bluebox.SetPosition(_right / 3.0f, 0.0f);
	_bluebox.SetTexture(KE::TextureManager::Instance()->GetTexture(102));
	_bluebox.SetScale(25.0f, 25.0f);
	_bluebox.InitBounding();
	Level::AddObjectToLevel(_bluebox);

	_activeBox = &_redbox;
}

//=============================================================================
//
//Update
//
//=============================================================================
void MovingBoxes::v_Update(void) 
{
	if(KE::Controller::Instance()->GetKeyDown(KE::Keys::ESCAPE)) 
	{ 
		KE::LevelManager::Instance()->SetActiveLevel(2); 
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
	if(_redbox.OverlapCheck(_greenbox))
	{
		_redbox.OnCollide();
	}

	if(_redbox.OverlapCheck(_bluebox))
	{
		_redbox.OnCollide();
	}
}