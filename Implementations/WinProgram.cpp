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
_wndName("Killer Engine"),
_hwnd(NULL),
_hdc(NULL),
_hglrc(NULL),
_wndClass()
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
    _totalWidth     = width;
    _totalHeight    = height;
    _right          = _totalWidth / 2;
    _left           = -_totalWidth / 2;
    _top            = _totalHeight / 2;
    _bottom         = -_totalHeight / 2;

    //=========Window Class registration and creation===========
	_wndClass.cbSize        = sizeof(WNDCLASSEX);
    _wndClass.style 		= CS_HREDRAW | CS_VREDRAW; //| CS_OWNDC; //Window Style
	_wndClass.lpfnWndProc   = &StaticWndProc; 	    //Windows Proc Callback function
	_wndClass.cbClsExtra    = 0;
    _wndClass.cbWndExtra    = 0;
	_wndClass.hInstance		= GetModuleHandle(NULL);//_hInstance;
    _wndClass.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    _wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
    _wndClass.hbrBackground = NULL;
	_wndClass.lpszMenuName  = NULL;
	_wndClass.lpszClassName = _wndName.c_str();
    _wndClass.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&_wndClass))
		ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to register window class");


	_hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
				   		   _wndName.c_str(),					    //Window Class name
				   		   _wndName.c_str(),						//Window Name
				   		   WS_CLIPSIBLINGS 	   | WS_CLIPCHILDREN |  //Window Styles
				   		   WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_CAPTION,		//^           ^
				   	  	   0,0,										//position of window
				   		   _totalWidth, _totalHeight,				//Dimensions
				   		   NULL, 									//Parent Window
				   		   NULL, 									//Window Menu
				   		   _wndClass.hInstance,						//hInstance,
				   		   this); 									//lpParam
	if (!_hwnd)
		ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to create HWND");

	SetWindowLong(_hwnd, GWL_STYLE, WS_BORDER);

    _hdc = GetDC(_hwnd);

    if(!_hdc)
    	ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to get HDC");

    ShowWindow(_hwnd, SW_SHOW);
    UpdateWindow(_hwnd);

    Controller::Instance()->Init((F32)width, (F32)height, 200.0f);
}

//=======================================================================================================
//ProcessWndEvents
//=======================================================================================================
void WinProgram::ProcessWndEvents(void) 
{
    MSG msg;

    while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

//=======================================================================================================
//BufferSwap
//=======================================================================================================
void WinProgram::BufferSwap(void)
{ 
    glFlush(); 
    SwapBuffers(_hdc); 
    glClearBufferfv(GL_COLOR, 0, _bgColor);
}
//==========================================================================================================================
//
//System Windows Functions
//
//==========================================================================================================================
//=======================================================================================================
//StaticWndProc
//=======================================================================================================    
LRESULT CALLBACK WinProgram::StaticWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	WinProgram* window = NULL;

    if(uMsg == WM_CREATE) 
    {
        window = (WinProgram*)((LPCREATESTRUCT)lParam)->lpCreateParams;

        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)window);
    }
    else 
    {
        window = (WinProgram*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

		if (!window)
			DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return window->WndProc(hWnd, uMsg, wParam, lParam);
}

//=======================================================================================================
//WndProc
//=======================================================================================================    
LRESULT WinProgram::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
    switch(uMsg) 
    {
        case WM_CREATE: 
        {
			_hdc = GetDC(hWnd);
		    
			//=====Create temporary context=====
			_SetTempPixelFormat();            
            HGLRC hrcTemp = wglCreateContext(_hdc);
            wglMakeCurrent(_hdc, hrcTemp);

			//=====Create Real Context=====
            _SetPixelFormat();
            
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
            wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
            
            if(!wglCreateContextAttribsARB)
            	ErrorManager::Instance()->SetError(EC_OpenGL, "Unable to get wglCreateContextAttribsARB function Vecer");

            GLint contextARBS[] = 
            {
                WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
                WGL_CONTEXT_MINOR_VERSION_ARB, 2,
                WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
                0
            };

            _hglrc = wglCreateContextAttribsARB(_hdc, 0, contextARBS);

            if(!_hglrc)
            	ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to create wgl Context");

            wglMakeCurrent(_hdc, _hglrc);
            wglDeleteContext(hrcTemp);

            if (gl3wInit())
            	ErrorManager::Instance()->SetError(EC_OpenGL, "gl3wInit() failed");

           // glEnable(GL_DEPTH_TEST);

            break;
        }
        case WM_DESTROY: 
        {
            _hdc = GetDC(hWnd);
            wglMakeCurrent(_hdc, NULL); 
			wglDeleteContext(_hglrc); 
			DestroyWindow(hWnd);
            PostQuitMessage(0);
            break;
        }
        //case WM_SIZE: {
          /*  _width  = LOWORD(lParam);
            _height = HIWORD(lParam);
            
            _halfWidth  = _width / 2;
            _halfHeight = _height / 2;

            //_OnResize(); */
        //}
        //break;
        case WM_KEYDOWN:
        {
            Keys keydown = ConvertKeyCodes(wParam);
            Controller::Instance()->KeyDown(keydown);
            break;
        }
        case WM_KEYUP:
        {
            Keys keyup = ConvertKeyCodes(wParam);
            Controller::Instance()->KeyUp(keyup);
            break;
        }
        case WM_LBUTTONDOWN:
        {
            POINT p;
            if(!GetCursorPos(&p)) { ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to find Left Cursor Position in WinProgram!"); }
            if(!ScreenToClient(_hwnd, &p)) { ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to convert Left Cursor to client in WinProgram!"); }
            Controller::Instance()->LeftMouseClick(KM::Vector2((F32)p.x, (F32)p.y));
            Controller::Instance()->KeyDown(Keys::LEFT_MOUSE);
            break; 
        }
        case WM_LBUTTONUP:
        {
            Controller::Instance()->KeyUp(Keys::LEFT_MOUSE);
            Controller::Instance()->LeftMouseClick(KM::Vector2(0.0f, 0.0f));
            break;
        }
        case WM_RBUTTONDOWN:
        {
            POINT p;
            if(!GetCursorPos(&p)) { ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to find Right Cursor Position in WinProgram!"); }
            if(!ScreenToClient(_hwnd, &p)) { ErrorManager::Instance()->SetError(EC_KillerEngine, "Unable to convert Right Cursor to client in WinProgram!"); }
            Controller::Instance()->RightMouseClick(KM::Vector2((F32)p.x, (F32)p.y));
            Controller::Instance()->KeyDown(Keys::RIGHT_MOUSE);
            break;
        }
        case WM_RBUTTONUP:
        {
            Controller::Instance()->KeyUp(Keys::RIGHT_MOUSE);
            Controller::Instance()->RightMouseClick(KM::Vector2(0.0f, 0.0f));
            break;
        }
        default:
        	return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
	return 0;
}

Keys WinProgram::ConvertKeyCodes(WPARAM wParam)
{
    switch(wParam)
    {
        case 'A':
            return Keys::A;
        case 'B':
            return Keys::B;
        case 'C':
            return Keys::C;
        case 'D':
            return Keys::D;
        case 'E':
            return Keys::E;
        case 'F':
            return Keys::F;
        case 'G':
            return Keys::G;
        case 'H':
            return Keys::H;
        case 'I':
            return Keys::I;
        case 'J':
            return Keys::J;
        case 'K':
            return Keys::K;    
        case 'L':
            return Keys::L;
        case 'M':
            return Keys::M;
        case 'N':
            return Keys::N;
        case 'O':
            return Keys::O;
        case 'P':
            return Keys::P;
        case 'Q':
            return Keys::Q;
        case 'R':
            return Keys::R;
        case 'S':
            return Keys::S;
        case 'T':
            return Keys::T;
        case 'U':
            return Keys::U;
        case 'V':
            return Keys::V;
        case 'W':
            return Keys::W;
        case 'X':
            return Keys::X;
        case 'Y':
            return Keys::Y;
        case 'Z':
            return Keys::Z;
        case VK_UP:
            return Keys::UP_ARROW;
        case VK_DOWN:
            return Keys::DOWN_ARROW;
        case VK_LEFT:
            return Keys::LEFT_ARROW;
        case VK_RIGHT:
            return Keys::RIGHT_ARROW;
        case '0':
            return Keys::ZERO;
        case '1':
            return Keys::ONE;
        case '2':
            return Keys::TWO;
        case '3':
            return Keys::THREE;
        case '4':
            return Keys::FOUR;
        case '5':
            return Keys::FIVE;
        case '6':
            return Keys::SIX;
        case '7':
            return Keys::SEVEN;
        case '8':
            return Keys::EIGHT;
        case '9':
            return Keys::NINE;
        case VK_OEM_MINUS:
            return Keys::MINUS;
        case VK_OEM_PLUS:
            return Keys::PLUS;
        case VK_SPACE:
            return Keys::SPACE;
        case VK_ESCAPE:
            return Keys::ESCAPE;
        case VK_TAB:
            return Keys::TAB;
        case VK_LSHIFT:
            return Keys::LSHIFT;
        case VK_RSHIFT:
            return Keys::RSHIFT;
        case VK_RETURN:
            return Keys::ENTER;
        case VK_XBUTTON1:
            return Keys::MIDDLE_MOUSE;
        default:
            return Keys::NO_KEY;
    }
}

//=======================================================================================================
//_SetTempPixelFormat
//=======================================================================================================
void WinProgram::_SetTempPixelFormat(void) 
{
    S32 pixelFormat;

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),  //size
        1,                              //version
        PFD_SUPPORT_OPENGL |            //OpenGL window
        PFD_DRAW_TO_WINDOW |            //render to window
        PFD_DOUBLEBUFFER,               //support double buffer
        PFD_TYPE_RGBA,                  //color type
        32,                             //prefered color depth
        0,0,0,0,0,0,                    //color bits (ignored)
        0,                              //no alpha buffer
        0,                              //alpha bits ignored
        0,                              //no accumulation buffer
        0,0,0,0,                        //accum bits (ignored)
        16,                             //depth buffer
        0,                              //no stencil buffer
        0,                              //no aux buffers
        PFD_MAIN_PLANE,                 //main layer
        0,                              //reserved
        0,0,0                           //no layer, visible, damage masks

    };

    pixelFormat = ChoosePixelFormat(_hdc, &pfd);    
    SetPixelFormat(_hdc, pixelFormat, &pfd);
}

//=======================================================================================================
//_SetPixelFormat
//=======================================================================================================
void WinProgram::_SetPixelFormat(void) 
{
    bool worked = true;

    //PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionstextARB = NULL; 
    //wglGetExtensionstextARB = (PFNWGLGETEXTENSIONSSTRINGARBPROC)wglGetProcAddress("wglGetExtensionstextARB");
    //if (!wglGetExtensionstextARB){ worked = false; } //{ ErrorManager::Instance()->SetError(EC_OpenGL, "Unable to get wglGetExtensionstextARB function Vecer"); }

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
    if (!wglChoosePixelFormatARB){ worked = false; } //{ ErrorManager::Instance()->SetError(EC_OpenGL, "Unable to get wglChoosePixelFormatARB function Vecer"); }

    int pixCount    = 0;
    int pixelFormat = 0;

    int pixAtrb[] = {
        WGL_SUPPORT_OPENGL_ARB, 1, //Support OGL rendering
        WGL_DRAW_TO_WINDOW_ARB, 1, //pf that can run a window
        WGL_RED_BITS_ARB,       8, //8 bits of RGB color
        WGL_GREEN_BITS_ARB,     8,
        WGL_BLUE_BITS_ARB,      8,
        WGL_DEPTH_BITS_ARB,     16, //16 bits of depth
        WGL_ACCELERATION_ARB,
        WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB,
        WGL_TYPE_RGBA_ARB,
        0};

    wglChoosePixelFormatARB(_hdc,              //device context
                            &pixAtrb[0],       //desired attributes
                            NULL,              //float attribute list
                            1,                 //max returned formats
                            &pixelFormat,      //list of returned formats
                            (UINT*)&pixCount); //number of formats found

    if(pixelFormat == -1) { ErrorManager::Instance()->SetError(EC_OpenGL, "Failed to load Pixel Format"); }

} 