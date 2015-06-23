#include "Time.h"

__int64 Time::m_currentTime{};
__int64 Time::m_previousTime{};

double Time::m_secondsPerCount{};
double Time::m_deltaTime{};

bool Time::m_paused{};

Time::Time()
{
}

Time::~Time()
{
}

void Time::Update()
{
	__int64 countsPerSecond{ 0 };
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSecond);
	m_secondsPerCount = 1.0 / static_cast<double>(countsPerSecond);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_currentTime);

	m_deltaTime = (m_currentTime - m_previousTime) * m_secondsPerCount;

	if (m_deltaTime < 0.0)
	{
		m_deltaTime = 0.0;
	}

	m_previousTime = m_currentTime;
}