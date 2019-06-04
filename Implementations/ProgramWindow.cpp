#include <Engine/ProgramWindow.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================   
ProgramWindow::ProgramWindow(void) 
: 
_isFullScreen(false),
_running(false),
_wireFrame(false),
_right(0), 
_left(0),
_top(0), 
_bottom(0),
_wndName("Killer Engine"),
_bgColor(),
_window(nullptr)
{  }

ProgramWindow::~ProgramWindow(void)
{  }
//==========================================================================================================================
//
//ProgramWindow Functions
//
//==========================================================================================================================
//=======================================================================================================
//Instance
//=======================================================================================================
shared_ptr<ProgramWindow> ProgramWindow::_instance = NULL;
int ProgramWindow::_totalWidth = 0;
int ProgramWindow::_totalHeight = 0;

shared_ptr<ProgramWindow> ProgramWindow::Instance(void) 
{
    if(_instance == NULL) 
    { 
        _instance = shared_ptr<ProgramWindow>(new ProgramWindow());
    }
    return _instance;
}

//==========================================================================================================================
//Init
//==========================================================================================================================
void ProgramWindow::Init(S32 width, S32 height, string wndName, bool isFullScreen) 
{
	_running = true;
	_isFullScreen = isFullScreen;
	_totalWidth = width;
	_totalHeight = height;

	_right = static_cast<F32>(_totalWidth) / 2.0f;
	_left = -static_cast<F32>(_totalWidth) / 2.0f;
	_top = static_cast<F32>(_totalHeight) / 2.0f;
	_bottom = -static_cast<F32>(_totalHeight) / 2.0f;

    if(!glfwInit())
    {
    	ErrorManager::Instance()->SetError(OPENGL, "Failed to init GLFW. ProgramWindow.");
    }

    //Set up your opengl context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //create window
    if(_isFullScreen)
    {
    	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    	const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
    	
    	if(vidMode != NULL)
    	{
    		_totalWidth = vidMode->width;
    		_totalHeight = vidMode->height;
    		
    		_window = glfwCreateWindow(_totalWidth, _totalHeight, wndName.c_str(), monitor, NULL);
    	}
    }
    else
    {
    	_window = glfwCreateWindow(_totalWidth, _totalHeight, wndName.c_str(), NULL, NULL);	
    }
    
    if(_window == NULL)
    {
    	ErrorManager::Instance()->SetError(OPENGL, "Failed to create GLFW window. ProgramWindow.");
    }

    glfwMakeContextCurrent(_window);

    glfwSetKeyCallback(_window, OnKey);
    glfwSetWindowSizeCallback(_window, OnResize);
    glfwSetMouseButtonCallback(_window, OnMouseClick);
    //glfwSetCursorPosCallback(_window, OnMouseMove);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
    	ErrorManager::Instance()->SetError(OPENGL, "Failed to init glew. ProgramWindow.");
    }

    glViewport(0, 0, _totalWidth, _totalHeight);
    glEnable(GL_DEPTH_TEST);
}

void ProgramWindow::ProcessEvents(void)
{
	glfwPollEvents();
}

//=======================================================================================================
//BufferSwap
//=======================================================================================================
void ProgramWindow::BufferSwap(void)
{ 
    glfwSwapBuffers(_window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Keys ProgramWindow::ConvertKeyCodes(int key)
{
    switch(key)
    {
        case GLFW_KEY_A:
            return Keys::A;
        case GLFW_KEY_B:
            return Keys::B;
        case GLFW_KEY_C:
            return Keys::C;
        case GLFW_KEY_D:
            return Keys::D;
        case GLFW_KEY_E:
            return Keys::E;
        case GLFW_KEY_F:
            return Keys::F;
        case GLFW_KEY_G:
            return Keys::G;
        case GLFW_KEY_H:
            return Keys::H;
        case GLFW_KEY_I:
            return Keys::I;
        case GLFW_KEY_J:
            return Keys::J;
        case GLFW_KEY_K:
            return Keys::K;    
        case GLFW_KEY_L:
            return Keys::L;
        case GLFW_KEY_M:
            return Keys::M;
        case GLFW_KEY_N:
            return Keys::N;
        case GLFW_KEY_O:
            return Keys::O;
        case GLFW_KEY_P:
            return Keys::P;
        case GLFW_KEY_Q:
            return Keys::Q;
        case GLFW_KEY_R:
            return Keys::R;
        case GLFW_KEY_S:
            return Keys::S;
        case GLFW_KEY_T:
            return Keys::T;
        case GLFW_KEY_U:
            return Keys::U;
        case GLFW_KEY_V:
            return Keys::V;
        case GLFW_KEY_W:
            return Keys::W;
        case GLFW_KEY_X:
            return Keys::X;
        case GLFW_KEY_Y:
            return Keys::Y;
        case GLFW_KEY_Z:
            return Keys::Z;
        case GLFW_KEY_UP:
            return Keys::UP_ARROW;
        case GLFW_KEY_DOWN:
            return Keys::DOWN_ARROW;
        case GLFW_KEY_LEFT:
            return Keys::LEFT_ARROW;
        case GLFW_KEY_RIGHT:
            return Keys::RIGHT_ARROW;
        case GLFW_KEY_0:
            return Keys::ZERO;
        case GLFW_KEY_1:
            return Keys::ONE;
        case GLFW_KEY_2:
            return Keys::TWO;
        case GLFW_KEY_3:
            return Keys::THREE;
        case GLFW_KEY_4:
            return Keys::FOUR;
        case GLFW_KEY_5:
            return Keys::FIVE;
        case GLFW_KEY_6:
            return Keys::SIX;
        case GLFW_KEY_7:
            return Keys::SEVEN;
        case GLFW_KEY_8:
            return Keys::EIGHT;
        case GLFW_KEY_9:
            return Keys::NINE;
        case GLFW_KEY_MINUS:
            return Keys::MINUS;
        case GLFW_KEY_EQUAL:
            return Keys::EQUAL;
        case GLFW_KEY_SPACE:
            return Keys::SPACE;
        case GLFW_KEY_ESCAPE:
            return Keys::ESCAPE;
        case GLFW_KEY_TAB:
            return Keys::TAB;
        case GLFW_KEY_LEFT_SHIFT:
            return Keys::LSHIFT;
        case GLFW_KEY_RIGHT_SHIFT:
            return Keys::RSHIFT;
        case GLFW_KEY_ENTER:
            return Keys::ENTER;
        case GLFW_KEY_F1:
            return Keys::F1;
        case GLFW_KEY_F2:
            return Keys::F2;
        case GLFW_KEY_F3:
            return Keys::F3;
        case GLFW_KEY_F4:
            return Keys::F4;
        case GLFW_KEY_F5:
            return Keys::F5;
        case GLFW_KEY_F6:
            return Keys::F6;
        case GLFW_KEY_F7:
            return Keys::F7;
        case GLFW_KEY_F8:
            return Keys::F8;
        case GLFW_KEY_F9:
            return Keys::F9;
        case GLFW_KEY_F10:
            return Keys::F10;
        case GLFW_KEY_F11:
            return Keys::F11;           
        default:
            return Keys::NO_KEY;
    }
}

void ProgramWindow::DisplayFPS(void)
{
	static F64 elapsed = 0.0f;
	static U32 frameCount = 0;

	F32 delta = KM::Timer::Instance()->DeltaTime();

	elapsed += delta;

	if(elapsed > 0.25f)
	{
		F64 fps = static_cast<F64>(frameCount / elapsed);
		F64 msPerFrame = 1000.0 / fps;

		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed
			 << _wndName << "  "
			 << "FPS: " << fps << "    "
			 << "Frame Time: " << msPerFrame << " (ms)";

		glfwSetWindowTitle(_window, outs.str().c_str());

		frameCount = 0;
		elapsed = 0.0f;
	}

	++frameCount;
}

void ProgramWindow::ToggleWireFrame(void)
{
    _wireFrame = !_wireFrame;

    if(_wireFrame)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);   
    }
}

void ProgramWindow::ResetMouseCursor(void)
{
    glfwSetCursorPos(_window, _totalWidth / 2.0f, _totalHeight / 2.0f);
}

void ProgramWindow::EnableMouseCursor(void)
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void ProgramWindow::DisableMouseCursor(void)
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void ProgramWindow::HideMouseCursor(void)
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

const KM::Point ProgramWindow::GetMousePos(void)
{
    F64 mouseX, mouseY;
    glfwGetCursorPos(_window, &mouseX, &mouseY);

    //Flips y, sets origin at bottom left of screen
   // mouseY = _totalHeight - mouseY;
    
    //Moves coords to be relative to middle. 
   // mouseX = mouseX + _left;
   // mouseY = mouseY + _bottom;

    //TODO:: This should probably be done through a Matrix4 transform
    //but for now, this seems way easier. 

    return KM::Point(static_cast<F32>(mouseX), static_cast<F32>(mouseY));
}

const KM::Point ProgramWindow::GetMousePosInScreen(void)
{
    F64 mouseX, mouseY;
    glfwGetCursorPos(_window, &mouseX, &mouseY);

    //Flips y, sets origin at bottom left of screen
    mouseY = _totalHeight - mouseY;
    
    //Moves coords to be relative to middle. 
    mouseX = mouseX + _left;
    mouseY = mouseY + _bottom;

    //TODO:: This should probably be done through a Matrix4 transform
    //but for now, this seems way easier. 

    return KM::Point(static_cast<F32>(mouseX), static_cast<F32>(mouseY));
}

/*
void ProgramWindow::AddMessageBox(string errCode, string errMessage)
{
    MessageBox(NULL, errMessage.c_str(), errCode.c_str(), MB_ICONERROR | MB_OKCANCEL);
}
*/

//==========================================================================================================================
//
//Callback Functions
//
//==========================================================================================================================
//=======================================================================================================
//OnKey
//=======================================================================================================    
void ProgramWindow::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        Controller::Instance()->KeyDown(ConvertKeyCodes(key));
    }
    else if(action == GLFW_RELEASE)
    {
        Controller::Instance()->KeyUp(ConvertKeyCodes(key));
    }
}

//==========================================================================================================================
//OnResize
//==========================================================================================================================
void ProgramWindow::OnResize(GLFWwindow* window, int width, int height)
{
    _totalWidth = width;
    _totalHeight = height;
    glViewport(0, 0, _totalWidth, _totalHeight);
}

//==========================================================================================================================
//OnMouseMove
//==========================================================================================================================
void ProgramWindow::OnMouseClick(GLFWwindow* window, int button, int action, int mods)
{   
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        Controller::Instance()->KeyDown(Keys::LEFT_MOUSE);
    }
    else if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    {
        Controller::Instance()->KeyUp(Keys::LEFT_MOUSE);
    }

    if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        Controller::Instance()->KeyDown(Keys::RIGHT_MOUSE);
    }
    else if(button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    {
        Controller::Instance()->KeyUp(Keys::RIGHT_MOUSE);
    }
}

//==========================================================================================================================
//OnMouseMove
//==========================================================================================================================
void ProgramWindow::OnMouseMove(GLFWwindow* window, F64 posX, F64 posY)
{
    //Controller::Instance()->SetMouseCoord(KM::Vector4(static_cast<F32>(posX), static_cast<F32>(posY)));
}