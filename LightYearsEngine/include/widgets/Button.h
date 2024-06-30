#pragma once

#include "framework/Delegate.h"
#include "widgets/Widget.h"

namespace ly
{
	class Button : public Widget
	{
	public:
		Button(const std::string& textString = "Button", const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");
		virtual sf::FloatRect GetBound() const;
		void SetTextString(const std::string& newStr);
		void SetTextSize(unsigned int characterSize);
		virtual bool HandleEvent(const sf::Event& windowEvent) override;
		bool CheckIfCursorInside(const int& x_cor, const int& y_cor);
		Delegate<> onButtonClicked;

	private:
		virtual void Draw(sf::RenderWindow& windowRef) override;
		virtual void LocationUpdated(const sf::Vector2f& location);
		virtual void RotationUpdated(float rotation);
		void CenterText();
		shared<sf::Texture> mButtonTexture;
		sf::Sprite mButtonSprite;

		shared<sf::Font> mButtonFont;
		sf::Text mButtonText;

		sf::Color mButtonDefaultColor;
		sf::Color mButtonDownColor;
		sf::Color mButtonHoverColor;

		bool mIsButtonDown;

		void ButtonUp();
		void ButtonDown();
		void MouseHovered();
	};
}