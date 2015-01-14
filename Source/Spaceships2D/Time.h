#pragma once
#include <ctime>

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
		return (((ft.dwHighDateTime + ft.dwLowDateTime) / 10000000.f) > (((m_time.dwHighDateTime + m_time.dwLowDateTime) / 10000000.f) + difference));
	}

	inline static FILETIME		Now()
	{
		SYSTEMTIME st;
		FILETIME ft;

		GetSystemTime(&st);
		SystemTimeToFileTime(&st, &ft);

		return ft;
	}

	inline FILETIME				Get() const
	{
		return m_time;
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
		return (((ft.dwHighDateTime + ft.dwLowDateTime) / 10000000.f) - ((m_time.dwHighDateTime + m_time.dwLowDateTime) / 10000000.f));
	}

private:
	FILETIME						m_time;
};