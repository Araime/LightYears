#include "gameplay/GameStage.h"
#include "framework/Core.h"

namespace ly
{
	GameStage::GameStage(World* world)
		: mWorld(world),
		mStageFinished(false)
	{

	}

	void GameStage::StartStage()
	{
		LOG("Stage Started");
	}

	void GameStage::TickStage(float deltaTime)
	{
		LOG("Stage Ticking");
	}

	void GameStage::FinishStage()
	{
		OnStageFinished.Broadcast();
		mStageFinished = true;
		StageFinished();
	}

	void GameStage::StageFinished()
	{
		LOG("Stage Finished");
	}
}