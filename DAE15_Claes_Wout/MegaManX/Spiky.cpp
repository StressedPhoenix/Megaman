#include "pch.h"
#include "Spiky.h"
#include "Texture.h"
#include "Player.h"

Spiky::Spiky(Vector2f position, BulletManager* bulletManager, Player* player)
	:Enemy(position, bulletManager, player)
{
	m_EnemyTexturePtr = new Texture{ "Enemy/Spiky/Spiky.png" };

	float scale{ 3 };

	m_Speed = 300.f;
	m_Health = 2;
	m_EnemyWidth = (m_EnemyTexturePtr->GetWidth() / 6 * scale);
	m_EnemyHeight = (m_EnemyTexturePtr->GetHeight() / 2 * scale);
	m_EnemyHitBox = Rectf{ position.x, position.y, m_EnemyWidth, m_EnemyHeight };
}

Spiky::~Spiky()
{
}

void Spiky::Draw() const
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
			case State::Normal:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 6) * (static_cast<int>(m_CurrentFrame) % 3), (m_EnemyTexturePtr->GetHeight() / 2) * 0, m_EnemyTexturePtr->GetWidth() / 6, m_EnemyTexturePtr->GetHeight() / 2 };
				break;
			case State::FallDown:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 6) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 2) * 1, m_EnemyTexturePtr->GetWidth() / 6, m_EnemyTexturePtr->GetHeight() / 2 };
				break;
			}
			m_EnemyTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
	Enemy::Draw();
}

void Spiky::Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	bool playerInRange{ m_EnemyPosition.x - m_PlayerPtr->GetPosition().x <= 500.f};

	m_Active = playerInRange && !m_Dead;

	if (m_EnemyPosition.x < m_PlayerPtr->GetPosition().x - 1000.f)
	{
		m_Dead = true;
	}

	if (!m_Dead && playerInRange && m_Speed >= 0)
	{
		if (utils::IsOverlapping(m_EnemyHitBox, m_PlayerPtr->GetPlayerHitBox()))
		{
			m_PlayerPtr->PlayerHit(4);
			m_Health = 0;
		}

		m_EnemyHitBox = Rectf{ m_EnemyPosition.x, m_EnemyPosition.y, m_EnemyWidth, m_EnemyHeight };

		if(m_EnemyPosition.x < m_PlayerPtr->GetPosition().x && m_State != State::FallDown)
		{
			m_State = State::FallDown;
			m_CurrentFrame = 0;
		}

		switch (m_State)
		{
		case State::Normal:
			m_CurrentFrame += 10 * elapsedSec;

			m_EnemyPosition.x -= m_Speed * elapsedSec;
			break;
		case State::FallDown:

			m_Timer += 1 * elapsedSec;

			if (m_Timer <= 0.6)
			{
				m_CurrentFrame += 10 * elapsedSec;
			}

			m_EnemyPosition.x -= m_Speed * elapsedSec;
			if(m_Speed > 0)
			{
				m_Speed -= 300 * elapsedSec;
			}

			if (m_Timer >= 0.7)
			{
				m_Dead = true;
				m_CurrentFrame = 0;
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

void Spiky::SetVolume(int Volume) const
{
	Enemy::SetVolume(Volume);
}