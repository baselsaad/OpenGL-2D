#include "Timer.h"
#include <iostream>

#define MAX_SIZE 2

Timer::Timer()
	: m_IsTimerStarted(false)
{
	CallbacksVec.reserve(MAX_SIZE);
}

void Timer::StartTimer() const
{
	m_Start = std::chrono::high_resolution_clock::now();
	m_IsTimerStarted = true;
}

void Timer::StopTimer() const
{
	m_End = std::chrono::high_resolution_clock::now();

	if (m_IsTimerStarted)
	{
		m_Duration = m_End - m_Start;
		m_ElapsedTime = m_Duration.count();
		m_IsTimerStarted = false;
	}
	else
	{
		m_ElapsedTime = 0.0f;
	}
}

int Timer::SetCallBackTimer(float rate, Lambda& callback)
{
	if (CallbacksVec.size() >= MAX_SIZE)
	{
		return -1;
	}


	int id = CallbacksVec.size();
	CallbacksVec.emplace_back(rate, callback);

	return id;
}

void Timer::ClearCallBackTimer(int id)
{
	CallbacksVec.erase(CallbacksVec.begin() + id);
}
