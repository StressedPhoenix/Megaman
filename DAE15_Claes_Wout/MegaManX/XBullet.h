#pragma once
#include "Bullet.h"
#include <vector>

class XBullet final : public Bullet
{
public:

	// ENUM CLASS
	enum class ChargeLevel
	{
		NoCharge = 0
		, HalfCharge = 1
		, FullCharge = 2
	};

	explicit XBullet(const Vector2f& spawnPos, bool goingRight, ChargeLevel chargeLevel);
	~XBullet();

	virtual void Update(float elapsedSec, const std::vector<Rectf>& EnemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox) override;
	virtual void Draw() const override;

	virtual void SetVolume(const int Volume);

	// RULE OF FIVE
	XBullet(const XBullet& other) = delete;
	XBullet& operator=(const XBullet& rhs) = delete;
	XBullet(XBullet&& rhs) = delete;
	XBullet& operator=(XBullet&& rhs) = delete;

private:

	std::vector<Texture*> m_XBulletTexturesPtr;
	ChargeLevel m_ChargeLevel;
};

