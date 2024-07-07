#include "enemy/Boss.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
	Boss::Boss(World* world)
		: EnemySpaceship(world, "SpaceShooterRedux/PNG/Enemies/boss.png"),
		mSpeed(100.f),
		mBaseSpeed(100.f),
		mSwitchDistanceToEdge(100.f),
		mBaseShooterLeft(this, 1.5f, {55.f, -45.f}),
		mBaseShooterRight(this, 1.5f, {55.f, 45.f}),
		mThreeWayShooter(this, 6.f, {110.f, 0.f}),
		mFrontalWiperLeft(this, 8.f, {30.f, -130.f}),
		mFrontalWiperRight(this, 8.f, {30.f, 130.f}),
		mFinalStageShooterLeft(this, 0.4f, {5.f, -150.f}),
		mFinalStageShooterRight(this, 0.4f, {5.f, 150.f}),
		mStage(1)
	{
		SetActorRotation(90.f);
		SetVelocity({mSpeed, 0.f});
		SetRewardSpawnWeight(0.f);
		HealthComponent& healthComp = GetHealthComp();
		healthComp.SetInitialHealth(3000.f, 3000.f);
	}

	void Boss::Tick(float deltaTime)
	{
		EnemySpaceship::Tick(deltaTime);
		ShootBaseShooters();
		ShootThreeWayShooter();
		ShootFrontalWipers();
		if (mStage == 4)
		{
			mFinalStageShooterLeft.Shoot();
			mFinalStageShooterRight.Shoot();
		}

		CheckMove();
	}

	void Boss::BeginPlay()
	{
		EnemySpaceship::BeginPlay();
		HealthComponent& healthComp = GetHealthComp();
		healthComp.SetInitialHealth(3000.f, 3000.f);
		healthComp.onHealthChanged.BindAction(GetWeakRef(), &Boss::HealthChanged);
	}

	void Boss::CheckMove()
	{
		if (GetActorLocation().x > GetWindowSize().x - mSwitchDistanceToEdge)
		{
			SetVelocity({-mSpeed, 0.f});
		}
		else if (GetActorLocation().x < mSwitchDistanceToEdge)
		{
			SetVelocity({mSpeed, 0.f});
		}
	}

	void Boss::ShootBaseShooters()
	{
		mBaseShooterLeft.Shoot();
		mBaseShooterRight.Shoot();
	}

	void Boss::ShootThreeWayShooter()
	{
		mThreeWayShooter.Shoot();
	}

	void Boss::ShootFrontalWipers()
	{
		mFrontalWiperLeft.Shoot();
		mFrontalWiperRight.Shoot();
	}

	void Boss::HealthChanged(float amt, float currentHealth, float maxHealth)
	{
		float percentLeft = currentHealth / maxHealth;
		if (percentLeft < 0.7f && percentLeft > 0.5f)
		{
			SetStage(2);
		}

		if (percentLeft < 0.5f && percentLeft > 0.3f)
		{
			SetStage(3);
		}

		if (percentLeft < 0.3f)
		{
			SetStage(4);
		}
	}

	void Boss::SetStage(int newStage)
	{
		mStage = newStage;
		mBaseShooterLeft.SetCurrentLevel(mStage);
		mBaseShooterRight.SetCurrentLevel(mStage);
		mThreeWayShooter.SetCurrentLevel(mStage);
		mFrontalWiperLeft.SetCurrentLevel(mStage);
		mFrontalWiperRight.SetCurrentLevel(mStage);
		mSpeed = mStage * mBaseSpeed * 0.6f;
	}
}