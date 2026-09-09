#pragma once
#include <vector>
#include "utils.h"
class Texture;
class SoundEffect;

class Bullet
{
public:

	Bullet(const Vector2f& spawnPos, bool goingRight);
	virtual ~Bullet();

	virtual void Update(float elapsedSec, const std::vector<Rectf>& EnemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox);
	virtual void Draw() const = 0;
	virtual Rectf GetBulletHitBox() const;

	virtual bool GetBulletActive();
	virtual int GetDamage();

	virtual bool BulletHitWall(const std::vector<std::vector<Vector2f>>& MapHitBoxes);

	virtual int GetHitEnemy() const;
	virtual bool GetEnemyHit() const;
	virtual bool GetPlayerHit() const;

	virtual void SetVolume(const int Volume);

	// RULE OF FIVE
	Bullet(const Bullet& other) = delete;
	Bullet& operator=(const Bullet& rhs) = delete;
	Bullet(Bullet&& rhs) = delete;
	Bullet& operator=(Bullet&& rhs) = delete;

protected:

	// FUNCTIONS
	virtual bool HitEntity(const Rectf& enemyHitBoxes);
	virtual void Hit();

	// DATAMEMBERS
	Texture* m_BulletTexturePtr;
	Rectf m_BulletHitBox;
	Vector2f m_BulletPosition;
	bool m_BulletActive{ true };
	bool m_BulletHit{ false };
	bool m_DirectionRight{ true };
	float m_Speed;
	float m_FrameNr{ 0 };
	float m_Timer{ 0 };
	int m_Damage{ 1 };
	SoundEffect* m_BulletHitSoundPtr;
	bool m_EnemyHit{ false };
	bool m_PlayerHit{ false };
	int m_HitEnemy{ 0 };
	bool m_DamageDone{ false };
};

