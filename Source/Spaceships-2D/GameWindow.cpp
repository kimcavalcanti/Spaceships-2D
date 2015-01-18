#include "GameWindow.h"
#include "GameLogic.h"
#include "resource.h"
#include <gl\GL.h>

GameWindow::GameWindow()
{
}

GameWindow::~GameWindow()
{
}

bool GameWindow::RegisterWindow(const HINSTANCE hinst)
{
	WNDCLASSEX wnd;

	wnd.cbSize = sizeof(WNDCLASSEX);
	wnd.style = CS_HREDRAW | CS_VREDRAW;
	wnd.lpfnWndProc = GameLogic::WndProc;
	wnd.cbClsExtra = 0;
	wnd.cbWndExtra = 0;
	wnd.hInstance = hinst;
	wnd.hIcon = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON));
	wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnd.hbrBackground = NULL;
	wnd.lpszMenuName = NULL;
	wnd.lpszClassName = "GameWindow";
	wnd.hIconSm = LoadIcon(hinst, MAKEINTRESOURCE(IDI_ICON));

	if (!RegisterClassEx(&wnd))
		return false;

	InitOGL(hinst, 1024, 768);

	if (!m_hwnd)
		return false;

	ShowWindow(m_hwnd, TRUE);

	return true;
}

void GameWindow::Destroy()
{
	DestroyOGLContext();

	DestroyWindow(m_hwnd);

	m_hwnd = NULL;
	m_hdc = NULL;
}

HGLRC GameWindow::CreateOGLContext(const HDC hdc)
{
	unsigned int pixelformat;
	HGLRC hglrc;

	// What does this even do?
	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support Window
		PFD_SUPPORT_OPENGL |						// Format Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request RGBA Format
		32,											// Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits mask
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// Z-Buffer depth
		0,											// Stencil Buffer
		0,											// Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(pixelformat = ChoosePixelFormat(hdc, &pfd)))
	{
		return 0;
	}

	if (!SetPixelFormat(hdc, pixelformat, &pfd))
	{
		return 0;
	}

	if (!(hglrc = wglCreateContext(hdc)))
	{
		return 0;
	}

	if (!wglMakeCurrent(hdc, hglrc))
	{
		return 0;
	}

	return hglrc;
}

bool GameWindow::DestroyOGLContext()
{
	if (m_hglrc)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hglrc);
		m_hglrc = NULL;
	}

	if (!ReleaseDC(m_hwnd, m_hdc))
		return false;

	return true;
}

bool GameWindow::InitOGL(const HINSTANCE hInstance, const int width, const int height)
{
	m_hwnd = CreateWindowEx(NULL, "GameWindow", "Spaceships 2D!", 
		WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, width, height, NULL, NULL, hInstance, NULL);

	if (!m_hwnd)
		return false;

	m_hdc = GetDC(m_hwnd);

	if (!(m_hglrc = CreateOGLContext(m_hdc)))
		return false;

	m_width = width;
	m_height = height;

	return true;
}

void GameWindow::InitOGLState()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GameWindow::SetScreenSize(const int width, const int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-0.5*width, 0.5*width, -0.5*height, 0.5*height, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return;
}

void GameWindow::Render(const std::vector<GameObject*> &renderables) const
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	for (const GameObject *object : renderables)
	{
		object->Render();
	}

	glFlush();
	SwapBuffers(m_hdc);

	return;
}