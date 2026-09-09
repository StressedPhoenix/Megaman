#include "pch.h"
#include "Fly.h"

Fly::Fly(Point2f Position)
	:m_Position{Position}
{
	m_FlyTexturePtr = new Texture{ "Fly.png" };
	m_Hitboxes = Rectf{ m_Position.x, m_Position.y, m_FlyTexturePtr->GetWidth(), m_FlyTexturePtr->GetHeight() };
}

Fly::~Fly()
{
	delete m_FlyTexturePtr;
	m_FlyTexturePtr = nullptr;
}

void Fly::Draw() const
{
	m_FlyTexturePtr->Draw(m_Position, Rectf{m_FlyTexturePtr->GetWidth() * (m_SpriteTimer % 10), 0, m_FlyTexturePtr->GetWidth(), m_FlyTexturePtr->GetHeight()});
}

void Fly::Update(float elapsedsec, std::vector<Rectf> Horizontal, std::vector <Rectf> Vertical, Rectf playerHitBox, std::vector<Bullet*> bulletvctr)
{
	m_SpriteTimer += 1;

	Point2f temp = Point2f{ playerHitBox.left - m_Position.x, playerHitBox.bottom - m_Position.y };
	float angle = atan2(temp.y, temp.x);
	double multCos{ cos(angle) };
	double multSin{ sin(angle) };

	m_Position.x += (m_Speed * multCos) * elapsedsec;
	m_Position.y += (m_Speed * multSin) * elapsedsec;
	

	for (int idx{}; idx < bulletvctr.size(); ++idx)
	{
		if (utils::IsOverlapping(Rectf{ m_Position.x, m_Position.y, m_FlyTexturePtr->GetWidth(), m_FlyTexturePtr->GetHeight() }, bulletvctr[idx]->GetBulletHitBox()))
		{
			if (!bulletvctr[idx]->GetHit())
			{
				--m_Health;
				bulletvctr[idx]->Hit();
			}
		}
	}
}

int Fly::GetHealth() const
{
	return m_Health;
}

Rectf Fly::GetHitboxes() const
{
		return m_Hitboxes;
}
