#include "pch.h"
#include "Bullet.h"
#include "SoundEffect.h"
#include "Texture.h"

Bullet::Bullet(const Vector2f& spawnPos, bool goingRight)
	:m_BulletTexturePtr{nullptr}
	,m_BulletPosition{spawnPos}
	,m_DirectionRight{ goingRight }
	,m_Speed{0}
	,m_BulletHitSoundPtr{nullptr}
{
}

Bullet::~Bullet()
{
	delete m_BulletTexturePtr;
	m_BulletTexturePtr = nullptr;

	delete m_BulletHitSoundPtr;
	m_BulletHitSoundPtr = nullptr;
}

void Bullet::Update(float elapsedSec, const std::vector<Rectf>& enemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox)
{
	if (m_BulletActive)
	{
		m_Timer += 1 * elapsedSec;
		if (m_Timer >= 2)
		{
			m_BulletActive = false;
		}
		if(m_BulletTexturePtr != nullptr)
		m_BulletHitBox = Rectf{ m_BulletPosition.x, m_BulletPosition.y, 10, 10 };

		if (m_BulletHit)
		{
			m_Speed = 0;
		}

		// CHECK WALL HIT
		if (BulletHitWall(MapHitBoxes))
		{
			Hit();
		}

		for (int idx{ 0 }; idx < enemyHitBoxes.size(); ++idx)
		{
			// CHECK ENEMY HIT
			if (HitEntity(enemyHitBoxes[idx]))
			{
				Hit();
				m_EnemyHit = true;
				m_HitEnemy = idx;
			}
		}

		// CHECK PLAYER HIT
		if (HitEntity(playerHitBox))
		{
			Hit();
			m_PlayerHit = true;
		}

		// DO MOVEMENT
		if (m_DirectionRight)
		{
			m_BulletPosition.x += m_Speed * elapsedSec;
		}
		else if (!m_DirectionRight)
		{
			m_BulletPosition.x -= m_Speed * elapsedSec;
		}
	}
}

Rectf Bullet::GetBulletHitBox() const
{
	return m_BulletHitBox;
}

void Bullet::Hit()
{
	if(!m_BulletHit)
	{
		m_BulletHitSoundPtr->Play(false);
	}
	m_BulletHit = true;
}

bool Bullet::GetBulletActive()
{
	return m_BulletActive;
}

int Bullet::GetDamage()
{
	if (!m_DamageDone)
	{
		m_DamageDone = true;
		return m_Damage;
	}
	else return 0;
}

bool Bullet::HitEntity(const Rectf& entityHitBox)
{
	if (utils::IsOverlapping(entityHitBox, m_BulletHitBox))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Bullet::BulletHitWall(const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	for (int idx{ 0 }; idx < MapHitBoxes.size(); idx++)
	{
		if (utils::IsOverlapping(MapHitBoxes[idx], m_BulletHitBox))
		{
			return true;
		}
	}
	return false;
}

int Bullet::GetHitEnemy() const
{
	return m_HitEnemy;
}

bool Bullet::GetEnemyHit() const
{
	return m_EnemyHit;
}

bool Bullet::GetPlayerHit() const
{
	return m_PlayerHit;
}

void Bullet::SetVolume(const int Volume)
{
	m_BulletHitSoundPtr->SetVolume(Volume);
}
