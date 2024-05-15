#include "weapon/FrontalWiper.h"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, float cooldownTime, const sf::Vector2f& localOffset, float width)
		: Shooter(owner),
		mWidth(width),
		mShooter1(owner, cooldownTime, { localOffset.x, localOffset.y - width / 2.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"),
		mShooter2(owner, cooldownTime, { localOffset.x, localOffset.y - width / 6.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"),
		mShooter3(owner, cooldownTime, { localOffset.x, localOffset.y + width / 6.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png"),
		mShooter4(owner, cooldownTime, { localOffset.x, localOffset.y + width / 2.f }, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png")
	{
	}

	void FrontalWiper::ShootImpl()
	{
		mShooter1.Shoot();
		mShooter2.Shoot();
		mShooter3.Shoot();
		mShooter4.Shoot();
	}
}