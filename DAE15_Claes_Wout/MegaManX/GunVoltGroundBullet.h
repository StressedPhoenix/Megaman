#pragma once
#include "Bullet.h"

class GunVoltGroundBullet final : public Bullet
{
public:

	explicit GunVoltGroundBullet(const Vector2f& spawnPos, bool goingRight);
	~GunVoltGroundBullet();

	virtual void Update(float elapsedSec, const std::vector<Rectf>& EnemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox);
	virtual void Draw() const override;

	virtual void SetVolume(const int Volume);

	// RULE OF FIVE
	GunVoltGroundBullet(const GunVoltGroundBullet& other) = delete;
	GunVoltGroundBullet& operator=(const GunVoltGroundBullet& rhs) = delete;
	GunVoltGroundBullet(GunVoltGroundBullet&& rhs) = delete;
	GunVoltGroundBullet& operator=(GunVoltGroundBullet&& rhs) = delete;
};

