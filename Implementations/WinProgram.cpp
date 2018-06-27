#include <Engine/WinProgram.h>

using namespace KillerEngine;

//==========================================================================================================================
//
//Constructors
//
//==========================================================================================================================   
WinProgram::WinProgram(void) 
: 
_isFullScreen(false),
_totalWidth(0), 
_totalHeight(0),
_right(0), 
_left(0),
_top(0), 
_bottom(0),
_wndName("Killer Engine")
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
void WinProgram::Init(S32 width, S32 height, string wndName, bool isFullScreen) 
{

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
    _window = glfwCreateWindow(width, height, wndName.c_str(), NULL, NULL);

    if(_window == NULL)
    {
    	ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to create GLFW window. WinProgram.");
    }

    glfwMakeContextCurrent(_window);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
    	ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to init glew. WinProgram.");
    }
}

void WinProgram::ProcessEvents(void)
{

}

//=======================================================================================================
//BufferSwap
//=======================================================================================================
void WinProgram::BufferSwap(void)
{ 
    glfwSwapBuffers(_window);
   // glClearBufferfv(GL_COLOR, 0, _bgColor);
}

void WinProgram::SetBackgroundColor(const Color& c) 
{
	_bgColor[0] = c.GetRed();
	_bgColor[1] = c.GetGreen();
	_bgColor[2] = c.GetBlue();
	_bgColor[3] = c.GetAlpha();

}