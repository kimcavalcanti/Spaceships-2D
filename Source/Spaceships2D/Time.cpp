#include "Time.h"

FILETIME Time::m_time;
float Time::m_deltaTime = 0;

Time::Time()
{
	Update();
}


Time::~Time()
{
}
