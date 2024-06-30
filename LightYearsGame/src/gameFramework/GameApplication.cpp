#include "config.h"
#include "gameFramework/GameApplication.h"
#include "framework/AssetManager.h"
#include "levels/GameLevelOne.h"
#include "levels/MainMenuLevel.h"

ly::Application* GetApplication()
{
	return new ly::GameApplication();
}

namespace ly
{
	GameApplication::GameApplication()
		: Application(800, 900, "Light Years", sf::Style::Titlebar | sf::Style::Close)
	{
		AssetManager::Get().SetAssetRootDirectory(GetResourceDir());
		weak<MainMenuLevel> newWorld = LoadWorld<MainMenuLevel>();
	}
}
