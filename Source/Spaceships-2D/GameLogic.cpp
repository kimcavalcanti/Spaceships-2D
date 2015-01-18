#include "GameLogic.h"
#include "Enemy.h"
#include <windowsx.h>
#include <fstream>
#include <iostream>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define PAUSE 0x50
#define MAX_ENEMY 50

GameLogic::~GameLogic()
{
}

// Initialise the game logic class
void GameLogic::Initialise(const HINSTANCE hinst)
{
	GameLogic::GetInstance().m_hinst = hinst;
	GameLogic::GetInstance().AddNewGameObject(new Player());

	GameLogic::GetInstance().m_random = std::uniform_int_distribution<int>(0, 4);
	GameLogic::GetInstance().m_maxEnemy = 5;
}

// Destory all game objects and the game window
void GameLogic::Destroy()
{
	// Clean up game object pointers
	for (GameObject *object : m_renderables)
	{
		delete object;
	}

	GameWindow::GetInstance().Destroy();
}

// Remove a game object from the game
void GameLogic::DestroyGameObject(const GameObject *gameObject)
{
	for (unsigned index = 0; index < m_renderables.size(); index++)
	{
		if (m_renderables[index] == gameObject)
		{
			delete m_renderables[index];
			m_renderables.erase(m_renderables.begin() + index);

			break;
		}
	}
}

// Add a game object to the game
void GameLogic::AddNewGameObject(GameObject *gameObject)
{
	gameObject->SetScreenSize(m_screenWidth, m_screenHeight);

	m_renderables.push_back(gameObject);
}

// Set the screen width and height
void GameLogic::SetScreenSize(const int width, const int height)
{
	m_screenWidth = width;
	m_screenHeight = height;

	for (GameObject *gameObject : m_renderables)
	{
		gameObject->SetScreenSize(width, height);
	}

	m_randomX = std::uniform_real_distribution<float>(-m_screenWidth / 2.f, m_screenWidth / 2.f);
	m_randomY = std::uniform_real_distribution<float>(-m_screenHeight / 2.f, m_screenHeight / 2.f);
}

// Ensures there are always enemies in game
void GameLogic::EnemyController()
{
	if (m_enemyCount < m_maxEnemy && m_enemySpawnTimer > 0.1f)
	{
		int direction = m_random(m_randomGenerator);

		if (direction == UP || direction == DOWN)
		{
			SpawnEnemy(100.f, m_randomX(m_randomGenerator), direction == UP ? (-m_screenHeight / 2.f) : (m_screenHeight / 2.f), direction == UP ? Vector4::MovementUp() : Vector4::MovementDown());
		}
		else if (direction == LEFT || direction == RIGHT)
		{
			SpawnEnemy(100.f, direction == LEFT ? (-m_screenWidth / 2.f) : (m_screenWidth / 2.f), m_randomY(m_randomGenerator), direction == LEFT ? Vector4::MovementRight() : Vector4::MovementLeft());
		}
	}

	for (unsigned index = 1; index < m_renderables.size(); index++)
	{
		if (m_renderables[index]->CanDestroy() && m_renderables[index]->Type() == "Enemy")
		{
			DestroyGameObject(m_renderables[index]);
			m_enemyCount--;
		}
	}

	// Increase maximum enemy count by one every 5 seconds
	if (m_enemyIncreaseTimer > 5.f && m_maxEnemy <= MAX_ENEMY)
	{
		m_maxEnemy++;

		// Reset timer
		m_enemyIncreaseTimer = 0;
	}
}

// Spawn an enemy at a given location, with a direction and speed
void GameLogic::SpawnEnemy(const float speed, const float originX, const float originY, const Vector4 direction)
{
	Enemy *enemy = new Enemy(speed, originX, originY);
	enemy->SetDirection(direction);

	// Calculate the enemy destroy time = distance / speed
	if (direction == Vector4::MovementUp() || direction == Vector4::MovementDown())
	{
		enemy->SetDuration(m_screenHeight / speed);
	}
	else if (direction == Vector4::MovementLeft() || direction == Vector4::MovementRight())
	{
		enemy->SetDuration(m_screenWidth / speed);
	}

	AddNewGameObject(enemy);
	m_enemyCount++;

	// Reset timer
	m_enemySpawnTimer = 0;
}

// Run the game loop
void GameLogic::Run()
{
	MSG msg;
	std::fstream file;

	if (!GameWindow::GetInstance().RegisterWindow(m_hinst))
		return;

	file.open("DeltaTimer.txt", std::fstream::out);
	while (!m_exit)
	{


		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				m_exit = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else if (!m_paused)
		{
			// Manage enemies
			EnemyController();

			// Update all game objects
			for (GameObject *gameObject : m_renderables)
			{
				gameObject->Update();
			}

			// Cleanup if required
			for (GameObject *gameObject : m_renderables)
			{
				gameObject->Cleanup();
			}

			// Render game objects to screen
			GameWindow::GetInstance().Render(m_renderables);

			Time::Update();

			m_enemySpawnTimer += Time::DeltaTime();
			m_enemyIncreaseTimer += Time::DeltaTime();
		}
		else
		{
			// Update time if game is paused
			Time::Update();
		}

		// End game if player is touched
		if (m_renderables[0]->CanDestroy())
		{
			PostQuitMessage(0);
		}

		file << Time::DeltaTime() << std::endl;
	}
	file.close();
}

LRESULT GameLogic::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		GameWindow::GetInstance().SetScreenSize(LOWORD(lparam), HIWORD(lparam));
		GameLogic::GetInstance().SetScreenSize(LOWORD(lparam), HIWORD(lparam));

		break;
	case WM_MOVE:
		// Update the timer when the window is moved
		Time::Update();
		break;
	case WM_KEYDOWN:
		if ((unsigned short)GetKeyState(PAUSE) >> 15)
		{
			GameLogic::GetInstance().m_paused = !GameLogic::GetInstance().m_paused;
		}
		break;
	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return 0;
}