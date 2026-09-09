#include "pch.h"
#include "GunVolt.h"
#include "SoundEffect.h"
#include "Texture.h"
#include "BulletManager.h"
#include "Player.h"

GunVolt::GunVolt(Vector2f position, BulletManager* bulletManager, Player* player)
	:Enemy(position, bulletManager, player)
{
	m_MissileFireSoundPtr = new SoundEffect{ "Sound/Enemy/GunVolt/Enemy_Missle_Fire.wav" };
	m_GroundBulletFireSoundPtr = new SoundEffect{ "Sound/Enemy/GunVolt/Enemy_Mech_Shoot.wav" };

	m_EnemyTexturePtr = new Texture{ "Enemy/GunVolt/GunVolt.png" };

	float scale{ 4 };

	m_Health = 15;
	m_EnemyWidth = (m_EnemyTexturePtr->GetWidth() / 7 * scale);
	m_EnemyHeight = (m_EnemyTexturePtr->GetHeight() / 4 * scale);
	m_EnemyHitBox = Rectf{ position.x, position.y, m_EnemyWidth, m_EnemyHeight };
}

GunVolt::~GunVolt()
{
	delete m_MissileFireSoundPtr;
	m_MissileFireSoundPtr = nullptr;

	delete m_GroundBulletFireSoundPtr;
	m_GroundBulletFireSoundPtr = nullptr;
}

void GunVolt::Draw() const
{
	if(!m_Dead)
	{
		glPushMatrix();
		{
			float scale{ 4 };

			glTranslatef(m_EnemyPosition.x, m_EnemyPosition.y, 0);
			glScalef(scale, scale, 0);

			Rectf drawBox{0,0,0,0};

			switch (m_State)
			{
			case State::Idle:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 7) * (static_cast<int>(m_CurrentFrame) % 2), (m_EnemyTexturePtr->GetHeight() / 4) * 0, m_EnemyTexturePtr->GetWidth() / 7, m_EnemyTexturePtr->GetHeight() / 4 };
				break;
			case State::AttackStart:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 7) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 4) * 0, m_EnemyTexturePtr->GetWidth() / 7, m_EnemyTexturePtr->GetHeight() / 4 };
				break;
			case State::GroundAttack:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 7) * (static_cast<int>(m_CurrentFrame) % 3), (m_EnemyTexturePtr->GetHeight() / 4) * 2, m_EnemyTexturePtr->GetWidth() / 7, m_EnemyTexturePtr->GetHeight() / 4 };
				break;
			case State::MissileAttack:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 7) * (static_cast<int>(m_CurrentFrame) % 6), (m_EnemyTexturePtr->GetHeight() / 4) * 1, m_EnemyTexturePtr->GetWidth() / 7, m_EnemyTexturePtr->GetHeight() / 4 };
				break;
			case State::AttackDone:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 7) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 4) * 3, m_EnemyTexturePtr->GetWidth() / 7, m_EnemyTexturePtr->GetHeight() / 4 };
				break;
			}
			m_EnemyTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
	Enemy::Draw();
}

void GunVolt::Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	bool playerInRange{ m_EnemyPosition.x - m_PlayerPtr->GetPosition().x <= 500.f };

	m_Active = playerInRange && !m_Dead;

	if (m_EnemyPosition.x < m_PlayerPtr->GetPosition().x - 1000.f)
	{
		m_Dead = true;
	}

	if(!m_Dead && playerInRange)
	{
		if (utils::IsOverlapping(m_EnemyHitBox, m_PlayerPtr->GetPlayerHitBox()))
		{
			m_PlayerPtr->PlayerHit(1);
		}

		m_Timer += 1 * elapsedSec;

		switch (m_State)
		{
		case State::Idle:
			m_CurrentFrame += 1 * elapsedSec;
			if (m_Timer >= 2)
			{
				m_State = State::AttackStart;
				m_CurrentFrame = 0;
				m_Timer = 0;
			}

			break;
		case State::AttackStart:
			m_CurrentFrame += 10 * elapsedSec;

			if (m_Timer >= 0.7)
			{
				int attack{ rand() % 2 };
				if (attack)
				{
					m_State = State::MissileAttack;
					m_CurrentFrame = 0;
					m_Timer = 0;
				}
				else
				{
					m_State = State::GroundAttack;
					m_CurrentFrame = 0;
					m_Timer = 0;
				}
			}

			break;
		case State::GroundAttack:
			m_CurrentFrame += 10 * elapsedSec;

			if (m_Timer >= 0.3)
			{
				m_State = State::AttackDone;

				m_GroundBulletFireSoundPtr->Play(false);
				Vector2f shootPos{ m_EnemyPosition.x, m_EnemyPosition.y };
				m_BulletManagerPtr->Shoot(shootPos, false, BulletManager::BulletID::GunVoltBullet);

				m_CurrentFrame = 0;
				m_Timer = 0;
			}
			break;
		case State::MissileAttack:
			m_CurrentFrame += 10 * elapsedSec;

			if (m_Timer >= 0.6)
			{
				m_State = State::AttackDone;

				m_MissileFireSoundPtr->Play(false);
				Vector2f shootPos{ m_EnemyPosition.x, m_EnemyPosition.y + m_EnemyHeight / 4 };
				m_BulletManagerPtr->Shoot(shootPos, false, BulletManager::BulletID::GunVoltMissile);

				m_CurrentFrame = 0;
				m_Timer = 0;
			}
			break;
		case State::AttackDone:
			m_CurrentFrame += 10 * elapsedSec;

			if (m_Timer >= 0.7)
			{
				m_State = State::Idle;
				m_CurrentFrame = 0;
				m_Timer = 0;
			}
			break;
		}

		if (m_Health <= 0)
		{
			m_CurrentFrame = 0;
			m_Dead = true;
			m_EnemyHitBox = Rectf{ 0,0,0,0 };
		}
	}
	
	Enemy::Update(elapsedSec, bulletHitBox, MapHitBoxes);
}

void GunVolt::SetVolume(int Volume) const
{
	m_MissileFireSoundPtr->SetVolume(Volume);
	m_GroundBulletFireSoundPtr->SetVolume(Volume);
	m_DeathSoundPtr->SetVolume(Volume);

	Enemy::SetVolume(Volume);
}