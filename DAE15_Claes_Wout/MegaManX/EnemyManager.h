#pragma once
#include <vector>

class Enemy;
class BulletManager;
class Player;

class EnemyManager final
{
public:

	explicit EnemyManager(BulletManager* bulletManager = nullptr, Player* player = nullptr);
	~EnemyManager();

	void Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	void Draw() const;
	void Hit(int enemy, int damage);

	bool GetBossDead() const;
	bool GetFinalBossDead();

	void SpawnBallDeVoux(Vector2f spawnPosition, BulletManager* bulletManager, Player* player);

	void SetVolume(const int Volume);

	std::vector<Rectf> GetEnemyHitBoxes();

	// RULE OF FIVE
	EnemyManager(const EnemyManager& other) = delete;
	EnemyManager& operator=(const EnemyManager& rhs) = delete;
	EnemyManager(EnemyManager&& rhs) = delete;
	EnemyManager& operator=(EnemyManager&& rhs) = delete;

private:

	// FUNCTIONS
	void PushEnemies(BulletManager* bulletManager, Player* player);

	// DATAMEMBERS
	std::vector<Enemy*> m_EnemiesPtr;
	bool m_FinalBossDead{ false };
};