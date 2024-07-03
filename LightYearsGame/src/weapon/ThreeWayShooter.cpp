#include "weapon/ThreeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset)
		: Shooter(owner),
		mShooterLeft(owner, cooldownTime, localOffset + sf::Vector2f{ 10.f, -10.f }, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
		mShooterMid(owner, cooldownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
		mShooterRight(owner, cooldownTime, localOffset + sf::Vector2f{ 10.f, 10.f }, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
		mTopLevelShooterLeft(owner, cooldownTime, localOffset + sf::Vector2f{ 10.f, 10.f }, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"),
		mTopLevelShooterRight(owner, cooldownTime, localOffset + sf::Vector2f{ 10.f, -10.f }, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png")
	{

	}

	void ThreeWayShooter::IncrementLevel(int amt)
	{
		Shooter::IncrementLevel(amt);
		mShooterLeft.IncrementLevel(amt);
		mShooterMid.IncrementLevel(amt);
		mShooterRight.IncrementLevel(amt);
		mTopLevelShooterLeft.IncrementLevel(amt);
		mTopLevelShooterRight.IncrementLevel(amt);
	}

	void ThreeWayShooter::ShootImpl()
	{
		mTopLevelShooterLeft.Shoot();
		mTopLevelShooterRight.Shoot();

		if (GetCurrentLevel() >= GetMaxLevel() - 1)
		{
			mShooterMid.Shoot();
		}

		if (GetCurrentLevel() == GetMaxLevel())
		{
			mShooterLeft.Shoot();
			mShooterRight.Shoot();
		}
	}
}