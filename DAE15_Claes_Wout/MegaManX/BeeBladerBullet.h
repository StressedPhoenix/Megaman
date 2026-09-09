#pragma once
#include "Bullet.h"

class BeeBladerBullet final : public Bullet
{
public:

	explicit BeeBladerBullet(const Vector2f& spawnPos, bool goingRight);
	~BeeBladerBullet();

	virtual void Update(float elapsedSec, const std::vector<Rectf>& enemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox);
	virtual void Draw() const override;

	virtual void SetVolume(const int Volume);

	// RULE OF FIVE
	BeeBladerBullet(const BeeBladerBullet& other) = delete;
	BeeBladerBullet& operator=(const BeeBladerBullet& rhs) = delete;
	BeeBladerBullet(BeeBladerBullet&& rhs) = delete;
	BeeBladerBullet& operator=(BeeBladerBullet&& rhs) = delete;
};