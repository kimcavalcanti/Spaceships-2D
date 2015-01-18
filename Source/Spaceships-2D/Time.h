#ifndef _TIME_H_
#define _TIME_H_

#include <Windows.h>

#define TO_SECONDS 10000000.f

class Time
{
public:
	Time();

	~Time();

	// Calculate time between frames
	inline static void				Update()
	{
		float temp = UpdateDeltaTime();

		// Sometimes UpdateDeltaTime() returns a negative - ignore it if it does so
		if (temp > 0)
			m_deltaTime = temp;

		m_time = Now();
	}

	inline static float				DeltaTime()
	{
		return m_deltaTime;
	}

private:

	inline static FILETIME&			Now()
	{
		static FILETIME ft;
		SYSTEMTIME st;

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