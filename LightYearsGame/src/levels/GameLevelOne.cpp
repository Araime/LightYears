#include "framework/Actor.h"
#include "framework/TimerManager.h"
#include "framework/World.h"
#include "enemy/Vanguard.h"
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

		weak<Vanguard> testSpaceship1 = SpawnActor<Vanguard>();
		testSpaceship1.lock()->SetActorLocation(sf::Vector2f(300.f, 25.f));

		weak<Vanguard> testSpaceship2 = SpawnActor<Vanguard>();
		testSpaceship2.lock()->SetActorLocation(sf::Vector2f(400.f, 50.f));

		weak<Vanguard> testSpaceship3 = SpawnActor<Vanguard>();
		testSpaceship3.lock()->SetActorLocation(sf::Vector2f(500.f, 25.f));
	}

	void GameLevelOne::BeginPlay()
	{
		timerIndex_Test = TimerManager::Get().SetTimer(GetWeakRef(), &GameLevelOne::TimerCallback_Test, 2, true);
	}

	void GameLevelOne::TimerCallback_Test()
	{
		LOG("Callback called!");
		TimerManager::Get().ClearTimer(timerIndex_Test);
	}
}