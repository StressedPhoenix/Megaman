#pragma once
#include "Enemy.h"
class EnemyManager;

class BeeBlader final : public Enemy
{
public:

	explicit BeeBlader(Vector2f position, const float& lowerLimit, BulletManager* bulletManager = nullptr, Player* player = nullptr, EnemyManager* enemyManager = nullptr);
	~BeeBlader();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes) override;
	virtual void SetVolume(int Volume) const override;

	// RULE OF FIVE
	BeeBlader(const BeeBlader& other) = delete;
	BeeBlader& operator=(const BeeBlader& rhs) = delete;
	BeeBlader(BeeBlader&& rhs) = delete;
	BeeBlader& operator=(BeeBlader&& rhs) = delete;

private:

	// ENUM CLASSES
	enum class State
	{
		ComeDown = 0,
		Idle = 1,
		ShootBullet = 2,
		ShootMissile = 3,
		SpawnEnemy = 4
	};

	// DATAMEMBERS
	State m_State{ State::ComeDown };
	EnemyManager* m_EnemyManager{ nullptr };
	bool m_Shot{ false };
	float m_LowerLimit{ 0.f };
};