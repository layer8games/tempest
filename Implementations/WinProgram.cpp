#include <Engine/WinProgram.h>
#include <iostream>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================   
WinProgram::WinProgram(void) 
: 
_isFullScreen(false),
_running(false),
_totalWidth(0), 
_totalHeight(0),
_right(0), 
_left(0),
_top(0), 
_bottom(0),
_wndName("Killer Engine"),
_bgColor(),
_window(nullptr)
{  }

WinProgram::~WinProgram(void)
{  }
//==========================================================================================================================
//
//WinProgram Functions
//
//==========================================================================================================================
//=======================================================================================================
//Instance
//=======================================================================================================
shared_ptr<WinProgram> WinProgram::_instance = NULL;

shared_ptr<WinProgram> WinProgram::Instance(void) 
{
    if(_instance == NULL) 
    { 
        _instance = shared_ptr<WinProgram>(new WinProgram());
    }
    return _instance;
}

//=======================================================================================================
//InitWindow
//=======================================================================================================    
void WinProgram::OnKey(GLFWwindow* window, int key, int scancode, int action, int mode)
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

void WinProgram::Init(S32 width, S32 height, string wndName, bool isFullScreen) 
{
	_running = true;
	_isFullScreen = isFullScreen;
	_totalWidth = width;
	_totalHeight = height;

	_right = _totalWidth;
	_left = 0;
	_top = _totalHeight;
	_bottom = 0;

    if(!glfwInit())
    {
    	ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to init GLFW. WinProgram.");
    }

    //Set up your opengl context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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
    		_right = _totalWidth;
    		_left = 0;
    		_top = _totalHeight;
    		_bottom = 0;
    		
    		_window = glfwCreateWindow(_totalWidth, _totalHeight, wndName.c_str(), monitor, NULL);
    	}
    }
    else
    {
    	_window = glfwCreateWindow(_totalWidth, _totalHeight, wndName.c_str(), NULL, NULL);	
    }
    
    if(_window == NULL)
    {
    	ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to create GLFW window. WinProgram.");
    }

    glfwMakeContextCurrent(_window);

    glfwSetKeyCallback(_window, OnKey);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
    	ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to init glew. WinProgram.");
    }
}

void WinProgram::ProcessEvents(void)
{
	glfwPollEvents();
}

//=======================================================================================================
//BufferSwap
//=======================================================================================================
void WinProgram::BufferSwap(void)
{ 
    glfwSwapBuffers(_window);
    glClear(GL_COLOR_BUFFER_BIT);
}

Keys WinProgram::ConvertKeyCodes(int key)
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
        default:
            return Keys::NO_KEY;
    }
}

void WinProgram::DisplayFPS(void)
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