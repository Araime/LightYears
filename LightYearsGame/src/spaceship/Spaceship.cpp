#include "spaceship/Spaceship.h"

namespace ly
{
	Spaceship::Spaceship(World* owningWorld, const std::string& texturePath)
		: Actor(owningWorld, texturePath),
		mVelocity(),
		mHealthComp(100.f, 100.f)
	{

	}

	void Spaceship::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		AddActorLocationOffset(GetVelocity() * deltaTime);
	}

	void Spaceship::SetVelocity(const sf::Vector2f& newVel)
	{
		mVelocity = newVel;
	}

	void Spaceship::Shoot()
	{

	}

	void Spaceship::BeginPlay()
	{
		Actor::BeginPlay();
		SetEnablePhysic(true);
		mHealthComp.onHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);

		mHealthComp.onHealthChanged.Broadcast(11.f, 88.f, 100.f);
	}

	void Spaceship::OnHealthChanged(float amt, float health, float maxHealth)
	{
		LOG("Health changed to: %f, and now is %f/%f", amt, health, maxHealth);
	}
}