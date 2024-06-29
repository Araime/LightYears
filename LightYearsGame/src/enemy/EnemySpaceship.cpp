#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* owningWorld, 
		const std::string& texturePath, 
		float collisionDamage, 
		const List<RewardFactoryFunc> rewards)
		: Spaceship(owningWorld, texturePath),
		mCollisionDamage(collisionDamage),
		mRewardFactories(rewards),
		scoreAwardAmt(10)
	{
		SetTeamID(2);
	}

	void EnemySpaceship::Tick(float deltaTime)
	{
		Spaceship::Tick(deltaTime);
		if (IsActorOutOfWindowBounds(GetActorGlobalBounds().width * 2.f))
		{
			Destroy();
		}
	}

	void EnemySpaceship::SetScoreAwardAmt(unsigned int amt)
	{
		scoreAwardAmt = amt;
	}

	void EnemySpaceship::SpawnReward()
	{
		if (mRewardFactories.size() == 0) return;

		int pick = static_cast<int>(RandomRange(0, mRewardFactories.size()));
		if (pick >= 0 && pick < mRewardFactories.size())
		{
			weak<Reward> newReward = mRewardFactories[pick](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
		}
	}

	void EnemySpaceship::OnActorBeginOverlap(Actor* other)
	{
		Spaceship::OnActorBeginOverlap(other);
		if (IsOtherHostile(other))
		{
			other->ApplyDamage(mCollisionDamage);
		}
	}

	void EnemySpaceship::Blew()
	{
		SpawnReward();

		Player* player = PlayerManager::Get().GetPlayer();
		if (player)
		{
			player->AddScore(scoreAwardAmt);
		}
	}
}