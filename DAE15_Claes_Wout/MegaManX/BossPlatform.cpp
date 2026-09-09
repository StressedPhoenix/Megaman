#include "pch.h"
#include "BossPlatform.h"
#include "Texture.h"

BossPlatform::BossPlatform(std::vector<Vector2f> startVector)
{
	m_BossPlatformTexturePtr = new Texture{ "Level/BossPlatform.png" };
	m_DestroyedBossPlatformTexturePtr = new Texture{ "Level/DestroyedBossPlatform.png" };

	m_HitBox = startVector;
	m_Position = startVector[0];
}

BossPlatform::~BossPlatform()
{
	delete m_DestroyedBossPlatformTexturePtr;
	m_DestroyedBossPlatformTexturePtr = nullptr;

	delete m_BossPlatformTexturePtr;
	m_BossPlatformTexturePtr = nullptr;
}

void BossPlatform::Update(float elapsedSec, const bool bossDead)
{
	if (!m_Destroyed && bossDead)
	{
		m_Destroyed = true;
	}
	if (m_Destroyed && m_Position.y >= 0.f)
	{
		int speed{ 140 };
		m_Position.y -= speed * elapsedSec;
		for (int idx{ 0 }; idx < m_HitBox.size(); ++idx)
		{
			m_HitBox[idx].y -= speed * elapsedSec;
		}
	}
}

void BossPlatform::Draw() const
{
	glPushMatrix();

	glTranslatef(m_Position.x, m_Position.y, 0);
	glScalef(4.5, 4.5, 0);

	if (m_Destroyed)
	{
		m_DestroyedBossPlatformTexturePtr->Draw();
	}
	else
	{
		m_BossPlatformTexturePtr->Draw();
	}

	glPopMatrix();
}

std::vector<Vector2f> BossPlatform::GetHitBox() const
{
	return m_HitBox;
}
