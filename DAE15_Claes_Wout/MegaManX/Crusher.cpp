#include "pch.h"
#include "Crusher.h"
#include "Texture.h"
#include "Player.h"
#include "SoundEffect.h"

Crusher::Crusher(Vector2f position, BulletManager* bulletManager, Player* player)
	:Enemy(position, bulletManager, player)
{
	m_EnemyTexturePtr = new Texture{ "Enemy/Crusher/Crusher.png" };
	m_CrusherTexturePtr = new Texture{ "Enemy/Crusher/CrusherWeapon.png" };
	m_CrusherHitSound = new SoundEffect{ "Sound/Enemy/Crusher/Crusher_Sound.wav" };

	float scale{ 3 };

	m_Health = 4;
	m_Speed = 150.f;
	m_EnemyWidth = (m_EnemyTexturePtr->GetWidth() / 2 * scale);
	m_EnemyHeight = (m_EnemyTexturePtr->GetHeight() / 2 * scale);
	m_EnemyHitBox = Rectf{ position.x, position.y, m_EnemyWidth, m_EnemyHeight };

	m_CrusherPosition = Vector2f{ position.x, position.y - 10.f };
	m_CrusherHitBox = Rectf{ m_CrusherPosition.x, m_CrusherPosition.y, m_EnemyWidth, m_CrusherTexturePtr->GetHeight() };
	m_Timer = rand() % 3;
}

Crusher::~Crusher()
{
	delete m_CrusherHitSound;
	m_CrusherHitSound = nullptr;

	delete m_CrusherTexturePtr;
	m_CrusherTexturePtr = nullptr;
}

void Crusher::Draw() const
{
	if (!m_Dead)
	{
		glPushMatrix();
		{
			float scale{ 3 };

			Rectf drawBox{ 0,0,0,0 };
			switch (m_State)
			{
			case State::Move:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 2) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 2) * 1, m_EnemyTexturePtr->GetWidth() / 2, m_EnemyTexturePtr->GetHeight() / 2 };
				break;
			case State::Attack:
				drawBox = Rectf{ (m_EnemyTexturePtr->GetWidth() / 2) * (static_cast<int>(m_CurrentFrame)), (m_EnemyTexturePtr->GetHeight() / 2) * 0, m_EnemyTexturePtr->GetWidth() / 2, m_EnemyTexturePtr->GetHeight() / 2 };

				utils::SetColor(Color4f{ 1.f,1.f,1.f,1.f });
				utils::DrawLine(Vector2f{ m_EnemyPosition.x + m_EnemyWidth / 2, m_EnemyPosition.y + m_EnemyHeight / 2 }, Vector2f{ m_CrusherPosition.x + (m_CrusherTexturePtr->GetWidth() * scale) / 2 + 10, m_CrusherPosition.y + m_CrusherTexturePtr->GetHeight() / 2 }, 2);

				glPushMatrix();
				{
					glTranslatef(m_CrusherPosition.x + 10, m_CrusherPosition.y, 0);
					glScalef(scale, scale, 0);

					Rectf crusherDrawBox{ 0, 0, m_CrusherTexturePtr->GetWidth(), m_CrusherTexturePtr->GetHeight() };
					m_CrusherTexturePtr->Draw(Vector2f{ 0,0 }, crusherDrawBox);
				}
				glPopMatrix();

				break;
			}
			glTranslatef(m_EnemyPosition.x + (m_EnemyWidth * !m_FacingRight), m_EnemyPosition.y, 0);
			glRotatef(180 * !m_FacingRight, 0, 1, 0);
			glScalef(scale, scale, 0);

			m_EnemyTexturePtr->Draw(Vector2f{ 0, 0 }, drawBox);
		}
		glPopMatrix();
	}
	Enemy::Draw();
}

void Crusher::Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	float scale{ 3 };
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
			m_PlayerPtr->PlayerHit(1);
		}
		if (utils::IsOverlapping(m_CrusherHitBox, m_PlayerPtr->GetPlayerHitBox()))
		{
			m_PlayerPtr->PlayerHit(3);
		}

		m_EnemyHitBox = Rectf{ m_EnemyPosition.x, m_EnemyPosition.y, m_EnemyWidth, m_EnemyHeight };
		m_CrusherHitBox = Rectf{ m_CrusherPosition.x, m_CrusherPosition.y, m_EnemyWidth, m_CrusherTexturePtr->GetHeight() };
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
		case Crusher::State::Move:
			if (m_FacingRight)
			{
				m_EnemyPosition.x += m_Speed * elapsedSec;
			}
			else
			{
				m_EnemyPosition.x -= m_Speed * elapsedSec;
			}
			if (m_Timer >= 2.f)
			{
				m_State = State::Attack;
				m_Timer = 0;
			}
			m_CrusherPosition = Vector2f{ m_EnemyPosition.x, m_EnemyPosition.y - 10 };
			break;
		case Crusher::State::Attack:
			if (m_PlayerPtr->GetPosition().x < m_EnemyPosition.x)
			{
				m_FacingRight = false;
			}
			else
			{
				m_FacingRight = true;
			}

			for(int idx{0}; idx < MapHitBoxes.size(); ++idx)
			{
				if (utils::IsOverlapping(MapHitBoxes[idx], m_CrusherHitBox) && !m_CrusherUp)
				{
					m_CrusherUp = true;
					m_CrusherHitSound->Play(false);
				}
			}

			if (m_CrusherUp && utils::IsOverlapping(m_EnemyHitBox, m_CrusherHitBox))
			{
				m_State = State::Move;
				m_Timer = 0;
				m_CrusherUp = false;
			}
			
			if (m_CrusherUp)
			{
				m_CrusherPosition.y += 150.f * elapsedSec;
			}
			else
			{
				m_CrusherPosition.y -= 150.f * elapsedSec;
			}
			break;
		}
	}

	Enemy::Update(elapsedSec, bulletHitBox, MapHitBoxes);
}

void Crusher::SetVolume(int Volume) const
{
	m_CrusherHitSound->SetVolume(Volume);
	Enemy::SetVolume(Volume);
}

Rectf Crusher::GetEnemyHitBox() const
{
	Rectf temp{ m_CrusherHitBox.left, m_CrusherHitBox.bottom, m_EnemyWidth, m_EnemyHitBox.bottom - m_CrusherHitBox.bottom + m_EnemyHeight };
	return temp;
}