#include "framework/Core.h"
#include "framework/Application.h"
#include "framework/World.h"

namespace ly
{
	Application::Application()
		: mWindow(sf::VideoMode(600, 800), "Light Years"),
		mTargetFramerate(60.f),
		mTickClock(),
		currentWorld(nullptr)
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
					mWindow.close();
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

	void Application::TickInternal(float deltaTime)
	{
		Tick(deltaTime);

		if (currentWorld)
		{
			currentWorld->TickInternal(deltaTime);
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
		sf::RectangleShape rect(sf::Vector2f(100, 100));
		rect.setFillColor(sf::Color::Red);
		rect.setOrigin(50, 50);
		rect.setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);

		mWindow.draw(rect);
	}

	void Application::Tick(float deltaTime)
	{

	}
}