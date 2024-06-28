#include "framework/Actor.h"
#include "player/Player.h"
#include "player/PlayerManager.h"
#include "player/PlayerSpaceship.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: mFrameRateText("Frame Rate:"),
		mPlayerHealthBar(),
		mPlayerLifeIcon("SpaceShooterRedux/PNG/Power-ups/life.png"),
		mHealthyHealthBarColor(128, 255, 128, 255),
		mCriticalHealthBarColor(255, 0, 0, 255),
		mCriticalThreshold(0.3),
		mWidgetSpacing(10.f)
	{
		mFrameRateText.SetTextSize(22);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFrameRateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
	}

	void GameplayHUD::Tick(float deltaTime)
	{
		int frameRate = static_cast<int>(1 / deltaTime);
		std::string frameRateStr = "Frame Rate: " + std::to_string(frameRate);
		mFrameRateText.SetString(frameRateStr);
	}

	void GameplayHUD::Init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mPlayerHealthBar.SetWidgetLocation(sf::Vector2f(20.f, windowSize.y - 50.f));

		sf::Vector2f lifeIconPos = mPlayerHealthBar.GetWidgetLocation();
		lifeIconPos += sf::Vector2f(mPlayerHealthBar.GetBound().width + mWidgetSpacing, 0.f);
		mPlayerLifeIcon.SetWidgetLocation(lifeIconPos);

		RefreshHealthBar();
	}

	void GameplayHUD::PlayerHealthUpdated(float amt, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.UpdateValue(currentHealth, maxHealth);
		if (currentHealth / maxHealth <= mCriticalThreshold)
		{
			mPlayerHealthBar.SetForegroundColor(mCriticalHealthBarColor);
		}
		else
		{
			mPlayerHealthBar.SetForegroundColor(mHealthyHealthBarColor);
		}
	}

	void GameplayHUD::RefreshHealthBar()
	{
		Player* player = PlayerManager::Get().GetPlayer();
		if (player && !player->GetCurrentSpaceship().expired())
		{
			weak<PlayerSpaceship> playerSpaceship = player->GetCurrentSpaceship();
			playerSpaceship.lock()->onActorDestroyed.BindAction(GetWeakRef(), &GameplayHUD::PlayerSpaceshipDestroyed);
			HealthComponent& healthComp = player->GetCurrentSpaceship().lock()->GetHealthComp();
			healthComp.onHealthChanged.BindAction(GetWeakRef(), &GameplayHUD::PlayerHealthUpdated);
			mPlayerHealthBar.UpdateValue(healthComp.GetHealth(), healthComp.GetMaxHealth());
		}
	}

	void GameplayHUD::PlayerSpaceshipDestroyed(Actor* actor)
	{
		RefreshHealthBar();
	}
}