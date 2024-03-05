#include "framework/World.h"
#include "framework/Core.h"

namespace ly
{
	World::World(Application* owningApp)
		: mOwningApp(owningApp),
		mBeganPlay(false)
	{

	}

	void World::BeginPlayInternal()
	{
		if (!mBeganPlay)
		{
			mBeganPlay = true;
			BeginPlay();
		}
	}

	void World::TickInternal(float deltaTime)
	{
		Tick(deltaTime);
	}

	World::~World()
	{

	}

	void World::BeginPlay()
	{
		LOG("Began play");
	}

	void World::Tick(float deltaTime)
	{
		LOG("Tick at framerate: %f", 1.f / deltaTime);
	}
}