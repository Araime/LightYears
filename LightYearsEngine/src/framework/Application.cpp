#include "framework/Core.h"
#include "framework/Application.h"
#include "framework/World.h"
#include "framework/AssetManager.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"

namespace ly
{
	Application::Application(unsigned int windowWidth, unsigned int windowHeight, const std::string& title, sf::Uint32 style)
		: mWindow(sf::VideoMode(windowWidth, windowHeight), title, style),
		mTargetFramerate(60.f),
		mTickClock(),
		mCurrentWorld(nullptr),
		mCleanCycleClock(),
		mCleanCycleInterval(2.f)
	{

	}

	void Application::Run()
	{
		mTickClock.restart();
		float accumulatedTime = 0.f;
		float targetDeltaTime = 1.f / mTargetFramerate;
		while (mWindow.isOpen())
		{
			sf::Event windowEvent;
			while (mWindow.pollEvent(windowEvent))
			{
				if (windowEvent.type == sf::Event::EventType::Closed)
				{
					QuitApplication();
				}
				else
				{
					DispatchEvent(windowEvent);
				}
			}
			float frameDeltaTime = mTickClock.restart().asSeconds();
			accumulatedTime += frameDeltaTime;
			while (accumulatedTime > targetDeltaTime)
			{
				accumulatedTime -= targetDeltaTime;
				TickInternal(targetDeltaTime);
				RenderInternal();
			}
		}
	}

	sf::Vector2u Application::GetWindowSize() const
	{
		return mWindow.getSize();
	}

	void Application::QuitApplication()
	{
		mWindow.close();
	}

	bool Application::DispatchEvent(const sf::Event& event)
	{
		if (mCurrentWorld)
		{
			return mCurrentWorld->DispatchEvent(event);
		}

		return false;
	}

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (mCurrentWorld)
		{
			mCurrentWorld->TickInternal(deltaTime);
		}

		TimerManager::Get().UpdateTimer(deltaTime);

		PhysicsSystem::Get().Step(deltaTime);	

		if (mCleanCycleClock.getElapsedTime().asSeconds() >= mCleanCycleInterval)
		{
			mCleanCycleClock.restart();
			AssetManager::Get().CleanCycle();
			if (mCurrentWorld)
			{
				mCurrentWorld->CleanCycle();
			}
		}

		if (mPendingWorld && mPendingWorld != mCurrentWorld)
		{
			mCurrentWorld = mPendingWorld;
			mPendingWorld->BeginPlayInternal();
		}
	}

	void Application::RenderInternal()
	{
		mWindow.clear();

		Render();

		mWindow.display();
	}

	void Application::Render()
	{
		if (mCurrentWorld)
		{
			mCurrentWorld->Render(mWindow);
		}
	}

	void Application::Tick(float deltaTime)
	{

	}
}