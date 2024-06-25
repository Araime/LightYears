#include "widgets/GameplayHUD.h"

namespace ly
{
	GameplayHUD::GameplayHUD()
		: mFrameRateText("Frame Rate:"),
		mPlayerHealthBar()
	{
		mFrameRateText.SetTextSize(22);
	}

	void GameplayHUD::Draw(sf::RenderWindow& windowRef)
	{
		mFrameRateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
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
		mPlayerHealthBar.UpdateValue(100.f, 200.f);
	}
}