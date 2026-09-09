#pragma once
#include "Bullet.h"
class Player;

class BeeBladerMissile final : public Bullet
{
public:

	explicit BeeBladerMissile(const Vector2f& spawnPos, bool goingRight);
	~BeeBladerMissile();

	virtual void Update(float elapsedSec, const std::vector<Rectf>& enemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox);
	virtual void Draw() const override;

	virtual void SetVolume(const int Volume);

	// RULE OF FIVE
	BeeBladerMissile(const BeeBladerMissile& other) = delete;
	BeeBladerMissile& operator=(const BeeBladerMissile& rhs) = delete;
	BeeBladerMissile(BeeBladerMissile&& rhs) = delete;
	BeeBladerMissile& operator=(BeeBladerMissile&& rhs) = delete;

private:

	float m_SpeedY{ 0.f };
};