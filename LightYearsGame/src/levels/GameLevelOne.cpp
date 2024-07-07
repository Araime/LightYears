#include "enemy/BossStage.h"
#include "enemy/ChaosStage.h"
#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/UFOStage.h"
#include "enemy/VanguardStage.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "levels/GameLevelOne.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World(owningApp)
	{

	}

	void GameLevelOne::AllGameStageFinished()
	{
		mGameplayHUD.lock()->GameFinished(true);
	}

	void GameLevelOne::BeginPlay()
	{
		Player& newPlayer = PlayerManager::Get().CreateNewPlayer();
		mPlayerSpaceship = newPlayer.SpawnSpaceship(this);
		mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		mGameplayHUD = SpawnHUD<GameplayHUD>();
		mGameplayHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::QuitGame);
		mGameplayHUD.lock()->onRestartButtonClicked.BindAction(GetWeakRef(), &GameLevelOne::Restart);
	}

	void GameLevelOne::PlayerSpaceshipDestroyed(Actor* destroyedPlayerSpaceship)
	{
		mPlayerSpaceship = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
		if (!mPlayerSpaceship.expired())
		{
			mPlayerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameLevelOne::PlayerSpaceshipDestroyed);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<VanguardStage>{new VanguardStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 2.f }});
		AddStage(shared<BossStage>{new BossStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 1.f }});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 1.f }});
		AddStage(shared<HexagonStage>{new HexagonStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 2.f }});
		AddStage(shared<UFOStage>{new UFOStage{ this }});

		AddStage(shared<WaitStage>{new WaitStage{ this, 2.f }});
		AddStage(shared<ChaosStage>{new ChaosStage{ this }});
	}

	void GameLevelOne::QuitGame()
	{
		GetApplication()->QuitApplication();
	}

	void GameLevelOne::Restart()
	{
		PlayerManager::Get().Reset();
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void GameLevelOne::GameOver()
	{
		mGameplayHUD.lock()->GameFinished(false);
	}
}