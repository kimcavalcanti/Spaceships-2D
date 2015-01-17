#ifndef _GAME_LOGIC_H_
#define _GAME_LOGIC_H_

#include "GameWindow.h"
#include <memory>
#include <random>

// Singleton class which runs the game logic
class GameLogic
{
public:
	virtual	~GameLogic();

	static LRESULT CALLBACK						WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static void									Initialise(const HINSTANCE hinst);
	void										Destroy();
	void										Run();

	inline static GameLogic&					GetInstance()
	{
		static GameLogic instance;

		return instance;
	}

	inline const std::vector<GameObject*>		GetGameObjectList() const
	{
		return m_renderables;
	}

private:
	GameLogic() { ; }

	void										DestroyGameObject(const GameObject *gameObject);
	void										AddNewGameObject(GameObject *gameObject);
	void										SetScreenSize(const int width, const int height);
	void										EnemyController();
	void										SpawnEnemy(const float speed, const float originX, const float originY, const Vector4 direction);

	std::default_random_engine					m_randomGenerator;

	std::uniform_int_distribution<int>			m_random;
	std::uniform_real_distribution<float>		m_randomY;
	std::uniform_real_distribution<float>		m_randomX;

	HINSTANCE									m_hinst;
	bool										m_exit;

	unsigned short								m_screenWidth;
	unsigned short								m_screenHeight;
	unsigned short								m_enemyCount;
	unsigned short								m_maxEnemy;

	// Timer for enemies spawning
	float										m_enemySpawnTimer;
	// Timer for max enemy increasing
	float										m_enemyIncreaseTimer;

	bool										m_paused;

	std::vector<GameObject*>					m_renderables;
};

#endif