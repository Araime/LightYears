#include <box2d/b2_body.h>
#include "framework/Actor.h"
#include "framework/Core.h"
#include "framework/AssetManager.h"
#include "framework/MathUtility.h"
#include "framework/World.h"
#include "framework/PhysicsSystem.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		: mOwningWorld(owningWorld),
		mHasBeganPlay(false),
		mSprite(),
		mTexture(),
		mPhysicBody(nullptr),
		mPhysicsEnabled(false)
	{
		SetTexture(texturePath);
	}

	Actor::~Actor()
	{
		LOG("Actor destroyed");
	}

	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}

	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}

	void Actor::BeginPlay()
	{

	}

	void Actor::Tick(float deltaTime)
	{
		
	}

	void Actor::SetTexture(const std::string& texturePath)
	{
		AssetManager& assetManager = AssetManager::Get();

		mTexture = assetManager.LoadTexture(texturePath);
		if (!mTexture) return;

		mSprite.setTexture(*mTexture);

		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect(sf::Vector2i(), sf::Vector2i(textureWidth, textureHeight)));
		CenterPivot();
	}

	void Actor::Render(sf::RenderWindow& window)
	{
		if (IsPendingDestroy()) return;

		window.draw(mSprite);
	}

	void Actor::SetActorLocation(const sf::Vector2f& newLoc)
	{
		mSprite.setPosition(newLoc);
	}

	void Actor::SetActorLRotation(float newRot)
	{
		mSprite.setRotation(newRot);
	}

	void Actor::AddActorLocationOffset(const sf::Vector2f offsetAmt)
	{
		SetActorLocation(GetActorLocation() + offsetAmt);
	}

	void Actor::AddActorLRotationOffset(float offsetAmt)
	{
		SetActorLRotation(GetActorRotation() + offsetAmt);
	}

	sf::Vector2f Actor::GetActorLocation() const
	{
		return mSprite.getPosition();
	}

	float Actor::GetActorRotation() const
	{
		return mSprite.getRotation();
	}

	sf::Vector2f Actor::GetActorForwardDirection() const
	{
		return RotationToVector(GetActorRotation());
	}

	sf::Vector2f Actor::GetActorRightDirection() const
	{
		return RotationToVector(GetActorRotation() + 90.f);
	}

	sf::FloatRect Actor::GetActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}

	sf::Vector2u Actor::GetWindowSize() const
	{
		return mOwningWorld->GetWindowSize();
	}

	bool Actor::IsActorOutOfWindowBounds() const
	{
		float windowWidth = GetWorld()->GetWindowSize().x;
		float windowHeight = GetWorld()->GetWindowSize().y;

		float width = GetActorGlobalBounds().width;
		float height = GetActorGlobalBounds().height;

		sf::Vector2f actorPos = GetActorLocation();

		if (actorPos.x < -width)
		{
			return true;
		}

		if (actorPos.x > windowWidth + width)
		{
			return true;
		}

		if (actorPos.y < -height)
		{
			return true;
		}

		if (actorPos.y > windowHeight + height)
		{
			return true;
		}

		return false;
	}

	void Actor::SetEnablePhysic(bool enable)
	{
		mPhysicsEnabled = true;
		if (mPhysicsEnabled)
		{
			InitializePhysics();
		}
		else
		{
			UnInitializePhysics();
		}
	}

	void Actor::InitializePhysics()
	{
		if (!mPhysicBody)
		{
			mPhysicBody = PhysicsSystem::Get().AddListener(this);
		}
	}

	void Actor::UnInitializePhysics()
	{
		if (mPhysicBody)
		{
			PhysicsSystem::Get().RemoveListener(mPhysicBody);
		}
	}

	void Actor::UpdatePhysicsBodyTransform()
	{
		if (mPhysicBody)
		{
			float physicsScale = PhysicsSystem::Get().GetPhysicsScale();
			b2Vec2 pos(GetActorLocation().x * physicsScale, GetActorLocation().y * physicsScale);
			float rotation = DegreesToRadians(GetActorRotation());

			mPhysicBody->SetTransform(pos, rotation);
		}
	}

	void Actor::CenterPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
}
