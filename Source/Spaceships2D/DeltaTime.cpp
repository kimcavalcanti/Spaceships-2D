#include "DeltaTime.h"

FILETIME DeltaTime::m_time;
float DeltaTime::m_deltaTime = 0;

DeltaTime::DeltaTime()
{
	Update();
}


DeltaTime::~DeltaTime()
{
}
