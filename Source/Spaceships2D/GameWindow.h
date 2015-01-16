#ifndef _GAME_WINDOW_H_
#define _GAME_WINDOW_H_

#include "Player.h"
#include <vector>
#include <Windows.h>
#include <memory>

// Singleton class which will setup the game window and run the game logic
class GameWindow
{
public:
	virtual	~GameWindow();

	bool										RegisterWindow(const HINSTANCE hinst);
	void										SetScreenSize(const int width, const int height);
	void										Render(const std::vector<GameObject*> &renderables) const;
	void										Destroy();

	inline static GameWindow&					GetInstance()
	{
		static GameWindow instance;

		return instance;
	}

private:
	GameWindow();

	HGLRC										CreateOGLContext(const HDC hdc);
	bool										DestroyOGLContext();
	bool										InitOGL(const HINSTANCE hInstance, const int width, const int height);
	void										InitOGLState();

	HWND										m_hwnd;
	HDC											m_hdc;
	HGLRC										m_hglrc;
	int											m_width;
	int											m_height;
	bool										m_exit;
};

#endif