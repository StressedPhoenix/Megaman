#include "pch.h"
#include "BeeBladerBullet.h"
#include "Texture.h"
#include "SoundEffect.h"

BeeBladerBullet::BeeBladerBullet(const Vector2f& spawnPos, bool goingRight)
	:Bullet(spawnPos, goingRight)
{
	m_BulletTexturePtr = new Texture{ "Enemy/BeeBlader/BeeBladerBullet.png" };
	m_BulletHitSoundPtr = new SoundEffect{ "Sound/Enemy/BeeBlader/BeeBlader_Shoot.wav" };

	m_Speed = 250.f;
	m_BulletHitBox = Rectf{ m_BulletPosition.x, m_BulletPosition.y, m_BulletTexturePtr->GetWidth() / 3, m_BulletTexturePtr->GetHeight() };

	m_Damage = 2;
}

BeeBladerBullet::~BeeBladerBullet()
{
}

void BeeBladerBullet::Update(float elapsedSec, const std::vector<Rectf>& enemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox)
{
	if (m_BulletHit)
	{
		m_FrameNr += 10 * elapsedSec;
		if (m_FrameNr < 4)
		{
			m_FrameNr = 1;
		}
		if (m_FrameNr >= 2)
		{
			m_BulletActive = false;
		}
	}

	// DO Y MOVEMENT
	m_BulletPosition.y -= m_Speed * elapsedSec;

	Bullet::Update(elapsedSec, enemyHitBoxes, MapHitBoxes, playerHitBox);
}

void BeeBladerBullet::Draw() const
{
	if (m_BulletActive && !m_BulletHit)
	{
		glPushMatrix();
		{
			glTranslatef(m_BulletPosition.x, m_BulletPosition.y, 0);
			glScalef(3, 3, 0);

			Rectf drawBox{ (m_BulletTexturePtr->GetWidth() / 3) * (static_cast<int>(m_FrameNr) % 3), 0, m_BulletTexturePtr->GetWidth() / 3, m_BulletTexturePtr->GetHeight() };
			m_BulletTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
}

void BeeBladerBullet::SetVolume(const int Volume)
{
	Bullet::SetVolume(Volume);
}
