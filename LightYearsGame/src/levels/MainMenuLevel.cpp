#include "framework/Application.h"
#include "framework/BackdropActor.h"
#include "levels/MainMenuLevel.h"
#include "levels/GameLevelOne.h"
#include "widgets/MainMenuHUD.h"

namespace ly
{
	MainMenuLevel::MainMenuLevel(Application* owningApp)
		: World(owningApp)
	{
		mMainMenuHUD = SpawnHUD<MainMenuHUD>();
	}

	void MainMenuLevel::BeginPlay()
	{
		mMainMenuHUD.lock()->onStartButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::StartGame);
		mMainMenuHUD.lock()->onQuitButtonClicked.BindAction(GetWeakRef(), &MainMenuLevel::QuitGame);
		SpawnActor<BackdropActor>("SpaceShooterRedux/Backgrounds/mainMenu.png", sf::Vector2f(30.f, 0.f));
	}

	void MainMenuLevel::StartGame()
	{
		GetApplication()->LoadWorld<GameLevelOne>();
	}

	void MainMenuLevel::QuitGame()
	{
		GetApplication()->QuitApplication();
	}
}