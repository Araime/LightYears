#include "framework/BackgroundLayer.h"

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
		SetEnablePhysic(false);
	}
}