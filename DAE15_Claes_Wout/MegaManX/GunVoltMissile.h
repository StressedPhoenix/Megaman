#pragma once
#include "Bullet.h"

class GunVoltMissile final : public Bullet
{
public:

	explicit GunVoltMissile(const Vector2f& spawnPos, bool goingRight);
	~GunVoltMissile();

	virtual void Update(float elapsedSec, const std::vector<Rectf>& EnemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox);
	virtual void Draw() const override;

	virtual void SetVolume(const int Volume);

	// RULE OF FIVE
	GunVoltMissile(const GunVoltMissile& other) = delete;
	GunVoltMissile& operator=(const GunVoltMissile& rhs) = delete;
	GunVoltMissile(GunVoltMissile&& rhs) = delete;
	GunVoltMissile& operator=(GunVoltMissile&& rhs) = delete;
};

