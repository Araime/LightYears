#include "enemy/Vanguard.h"
#include "enemy/UFO.h"
#include "enemy/VanguardStage.h"
#include "framework/World.h"

namespace ly
{
	VanguardStage::VanguardStage(World* world)
		: GameStage(world),
		mSpawnInterval(2.f),
		mSwitchInterval(4.f),
		mSpawnDistanceToEdge(100.f),
		mLeftSpawnLoc(0.f, 0.f),
		mRightSpawnLoc(0.f, 0.f),
		mSpawnLoc(0.f, 0.f),
		mRowsToSpawn(2),
		mRowSpawnCount(0),
		mVanguardsPerRow(5),
		mCurrentRowVanguardCount(0)
	{

	}

	void VanguardStage::StartStage()
	{
		auto windowSize = GetWorld()->GetWindowSize();
		mLeftSpawnLoc = sf::Vector2f(mSpawnDistanceToEdge, -100.f);
		mRightSpawnLoc = sf::Vector2f(windowSize.x - mSpawnDistanceToEdge, -100.f);

		SwitchRow();
	}

	void VanguardStage::StageFinished()
	{
		TimerManager::Get().ClearTimer(mSpawnTimerHandle);
		TimerManager::Get().ClearTimer(mSwitchimerHandle);
	}

	void VanguardStage::SpawnVanguard()
	{
		//weak<Vanguard> newVanguard = GetWorld()->SpawnActor<Vanguard>();
		weak<UFO> newVanguard = GetWorld()->SpawnActor<UFO>();
		newVanguard.lock()->SetActorLocation(mSpawnLoc);
		++mCurrentRowVanguardCount;
		if (mCurrentRowVanguardCount == mVanguardsPerRow)
		{
			TimerManager::Get().ClearTimer(mSpawnTimerHandle);
			mSwitchimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SwitchRow, mSwitchInterval, false);
			mCurrentRowVanguardCount = 0;
		}
	}

	void VanguardStage::SwitchRow()
	{
		if (mRowSpawnCount == mRowsToSpawn)
		{
			FinishStage();
			return;
		}

		if (mSpawnLoc == mLeftSpawnLoc)
		{
			mSpawnLoc = mRightSpawnLoc;
		}
		else
		{
			mSpawnLoc = mLeftSpawnLoc;
		}

		mSpawnTimerHandle = TimerManager::Get().SetTimer(GetWeakRef(), &VanguardStage::SpawnVanguard, mSpawnInterval, true);

		++mRowSpawnCount;
	}
}