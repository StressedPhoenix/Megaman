#pragma once
#include <vector>
#include "XBullet.h"
class Bullet;
class Player;
class EnemyManager;

class BulletManager final
{
public:
	
	// ENUM CLASS
	enum class BulletID
	{
		XBullet,
		GunVoltBullet,
		GunVoltMissile,
		BeeBladerBullet,
		BeeBladerMissile
	};

	BulletManager();
	~BulletManager();

	void SetPlayerPtr(Player* player);
	void SetEnemyManagerPtr(EnemyManager* enemyManager);
	void Update(float elapsedSec, const std::vector<Rectf>& EnemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	void Draw() const;
	void Shoot(const Vector2f& StartPos, bool rightDirection, const BulletID shooterID, const XBullet::ChargeLevel chargeLevel = XBullet::ChargeLevel::NoCharge);
	std::vector<Rectf> GetBulletHitBoxes() const;

	void SetVolume(const int Volume);

	// RULE OF FIVE
	BulletManager(const BulletManager& other) = delete;
	BulletManager& operator=(const BulletManager& rhs) = delete;
	BulletManager(BulletManager&& rhs) = delete;
	BulletManager& operator=(BulletManager&& rhs) = delete;

private:

	std::vector<Bullet*> m_BulletsPtr;
	std::vector<BulletID> m_BulletIDs;
	Player* m_PlayerPtr{ nullptr };
	EnemyManager* m_EnemyManagerPtr{ nullptr };
};

