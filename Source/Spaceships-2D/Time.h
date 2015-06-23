#ifndef _TIME_H_
#define _TIME_H_

#include <Windows.h>

class Time
{
private:
	static __int64				m_currentTime;
	static __int64				m_previousTime;

	static double				m_secondsPerCount;
	static double				m_deltaTime;

	static bool					m_paused;

public:
	Time();
	virtual ~Time();

	static void				Update();
	void					Stop() { m_paused = true; }
	void					Start() { m_paused = false; }

	static inline float		DeltaTime() { return static_cast<float>(m_deltaTime); }
};

#endif