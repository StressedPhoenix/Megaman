#include "pch.h"
#include "BallDeVoux.h"
#include "Texture.h"
#include "Player.h"

BallDeVoux::BallDeVoux(Vector2f position, BulletManager* bulletManager, Player* player)
	:Enemy(position, bulletManager, player)
{
	m_EnemyTexturePtr = new Texture{ "Enemy/BallDeVoux/BallDeVoux.png" };

	float scale{ 3 };

	m_Health = 4;
	m_EnemyWidth = (m_EnemyTexturePtr->GetWidth() / 20 * scale);
	m_EnemyHeight = (m_EnemyTexturePtr->GetHeight() / 3 * scale);
	m_EnemyHitBox = Rectf{ position.x, position.y, m_EnemyWidth, m_EnemyHeight };
}

BallDeVoux::~BallDeVoux()
{
}

void BallDeVoux::Draw() const
{
	if (!m_Dead)
	{
		glPushMatrix();
		{
			float scale{ 3 };

			glTranslatef(m_EnemyPosition.x, m_EnemyPosition.y, 0);
			glScalef(scale, scale, 0);

			Rectf drawBox{ 0,0,0,0 };
			switch (m_State)
			{
			case State::Roll:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 20) * (static_cast<int>(m_CurrentFrame) % 4), (m_EnemyTexturePtr->GetHeight() / 3) * 0, m_EnemyTexturePtr->GetWidth() / 20, m_EnemyTexturePtr->GetHeight() / 3 };
				break;
			case State::GetUp:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 20) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 3) * 1, m_EnemyTexturePtr->GetWidth() / 20, m_EnemyTexturePtr->GetHeight() / 3 };
				break;
			case State::Walk:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 20) * (static_cast<int>(m_CurrentFrame) % 8), (m_EnemyTexturePtr->GetHeight() / 3) * 2, m_EnemyTexturePtr->GetWidth() / 20, m_EnemyTexturePtr->GetHeight() / 3 };
				break;
			}
			m_EnemyTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
	Enemy::Draw();
}

void BallDeVoux::Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	bool playerInRange{ m_EnemyPosition.x - m_PlayerPtr->GetPosition().x <= 500.f };

	m_Active = playerInRange && !m_Dead;
	
	if (m_EnemyPosition.x < m_PlayerPtr->GetPosition().x - 1000.f)
	{
		m_Dead = true;
	}

	if (!m_Dead && playerInRange)
	{
		if (utils::IsOverlapping(m_EnemyHitBox, m_PlayerPtr->GetPlayerHitBox()))
		{
			m_PlayerPtr->PlayerHit(2);
		}

		m_EnemyHitBox = Rectf{ m_EnemyPosition.x, m_EnemyPosition.y, m_EnemyWidth, m_EnemyHeight };
		m_CurrentFrame += 8 * elapsedSec;
		m_Timer += 1 * elapsedSec;

		if (m_Health <= 0)
		{
			m_CurrentFrame = 0;
			m_Dead = true;
			m_EnemyHitBox = Rectf{ 0,0,0,0 };
		}

		switch (m_State)
		{
		case State::Roll:
			m_Speed = 50.f;
			if (m_Timer >= 0.5)
			{
				m_CurrentFrame = 0;
				m_Timer = 0;
				m_State = State::GetUp;
			}
			m_EnemyPosition.x -= m_Speed * elapsedSec;
			break;
		case State::GetUp:
			if (m_Timer >= 2)
			{
				m_CurrentFrame = 0;
				m_Timer = 0;
				m_State = State::Walk;
			}

			break;
		case State::Walk:
			m_Speed = 100.f;
			m_EnemyPosition.x -= m_Speed * elapsedSec;
			break;
		}
	}

	Enemy::Update(elapsedSec, bulletHitBox, MapHitBoxes);
}

void BallDeVoux::SetVolume(int Volume) const
{
	Enemy::SetVolume(Volume);
}