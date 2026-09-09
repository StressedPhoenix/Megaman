#include "pch.h"
#include "BeeBlader.h"
#include "Texture.h"
#include "EnemyManager.h"
#include "Player.h"
#include "BulletManager.h"

BeeBlader::BeeBlader(Vector2f position, const float& lowerLimit, BulletManager* bulletManager, Player* player, EnemyManager* enemyManager)
	:Enemy(position, bulletManager, player)
	,m_EnemyManager{enemyManager}
	,m_LowerLimit{lowerLimit}
{
	m_EnemyTexturePtr = new Texture{ "Enemy/BeeBlader/BeeBlader.png" };

	float scale{ 4 };

	m_Health = 20;
	m_Speed = 50.f;
	m_EnemyWidth = (m_EnemyTexturePtr->GetWidth() / 3 * scale);
	m_EnemyHeight = (m_EnemyTexturePtr->GetHeight() / 3 * scale);
	m_EnemyHitBox = Rectf{ position.x, position.y, m_EnemyWidth, m_EnemyHeight };
}

BeeBlader::~BeeBlader()
{
}

void BeeBlader::Draw() const
{
	if (m_Dead)
	{
		glPushMatrix();
		{
			float scale{ 4 };

			glTranslatef(m_EnemyPosition.x, m_EnemyPosition.y, 0);
			glScalef(scale, scale, 0);
			Rectf drawBox{ (m_EnemyTexturePtr->GetWidth() / 3) * (static_cast<int>(0)), (m_EnemyTexturePtr->GetHeight() / 3) * 2, m_EnemyTexturePtr->GetWidth() / 3, m_EnemyTexturePtr->GetHeight() / 3 };;
			m_EnemyTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		{
			float scale{ 4 };

			glTranslatef(m_EnemyPosition.x, m_EnemyPosition.y, 0);
			glScalef(scale, scale, 0);
			Rectf drawBox{ 0,0,0,0 };

			switch (m_State)
			{
			case BeeBlader::State::ComeDown:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 3) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 3) * 0, m_EnemyTexturePtr->GetWidth() / 3, m_EnemyTexturePtr->GetHeight() / 3 };
				break;
			case State::Idle:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 3) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 3) * 0, m_EnemyTexturePtr->GetWidth() / 3, m_EnemyTexturePtr->GetHeight() / 3 };
				break;
			case BeeBlader::State::ShootBullet:
				if (m_Shot)
				{
					drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 3) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 3) * 0, m_EnemyTexturePtr->GetWidth() / 3, m_EnemyTexturePtr->GetHeight() / 3 };
				}
				else
				{
					drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 3) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 3) * 1, m_EnemyTexturePtr->GetWidth() / 3, m_EnemyTexturePtr->GetHeight() / 3 };
				}
				break;
			case BeeBlader::State::ShootMissile:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 3) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 3) * 0, m_EnemyTexturePtr->GetWidth() / 3, m_EnemyTexturePtr->GetHeight() / 3 };
				break;
			}
			m_EnemyTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
	Enemy::Draw();
}

void BeeBlader::Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	bool playerInRange{ m_EnemyPosition.x - m_PlayerPtr->GetPosition().x <= 500.f };
	utils::HitInfo hitInfo{};
	Vector2f shootPos{ 0, 0 };

	m_EnemyHitBox = Rectf{ m_EnemyPosition.x, m_EnemyPosition.y, m_EnemyWidth, m_EnemyHeight };

	m_Active = playerInRange && !m_Dead;

	if (m_EnemyPosition.x < m_PlayerPtr->GetPosition().x - 1000.f)
	{
		m_Dead = true;
	}

	if (m_Dead && m_EnemyPosition.y > m_LowerLimit)
	{
		m_EnemyHitBox = Rectf{ 0, 0, 0, 0 };
		m_EnemyPosition.y -= 140 * elapsedSec;
	}

	if (!m_Dead && playerInRange)
	{
		if (utils::IsOverlapping(m_EnemyHitBox, m_PlayerPtr->GetPlayerHitBox()))
		{
			m_PlayerPtr->PlayerHit(1);
		}

		m_CurrentFrame += 8 * elapsedSec;
		m_Timer += 1 * elapsedSec;

		if (m_Health <= 0)
		{
			m_CurrentFrame = 0;
			m_Dead = true;
		}

		switch (m_State)
		{
		case State::ComeDown:
			m_EnemyPosition.y -= 150.f * elapsedSec;

			for(int idx{0}; idx < MapHitBoxes.size(); ++idx)
			{
				if (utils::Raycast(MapHitBoxes[idx], m_EnemyPosition, Vector2f{ m_EnemyPosition.x, m_EnemyPosition.y - 20.f }, hitInfo))
				{
					m_State = State::Idle;
				}
			}
			break;
		case State::Idle:
			m_EnemyPosition.x -= m_Speed * elapsedSec;

			if (m_Timer >= 3)
			{
				int attack{ 2 + rand() % 3 };
				m_State = static_cast<State>(attack);
				m_Timer = 0;
			}

			break;
		case State::ShootBullet:
			m_EnemyPosition.x -= m_Speed * elapsedSec;

			if(m_Timer >= 0 && m_Timer < 0.1 && !m_Shot)
			{
				shootPos = Vector2f{ m_EnemyPosition.x + 75, m_EnemyPosition.y + 30 };
				m_BulletManagerPtr->Shoot(shootPos, false, BulletManager::BulletID::BeeBladerBullet);
				m_Shot = true;
			}
			else if (m_Timer >= 0.2 && m_Timer < 0.3)
			{
				m_Shot = false;
			}

			else if (m_Timer >= 0.3 && m_Timer < 0.4 && !m_Shot)
			{
				m_BulletManagerPtr->Shoot(shootPos, false, BulletManager::BulletID::BeeBladerBullet);
				m_Shot = true;
			}
			else if (m_Timer >= 0.5 && m_Timer < 0.6)
			{
				m_Shot = false;
			}

			else if (m_Timer >= 0.6 && m_Timer < 0.7 && !m_Shot)
			{
				m_BulletManagerPtr->Shoot(shootPos, false, BulletManager::BulletID::BeeBladerBullet);
				m_Shot = true;
			}
			else if (m_Timer >= 0.8 && m_Timer < 0.9)
			{
				m_Shot = false;
			}

			else if (m_Timer >= 1)
			{
				m_State = State::Idle;
				m_Timer = 0;
			}
			break;
		case State::ShootMissile:
			m_EnemyPosition.x -= m_Speed * elapsedSec;

			shootPos = Vector2f{ m_EnemyPosition.x, m_EnemyPosition.y + m_EnemyHeight / 4 };
			m_BulletManagerPtr->Shoot(shootPos, false, BulletManager::BulletID::BeeBladerMissile);

			m_State = State::Idle;
			m_Timer = 0;

			break;
		case State::SpawnEnemy:
			m_EnemyPosition.x -= m_Speed * elapsedSec;

			m_EnemyManager->SpawnBallDeVoux(Vector2f{ m_EnemyPosition.x - 30.f, m_EnemyPosition.y }, m_BulletManagerPtr, m_PlayerPtr);
			m_State = State::Idle;
			m_Timer = 0;
		}
	}
	Enemy::Update(elapsedSec, bulletHitBox, MapHitBoxes);
}

void BeeBlader::SetVolume(int Volume) const
{
	Enemy::SetVolume(Volume);
}
