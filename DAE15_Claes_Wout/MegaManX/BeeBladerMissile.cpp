#include "pch.h"
#include "BeeBladerMissile.h"
#include "Player.h"
#include "Texture.h"
#include "SoundEffect.h"

BeeBladerMissile::BeeBladerMissile(const Vector2f& spawnPos, bool goingRight)
	:Bullet(spawnPos, goingRight)
{
	m_BulletTexturePtr = new Texture{ "Enemy/BeeBlader/BeeBladerMissile.png" };
	m_BulletHitSoundPtr = new SoundEffect{ "Sound/Enemy/Enemy_Die.wav" };

	m_Damage = 3;
	m_Speed = 350.f;
}

BeeBladerMissile::~BeeBladerMissile()
{
}

void BeeBladerMissile::Update(float elapsedSec, const std::vector<Rectf>& enemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox)
{
	Bullet::Update(elapsedSec, enemyHitBoxes, MapHitBoxes, playerHitBox);
}

void BeeBladerMissile::Draw() const
{
	if (m_BulletActive && !m_BulletHit)
	{
		glPushMatrix();
		{
			glTranslatef(m_BulletPosition.x, m_BulletPosition.y, 0);
			glScalef(3, 3, 0);

			Rectf drawBox{ m_BulletTexturePtr->GetWidth() * (static_cast<int>(m_FrameNr) % 3), 0, m_BulletTexturePtr->GetWidth(), m_BulletTexturePtr->GetHeight()};
			m_BulletTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
}

void BeeBladerMissile::SetVolume(const int Volume)
{
	Bullet::SetVolume(Volume);
}
