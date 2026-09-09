#include "pch.h"
#include "GunVoltGroundBullet.h"
#include "Texture.h"
#include "SoundEffect.h"

GunVoltGroundBullet::GunVoltGroundBullet(const Vector2f& spawnPos, bool goingRight)
	:Bullet(spawnPos, goingRight)
{
	m_BulletTexturePtr = new Texture{ "Mech_Enemy/Ground_Bullet.png" };
	m_BulletHitSoundPtr = new SoundEffect{ "Sound/Enemy/GunVolt/Enemy_Mech_Shoot.wav" };

	m_Speed = 400.f;
	m_BulletHitBox = Rectf{ m_BulletPosition.x, m_BulletPosition.y, m_BulletTexturePtr->GetWidth() / 3, m_BulletTexturePtr->GetHeight() };

	m_Damage = 3;
}

GunVoltGroundBullet::~GunVoltGroundBullet()
{
}

void GunVoltGroundBullet::Update(float elapsedSec, const std::vector<Rectf>& enemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox)
{
	m_FrameNr += 10 * elapsedSec;
	Bullet::Update(elapsedSec, enemyHitBoxes, MapHitBoxes, playerHitBox);
}

void GunVoltGroundBullet::Draw() const
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

void GunVoltGroundBullet::SetVolume(const int Volume)
{
	Bullet::SetVolume(Volume);
}
