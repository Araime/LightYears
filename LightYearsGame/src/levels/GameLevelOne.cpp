#include "levels/GameLevelOne.h"
#include "framework/Actor.h"
#include "player/PlayerSpaceship.h"
#include "framework/World.h"
#include "enemy/Vanguard.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		: World(owningApp)
	{
		testPlayerSpaceship = SpawnActor<PlayerSpaceship>();
		testPlayerSpaceship.lock()->SetActorLocation(sf::Vector2f(500.f, 600.f));
		testPlayerSpaceship.lock()->SetActorRotation(-90.f);

		weak<Vanguard> testSpaceship1 = SpawnActor<Vanguard>();
		testSpaceship1.lock()->SetActorLocation(sf::Vector2f(400.f, 25.f));

		weak<Vanguard> testSpaceship2 = SpawnActor<Vanguard>();
		testSpaceship2.lock()->SetActorLocation(sf::Vector2f(500.f, 50.f));

		weak<Vanguard> testSpaceship3 = SpawnActor<Vanguard>();
		testSpaceship3.lock()->SetActorLocation(sf::Vector2f(600.f, 25.f));
	}
}