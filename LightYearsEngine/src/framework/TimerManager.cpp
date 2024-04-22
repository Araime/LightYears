#include "framework/TimerManager.h"

namespace ly
{
	Timer::Timer(weak<Object> weakRef, std::function<void()> callback, float duration, bool repeat)
		: mListener(weakRef, callback),
		mDuration(duration),
		mRepeat(repeat),
		mTimeCounter(0.f),
		mIsExpired(false)
	{

	}

	void Timer::TickTime(float deltaTime)
	{
		if (Expired())
		{
			return;
		}

		mTimeCounter += deltaTime;
		if (mTimeCounter >= mDuration)
		{
			mListener.second();

			if (mRepeat)
			{
				mTimeCounter = 0.f;
			}
			else
			{
				SetExpired();
			}
		}
	}

	bool Timer::Expired() const
	{
		return mIsExpired || mListener.first.expired() || mListener.first.lock()->IsPendingDestroy();
	}

	void Timer::SetExpired()
	{
		mIsExpired = true;
	}

	unsigned int TimerManager::timerIndexCounter = 0;

	unique<TimerManager> TimerManager::timerManager(nullptr);

	void TimerManager::UpdateTimer(float deltaTime)
	{
		for (auto iter = mTtimers.begin(); iter != mTtimers.end();)
		{
			if (iter->second.Expired())
			{
				iter = mTtimers.erase(iter);
			}
			else
			{
				iter->second.TickTime(deltaTime);
				++iter;
			}
		}
	}

	void TimerManager::ClearTimer(unsigned int timerIndex)
	{
		auto iter = mTtimers.find(timerIndex);
		if (iter != mTtimers.end())
		{
			iter->second.SetExpired();
		}
	}

	TimerManager::TimerManager() : mTtimers()
	{

	}

	TimerManager& TimerManager::Get()
	{
		if (!timerManager)
		{
			timerManager = std::move(unique<TimerManager>(new TimerManager()));
		}

		return *timerManager;
	}
}