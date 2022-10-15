#pragma once
#include <chrono>
#include <functional>
#include "Renderer.h"


class Timer
{

public:
	using Lambda = std::function<void()>;
	Timer();

	struct CallbackTimersContainer
	{
		float Rate;
		Lambda CallBack;

		std::chrono::time_point<std::chrono::steady_clock> StartTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> LastFrameTime;

		CallbackTimersContainer(const float& rate, const Lambda& lambdaCallback)
			: Rate(rate)
			, CallBack(lambdaCallback)
		{
		}

		void Update()
		{
			LastFrameTime = std::chrono::high_resolution_clock::now() - StartTime;
			float currentRate = LastFrameTime.count();

			if (currentRate >= Rate)
			{
				CallBack();
				StartTime = std::chrono::high_resolution_clock::now();
			}
		}

	};

	void StartTimer() const;
	void StopTimer() const;

	inline float ElapsedTimeInMili() const { return m_ElapsedTime; }
	inline float ElapsedTimeInSecound() const { return m_ElapsedTime / 1000.0f; }
	inline double GetTime() { return glfwGetTime(); }

	int SetCallBackTimer(float rate, Lambda& callback);
	void ClearCallBackTimer(int id);

public:
	std::vector<CallbackTimersContainer> CallbacksVec;

private:
	static const int INVALID = -1;
	mutable float m_ElapsedTime;
	mutable bool m_IsTimerStarted;
	mutable std::chrono::time_point<std::chrono::steady_clock> m_Start;
	mutable std::chrono::time_point<std::chrono::steady_clock> m_End;
	mutable std::chrono::duration<float> m_Duration;
};

