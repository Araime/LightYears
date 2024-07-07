#include "enemy/EnemySpaceship.h"
#include "framework/MathUtility.h"
#include "player/PlayerManager.h"

namespace ly
{
	EnemySpaceship::EnemySpaceship(World* owningWorld,
		const std::string& texturePath,
		float collisionDamage,
		float rewardSpawnWeight,
		const List<RewardFactoryFunc> rewards)
		: Spaceship(owningWorld, texturePath),
		mCollisionDamage(collisionDamage),
		scoreAwardAmt(10),
		mRewardSpawnWeight(rewardSpawnWeight),
		HealthID(0),
		ThreewayShooterID(1),
		FrontalWiperID(2),
		LifeID(3),
		mRewardFactories(rewards)
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

	void EnemySpaceship::SetRewardSpawnWeight(float weight)
	{
		if (weight < 0 || weight > 1)
		{
			return;
		}

		mRewardSpawnWeight = weight;
	}

	void EnemySpaceship::SpawnReward()
	{
		if (mRewardFactories.size() == 0) return;

		if (mRewardSpawnWeight < RandomRange(0.f, 1.f)) return;

		float randomReward = RandomRange(0.f, 1.f);
		if (randomReward <= 0.08f)
		{
			weak<Reward> newReward = mRewardFactories[LifeID](GetWorld());
			newReward.lock()->SetActorLocation(GetActorLocation());
		}
		else if (0.08f < randomReward && randomReward <= 0.6f)
		{
			float randomWeapon = RandomRange(0.f, 1.f);

			if (0.5f < RandomRange(0.f, 1.f))
			{
				weak<Reward> newReward = mRewardFactories[ThreewayShooterID](GetWorld());
				newReward.lock()->SetActorLocation(GetActorLocation());
			}
			else
			{
				weak<Reward> newReward = mRewardFactories[FrontalWiperID](GetWorld());
				newReward.lock()->SetActorLocation(GetActorLocation());
			}
		}
		else
		{
			weak<Reward> newReward = mRewardFactories[HealthID](GetWorld());
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