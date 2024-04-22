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

	bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
	{
		return lhs.GetTimerKey() == rhs.GetTimerKey();
	}

	void TimerManager::ClearTimer(TimerHandle timerHandle)
	{
		auto iter = mTtimers.find(timerHandle);
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

	unsigned int TimerHandle::timerCounterKey = 0;

	TimerHandle::TimerHandle()
		: mTimerKey(GetNextTimerKey())
	{

	}
}