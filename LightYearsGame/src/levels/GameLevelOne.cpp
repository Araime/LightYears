#include "enemy/VanguardStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/HexagonStage.h"
#include "framework/Actor.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "gameplay/GameStage.h"
#include "gameplay/WaitStage.h"
#include "levels/GameLevelOne.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World(owningApp)
	{
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(400.f, 600.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);
	}

	void GameLevelOne::BeginPlay()
	{

	}

	void GameLevelOne::InitGameStages()
	{
		AddStage(shared<WaitStage>{new WaitStage{this}});
		AddStage(shared<VanguardStage>{new VanguardStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 3.f}});
		AddStage(shared<TwinBladeStage>{new TwinBladeStage{this}});

		AddStage(shared<WaitStage>{new WaitStage{this, 3.f}});
		AddStage(shared<HexagonStage>{new HexagonStage{this}});
	}
}