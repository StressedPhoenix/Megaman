#include "pch.h"
#include "XBullet.h"
#include "Texture.h"
#include "SoundEffect.h"

XBullet::XBullet(const Vector2f& spawnPos, bool goingRight, ChargeLevel chargeLevel)
	:Bullet(spawnPos, goingRight)
	,m_ChargeLevel{chargeLevel}
{
	m_Speed = 600.f;
	m_XBulletTexturesPtr.push_back(new Texture{ "X/XBullet_Small.png" });
	m_XBulletTexturesPtr.push_back(new Texture{ "X/XBullet_Medium.png" });
	m_XBulletTexturesPtr.push_back(new Texture{ "X/XBullet_Big.png" });

	if (m_ChargeLevel == XBullet::ChargeLevel::FullCharge)
		m_BulletHitSoundPtr = new SoundEffect{ "Sound/X/Bullet/Big_Hit.wav" };
	else
		m_BulletHitSoundPtr = new SoundEffect{ "Sound/X/Bullet/Small_Hit.wav" };

	switch (m_ChargeLevel)
	{
	case XBullet::ChargeLevel::NoCharge:
		m_Damage = 1;
		break;
	case XBullet::ChargeLevel::HalfCharge:
		m_Damage = 2;
		break;
	case XBullet::ChargeLevel::FullCharge:
		m_Damage = 4;
		break;
	}
}

XBullet::~XBullet()
{
	for (int idx {0}; idx < m_XBulletTexturesPtr.size(); ++idx)
	{
		delete m_XBulletTexturesPtr[idx];
		m_XBulletTexturesPtr[idx] = nullptr;
	}
	m_XBulletTexturesPtr.clear();
}

void XBullet::Update(float elapsedSec, const std::vector<Rectf>& enemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes, const Rectf& playerHitBox)
{
	int hitboxDevider{};

	switch (m_ChargeLevel)
	{
	case XBullet::ChargeLevel::NoCharge:
		if(m_BulletHit)
		{
			m_FrameNr += 10 * elapsedSec;
			if (m_FrameNr >= 4)
			{
				m_BulletActive = false;
			}
		}
		hitboxDevider = 4;
		break;
	case XBullet::ChargeLevel::HalfCharge:
		if (!m_BulletHit && m_FrameNr <= 6)
		{
			m_FrameNr += 10 * elapsedSec;

			if (m_FrameNr >= 6)
			{
				m_FrameNr = 2;
			}
		}
		if (m_BulletHit)
		{
			m_FrameNr += 10 * elapsedSec;
			if (m_FrameNr < 6)
			{
				m_FrameNr = 6;
			}
			if (m_FrameNr >= 12)
			{
				m_BulletActive = false;
			}
		}
		hitboxDevider = 12;
		break;
	case XBullet::ChargeLevel::FullCharge:
		if (!m_BulletHit && m_FrameNr <= 5)
		{
			m_FrameNr += 10 * elapsedSec;

			if (m_FrameNr >= 5)
			{
				m_FrameNr = 2;
			}
		}
		if (m_BulletHit)
		{
			m_FrameNr += 10 * elapsedSec;
			if (m_FrameNr < 4)
			{
				m_FrameNr = 4;
			}
			if (m_FrameNr >= 10)
			{
				m_BulletActive = false;
			}
		}
		hitboxDevider = 10;
		break;
	}

	m_BulletHitBox = Rectf{ m_BulletPosition.x, m_BulletPosition.y, m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetWidth() / hitboxDevider,
		m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetHeight() / hitboxDevider};
	Bullet::Update(elapsedSec, enemyHitBoxes, MapHitBoxes, playerHitBox);
}

void XBullet::Draw() const
{
	int hitboxDevider{};

	if (m_BulletActive)
	{
		Rectf drawBox{};

		switch (m_ChargeLevel)
		{
		case XBullet::ChargeLevel::NoCharge:
			hitboxDevider = 4;
			drawBox = Rectf{ (m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetWidth() / hitboxDevider) * (int)m_FrameNr, 0,
				m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetWidth() / hitboxDevider, m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetHeight() };
			break;
		case XBullet::ChargeLevel::HalfCharge:
			hitboxDevider = 12;
			drawBox = Rectf{ (m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetWidth() / hitboxDevider) * (int)m_FrameNr, 0,
				m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetWidth() / hitboxDevider, m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetHeight() };
			break;
		case XBullet::ChargeLevel::FullCharge:
			hitboxDevider = 10;
			drawBox = Rectf{ (m_XBulletTexturesPtr[(int)m_ChargeLevel]->GetWidth() / hitboxDevider) * (int)m_FrameNr, 0,
				m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetWidth() / hitboxDevider, m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetHeight() };
			break;
		}

		glPushMatrix();
		glTranslatef(m_BulletPosition.x + ((m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->GetWidth() / hitboxDevider) * !m_DirectionRight), m_BulletPosition.y, 0);
		glRotatef(180 * !m_DirectionRight, 0, 1, 0);

		m_XBulletTexturesPtr[static_cast<int>(m_ChargeLevel)]->Draw(Vector2f{ 0,0 }, drawBox);

		glPopMatrix();
	}
}

void XBullet::SetVolume(const int Volume)
{
	m_BulletHitSoundPtr->SetVolume(Volume);
	Bullet::SetVolume(Volume);
}
