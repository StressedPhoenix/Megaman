#include "pch.h"
#include "GunVoltMissile.h"
#include "Texture.h"
#include "SoundEffect.h"

GunVoltMissile::GunVoltMissile(const Vector2f& spawnPos, bool goingRight)
	:Bullet(spawnPos, goingRight)
{
	m_BulletTexturePtr = new Texture{ "Mech_Enemy/Rocket.png" };
	m_BulletHitSoundPtr = new SoundEffect{ "Sound/Enemy/GunVolt/Enemy_Missle_Fire.wav" };

	m_Speed = 400.f;
	m_BulletHitBox = Rectf{ m_BulletPosition.x, m_BulletPosition.y, m_BulletTexturePtr->GetWidth() / 2, m_BulletTexturePtr->GetHeight() };

	m_Damage = 4;
}

GunVoltMissile::~GunVoltMissile()
{
}


void GunVoltMissile::Update(float elapsedSec, const std::vector<Rectf>& enemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox)
{
	m_FrameNr += 10 * elapsedSec;
	Bullet::Update(elapsedSec, enemyHitBoxes, MapHitBoxes, playerHitBox);
}

void GunVoltMissile::Draw() const
{
	if (m_BulletActive && !m_BulletHit)
	{
		glPushMatrix();
		{
			glTranslatef(m_BulletPosition.x, m_BulletPosition.y, 0);
			glScalef(3, 3, 0);

			Rectf drawBox{ (m_BulletTexturePtr->GetWidth() / 2) * (static_cast<int>(m_FrameNr) % 2), 0, m_BulletTexturePtr->GetWidth() / 2, m_BulletTexturePtr->GetHeight() };
			m_BulletTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
}

void GunVoltMissile::SetVolume(const int Volume)
{
	Bullet::SetVolume(Volume);
}
