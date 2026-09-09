#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(Point2f startpos, bool left, bool right, bool up, bool down)
	:m_BulletPosition{startpos}
{
	m_BulletSound = new SoundEffect("Tears_Fire.mp3");
	if (left) m_BulletDirection = BulletDirection::Left;
	if (right) m_BulletDirection = BulletDirection::Right;
	if (up) m_BulletDirection = BulletDirection::Up;
	if (down) m_BulletDirection = BulletDirection::Down;
	m_BulletTexturePtr = new Texture("Bullet.PNG");
	if (m_BulletSound->IsLoaded())
	{
		m_BulletSound->Play(false);
	}
}

Bullet::~Bullet()
{
	delete m_BulletTexturePtr;
	m_BulletTexturePtr = nullptr;
	delete m_BulletSound;
	m_BulletSound = nullptr;
}

void Bullet::Draw() const
{
	m_BulletTexturePtr->Draw(Rectf(m_BulletPosition.x, m_BulletPosition.y, bulletScale, bulletScale));
}

void Bullet::Update(float elapsedSec)
{
	switch (m_BulletDirection)
	{
	case BulletDirection::Up:
		m_BulletPosition.y += m_BulletSpeed * elapsedSec;
		break;
	case BulletDirection::Down:
		m_BulletPosition.y -= m_BulletSpeed * elapsedSec;
		break;
	case BulletDirection::Left:
		m_BulletPosition.x -= m_BulletSpeed * elapsedSec;
		if (m_BulletDistance >= (m_MaxDistance - (m_MaxDistance / 2)))
		{
			m_Gravity += 100 * elapsedSec;
			m_BulletPosition.y -= m_Gravity * elapsedSec;
		}
		break;
	case BulletDirection::Right:
		m_BulletPosition.x += m_BulletSpeed * elapsedSec;
		if (m_BulletDistance >= (m_MaxDistance - (m_MaxDistance / 2)))
		{
			m_Gravity += 100 * elapsedSec;
			m_BulletPosition.y -= m_Gravity * elapsedSec;
		}
		break;
	}
	m_BulletDistance += m_BulletSpeed * elapsedSec;
}

bool Bullet::HitGround()
{
	if (m_BulletDistance >= m_MaxDistance)
	{
		return true;
	}
	return false;
}

Rectf Bullet::GetBulletHitBox() const
{
	return Rectf(m_BulletPosition.x, m_BulletPosition.y, bulletScale, bulletScale);
}

void Bullet::Hit()
{
	m_Hit = true;
}

bool Bullet::GetHit() const
{
	return m_Hit;
}

