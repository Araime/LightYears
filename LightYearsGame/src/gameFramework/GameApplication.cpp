#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"
#include "spaceship/Spaceship.h"
#include "config.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication();
}

namespace ly
{
	GameApplication::GameApplication()
		: Application(600, 800, "Light Years", sf::Style::Titlebar | sf::Style::Close)
	{
		weak<World> newWorld = LoadWorld<World>();
		newWorld.lock()->SpawnActor<Actor>();
		testPlayerSpaceship = newWorld.lock()->SpawnActor<Spaceship>();
		testPlayerSpaceship.lock()->SetTexture(GetResourceDir() + "SpaceShooterRedux/PNG/playerShip1_blue.png");
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(300.f, 400.f));
		testPlayerSpaceship.lock()->SetVelocity(sf::Vector2f(0.f, -200.f));
		counter = 0;
	}

	void GameApplication::Tick(float deltaTime)
	{

	}
}
