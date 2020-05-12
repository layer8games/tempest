#include "stdafx.h"
#include <Engine/OpenGLGameWindow.h>
using namespace Tempest;
   
OpenGLGameWindow::OpenGLGameWindow(void) 
    :
    _window(nullptr)
{  }

OpenGLGameWindow::~OpenGLGameWindow(void)
{
    glfwDestroyWindow(_window);
}

void OpenGLGameWindow::v_Init(S32 width, S32 height, string wndName, bool isFullScreen) 
{
    _isFullScreen = isFullScreen;
    _screenWidth = width;
    _screenHeight = height;

    _right = static_cast<F32>(_screenWidth) / 2.0f;
    _left = -static_cast<F32>(_screenWidth) / 2.0f;
    _top = static_cast<F32>(_screenHeight) / 2.0f;
    _bottom = -static_cast<F32>(_screenHeight) / 2.0f;

    if(!glfwInit())
    {
        ErrorManager::Instance()->SetError(OPENGL, "Failed to init GLFW. OpenGLGameWindow.");
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
            _screenWidth = vidMode->width;
            _screenHeight = vidMode->height;
            
            _window = glfwCreateWindow(_screenWidth, _screenHeight, wndName.c_str(), monitor, NULL);
        }
    }
    else
    {
        _window = glfwCreateWindow(_screenWidth, _screenHeight, wndName.c_str(), NULL, NULL);	
    }
    
    if(_window == NULL)
    {
        ErrorManager::Instance()->SetError(OPENGL, "Failed to create GLFW window. OpenGLGameWindow.");
    }

    glfwMakeContextCurrent(_window);

    glfwSetKeyCallback(_window, OnKey);
    glfwSetWindowSizeCallback(_window, OnResize);
    glfwSetMouseButtonCallback(_window, OnMouseClick);
    //glfwSetCursorPosCallback(_window, OnMouseMove);

    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        ErrorManager::Instance()->SetError(OPENGL, "Failed to init glew. OpenGLGameWindow.");
    }

    glViewport(0, 0, _screenWidth, _screenHeight);
    glEnable(GL_DEPTH_TEST);
}

void OpenGLGameWindow::v_ProcessEvents(void)
{
    glfwPollEvents();
}

void OpenGLGameWindow::v_BufferSwap(void)
{ 
    glfwSwapBuffers(_window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLGameWindow::v_DisplayFPS(void)
{
    static F64 elapsed = 0.0f;
    static U32 frameCount = 0;

    F32 delta = TM::Timer::Instance()->DeltaTime();

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

void OpenGLGameWindow::v_ToggleWireFrame(void)
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

void OpenGLGameWindow::v_ResetMouseCursor(void)
{
    glfwSetCursorPos(_window, _screenWidth / 2.0f, _screenHeight / 2.0f);
}

void OpenGLGameWindow::v_EnableMouseCursor(void)
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void OpenGLGameWindow::v_DisableMouseCursor(void)
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void OpenGLGameWindow::v_HideMouseCursor(void)
{
    glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

const TM::Point2 OpenGLGameWindow::v_GetMousePos(void)
{
    F64 mouseX, mouseY;
    glfwGetCursorPos(_window, &mouseX, &mouseY); 

    return TM::Point2(static_cast<real>(mouseX), static_cast<real>(mouseY));
}

const TM::Point2 OpenGLGameWindow::v_GetMousePosInScreen(void)
{
    F64 mouseX, mouseY;
    glfwGetCursorPos(_window, &mouseX, &mouseY);

    //Flips y, sets origin at bottom left of screen
    mouseY = _screenHeight - mouseY;
    
    //Moves coords to be relative to middle. 
    mouseX = mouseX + _left;
    mouseY = mouseY + _bottom;

    //TODO:: This should probably be done through a Matrix4 transform
    //but for now, this seems way easier. 

    return TM::Point2(static_cast<real>(mouseX), static_cast<real>(mouseY));
}

F64 OpenGLGameWindow::v_GetTime(void)
{
    return glfwGetTime();
}

void OpenGLGameWindow::v_EndRunning(void)
{
    glfwSetWindowShouldClose(_window, GL_TRUE);
}

void OpenGLGameWindow::v_SetScreenColor(const Color& col)
{
    glClearColor(col[0], col[1], col[2], col[3]);
}

//==========================================================================================================================
//
//Callback Functions
//
//==========================================================================================================================
//=======================================================================================================
//OnKey
//=======================================================================================================    
void OpenGLGameWindow::OnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        Controller::Instance()->KeyDown(_ConvertKeyCodes(key));
    }
    else if(action == GLFW_RELEASE)
    {
        Controller::Instance()->KeyUp(_ConvertKeyCodes(key));
    }
}

//==========================================================================================================================
//OnResize
//==========================================================================================================================
void OpenGLGameWindow::OnResize(GLFWwindow* window, int width, int height)
{
    _screenWidth = width;
    _screenHeight = height;
    glViewport(0, 0, _screenWidth, _screenHeight);
}

//==========================================================================================================================
//OnMouseMove
//==========================================================================================================================
void OpenGLGameWindow::OnMouseClick(GLFWwindow* window, int button, int action, int mods)
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
void OpenGLGameWindow::OnMouseMove(GLFWwindow* window, F64 posX, F64 posY)
{
    //Controller::Instance()->SetMouseCoord(TM::Vector4(static_cast<F32>(posX), static_cast<F32>(posY)));
}

Keys OpenGLGameWindow::_ConvertKeyCodes(int key)
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