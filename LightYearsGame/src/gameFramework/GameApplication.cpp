#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "framework/AssetManager.h"
#include "player/PlayerSpaceship.h"
#include "config.h"
#include "enemy/Vanguard.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication();
}

namespace ly
{
	GameApplication::GameApplication()
		: Application(1000, 750, "Light Years", sf::Style::Titlebar | sf::Style::Close)
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<World> newWorld = LoadWorld<World>();
		testPlayerSpaceship = newWorld.lock()->SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(500.f, 600.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testSpaceship1 = newWorld.lock()->SpawnActor<Vanguard>();
		testSpaceship1.lock()->SetActorLocation(sf::Vector2f(400.f, 25.f));
		counter = 0.f;
		weak<Vanguard> testSpaceship2 = newWorld.lock()->SpawnActor<Vanguard>();
		testSpaceship2.lock()->SetActorLocation(sf::Vector2f(500.f, 50.f));
		counter = 0.f;
		weak<Vanguard> testSpaceship3 = newWorld.lock()->SpawnActor<Vanguard>();
		testSpaceship3.lock()->SetActorLocation(sf::Vector2f(600.f, 25.f));
		counter = 0.f;
	}

	void GameApplication::Tick(float deltaTime)
	{
		counter += deltaTime;
		/*if (counter > 10.f)
		{
			if (!testPlayerSpaceship.expired())
			{
				testPlayerSpaceship.lock()->Destroy();
			}
		}*/


	}
}
