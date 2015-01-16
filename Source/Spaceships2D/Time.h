#ifndef _TIME_H_
#define _TIME_H_

#include "DeltaTime.h"

#define TO_SECONDS 10000000.f

class Time
{
public:
	Time()
	{
		Update();
	}
	
	~Time() {}

	inline bool					CompareTime(FILETIME ft, float difference) const
	{
		return (((ft.dwHighDateTime + ft.dwLowDateTime) / TO_SECONDS) > (((m_time.dwHighDateTime + m_time.dwLowDateTime) / TO_SECONDS) + difference));
	}

	inline void					Update()
	{
		SYSTEMTIME st;

		GetSystemTime(&st);
		SystemTimeToFileTime(&st, &m_time);
	}

	// Difference in seconds ##.####
	inline float				Difference(FILETIME ft) const
	{
		return (((ft.dwHighDateTime + ft.dwLowDateTime) / TO_SECONDS) - ((m_time.dwHighDateTime + m_time.dwLowDateTime) / TO_SECONDS));
	}

	inline static DeltaTime			Delta()
	{
		static DeltaTime deltaTime;

		return deltaTime;
	}

	inline static FILETIME			Now()
	{
		SYSTEMTIME st;
		FILETIME ft;

		GetSystemTime(&st);
		SystemTimeToFileTime(&st, &ft);

		return ft;
	}

private:
	FILETIME						m_time;
};

#endif