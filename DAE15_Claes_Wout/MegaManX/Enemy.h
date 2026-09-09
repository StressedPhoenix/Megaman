#pragma once
#include <vector>
class SoundEffect;
class Texture;
class BulletManager;
class Player;

class Enemy
{
public:

	explicit Enemy(Vector2f position, BulletManager* bulletManager = nullptr, Player* player = nullptr);
	virtual ~Enemy();

	virtual void Draw() const;
	virtual void Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	virtual void Hit(int damage);
	virtual Rectf GetEnemyHitBox() const;
	virtual int GetHealth() const;
	virtual bool GetActive() const;

	virtual void SetVolume(int Volume) const;

	// RULE OF FIVE
	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& rhs) = delete;
	Enemy(Enemy&& rhs) = delete;
	Enemy& operator=(Enemy&& rhs) = delete;

protected:

	// FUNCTIONS
	bool HitEntity(const Rectf& entityHitBox);

	// DATAMEMBERS
	Rectf m_EnemyHitBox{ 0,0,0,0 };
	bool m_Dead{ false };
	int m_Health{ 0 };
	float m_EnemyWidth{ 0 };
	float m_EnemyHeight{ 0 };
	SoundEffect* m_DeathSoundPtr{ nullptr };
	Texture* m_EnemyExplosionTexturePtr{ nullptr };
	Texture* m_EnemyTexturePtr{ nullptr };
	Vector2f m_EnemyPosition;
	BulletManager* m_BulletManagerPtr;
	Player* m_PlayerPtr;
	float m_CurrentFrame{ 0 };
	float m_Timer{ 0 };
	float m_Speed{ 0 };
	bool m_Exploded{ false };
	bool m_ExplosionSoundStarted{ false };
	bool m_Active{ false };
};

