#ifndef _DELTA_TIME_H_
#define _DELTA_TIME_H_

#include <Windows.h>

#define TO_SECONDS 10000000.f

class DeltaTime
{
public:
	DeltaTime();

	~DeltaTime();

	inline static void				Update()
	{
		m_deltaTime = UpdateDeltaTime();

		m_time = Now();
	}

	inline static float				Get()
	{
		return m_deltaTime;
	}

private:

	inline static FILETIME			Now()
	{
		SYSTEMTIME st;
		FILETIME ft;

		GetSystemTime(&st);
		SystemTimeToFileTime(&st, &ft);

		return ft;
	}

	inline static float				UpdateDeltaTime()
	{
		return (((Now().dwHighDateTime + Now().dwLowDateTime) / TO_SECONDS) - ((m_time.dwHighDateTime + m_time.dwLowDateTime) / TO_SECONDS));
	}

	static FILETIME		m_time;
	static float		m_deltaTime;
};

#endif