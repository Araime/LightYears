#include "framework/AssetManager.h"
#include "framework/BackgroundLayer.h"
#include "framework/MathUtility.h"
#include "framework//World.h"

namespace ly
{
	BackgroundLayer::BackgroundLayer(World* owningWorld,
		const List<std::string>& assetPaths,
		const sf::Vector2f& minVel,
		const sf::Vector2f& maxVel,
		float sizeMin,
		float sizeMax,
		int spriteCount,
		const sf::Color& colorTint)
		: Actor(owningWorld),
		mMinVelocity(minVel),
		mMaxVelocity(maxVel),
		mSizeMin(sizeMin),
		mSizeMax(sizeMax),
		mSpriteCount(spriteCount),
		mTintColor(colorTint)
	{
		SetAssets(assetPaths);
		SetEnablePhysic(false);
	}

	void BackgroundLayer::SetAssets(const List<std::string>& assetPaths)
	{
		for (const std::string& texturePath : assetPaths)
		{
			shared<sf::Texture> newTexture = AssetManager::Get().LoadTexture(texturePath);
			mTextures.push_back(newTexture);
		}
	}

	void BackgroundLayer::SetColorTint(const sf::Color& color)
	{
		mTintColor = color;
		for (sf::Sprite& sprite : mSprites)
		{
			sprite.setColor(color);
		}
	}

	void BackgroundLayer::SetSpriteCount(int newCount)
	{
		mSpriteCount = newCount;
		RefreshSprites();
	}

	void BackgroundLayer::RefreshSprites()
	{
		mSprites.clear();
		mVelocities.clear();

		for (int i = 0; i < mSpriteCount; ++i)
		{
			sf::Sprite newSprite{};
			RandomSpriteTexture(newSprite);
			RandomSpriteTransform(newSprite, true);
			mSprites.push_back(newSprite);

			float velX = RandomRange(mMinVelocity.x, mMaxVelocity.x);
			float velY = RandomRange(mMinVelocity.y, mMaxVelocity.y);
			mVelocities.push_back(sf::Vector2f(velX, velY));
		}

		SetColorTint(mTintColor);
	}

	void BackgroundLayer::RandomSpriteTexture(sf::Sprite& sprite)
	{
		if (mTextures.size() > 0)
		{
			shared<sf::Texture> pickedTexture = GetRandomTexture();
			sprite.setTexture(*(pickedTexture.get()));
			sprite.setTextureRect(sf::IntRect(0, 0, pickedTexture->getSize().x, pickedTexture->getSize().y));
			sf::FloatRect bound = sprite.getGlobalBounds();
			sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
		}
	}

	void BackgroundLayer::RandomSpriteTransform(sf::Sprite& sprite, bool randomY)
	{
		RandomSpritePosition(sprite, randomY);
		RandomSpriteRotation(sprite);
		RandomSpriteSize(sprite);
	}

	void BackgroundLayer::RandomSpritePosition(sf::Sprite& sprite, bool randomY)
	{
		auto windowSize = GetWorld()->GetWindowSize();
		auto bound = sprite.getGlobalBounds();

		float posX = RandomRange(0.f, windowSize.x);
		float posY = randomY ? RandomRange(0.f, windowSize.y) : -bound.height;

		sprite.setPosition(sf::Vector2f(posX, posY));
	}

	void BackgroundLayer::RandomSpriteRotation(sf::Sprite& sprite)
	{
		sprite.setRotation(RandomRange(0.f, 360.f));
	}

	void BackgroundLayer::RandomSpriteSize(sf::Sprite& sprite)
	{
		float size = RandomRange(mSizeMin, mSizeMax);
		sprite.setScale(size, size);
	}

	shared<sf::Texture> BackgroundLayer::GetRandomTexture() const
	{
		int randomPickIndex = static_cast<int>(RandomRange(0.f, mTextures.size()));

		return mTextures[randomPickIndex];
	}
}