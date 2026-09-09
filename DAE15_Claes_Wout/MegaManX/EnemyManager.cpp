#include "pch.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "BulletManager.h"
#include "GunVolt.h"
#include "Spiky.h"
#include "Crusher.h"
#include "BeeBlader.h"
#include "BallDeVoux.h"

EnemyManager::EnemyManager(BulletManager* bulletManager, Player* player)
{
	PushEnemies(bulletManager, player);
}

EnemyManager::~EnemyManager()
{
	for (int idx{ 0 }; idx < m_EnemiesPtr.size(); ++idx)
	{
		delete m_EnemiesPtr[idx];
		m_EnemiesPtr[idx] = nullptr;
	}
	m_EnemiesPtr.clear();
}

void EnemyManager::Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	for (int idx{ 0 }; idx < m_EnemiesPtr.size(); ++idx)
	{
		m_EnemiesPtr[idx]->Update(elapsedSec, bulletHitBox, MapHitBoxes);
	}
}

void EnemyManager::Draw() const
{
	for (int idx{ 0 }; idx < m_EnemiesPtr.size(); ++idx)
	{
		m_EnemiesPtr[idx]->Draw();
	}
}

void EnemyManager::Hit(int enemy, int damage)
{
	if(enemy < m_EnemiesPtr.size())
	{
		m_EnemiesPtr[enemy]->Hit(damage);
	}
}

bool EnemyManager::GetBossDead() const
{
	for (int idx{ 0 }; idx < m_EnemiesPtr.size(); ++idx)
	{
		if (m_EnemiesPtr[idx]->GetActive() && dynamic_cast<BeeBlader*>(m_EnemiesPtr[idx]) != nullptr)
		{
			if(m_EnemiesPtr[idx]->GetHealth() <= 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool EnemyManager::GetFinalBossDead()
{
	bool firstBeeBladerPassed{ false };

	for (int idx{ 0 }; idx < m_EnemiesPtr.size(); ++idx)
	{
		if (dynamic_cast<BeeBlader*>(m_EnemiesPtr[idx]) != nullptr)
		{
			if (!firstBeeBladerPassed)
			{
				firstBeeBladerPassed = true;
			}
			else
			{
				if(m_EnemiesPtr[idx]->GetHealth() <= 0)
				m_FinalBossDead = true;
			}
		}
	}
	return m_FinalBossDead;
}

void EnemyManager::SpawnBallDeVoux(Vector2f spawnPosition, BulletManager* bulletManager, Player* player)
{
	m_EnemiesPtr.push_back(new BallDeVoux{ spawnPosition, bulletManager, player });
}

void EnemyManager::SetVolume(const int Volume)
{
	for (int idx{ 0 }; idx < m_EnemiesPtr.size(); ++idx)
	{
		m_EnemiesPtr[idx]->SetVolume(Volume);
	}
}

std::vector<Rectf> EnemyManager::GetEnemyHitBoxes()
{
	std::vector<Rectf> temp{};
	for (int idx{ 0 }; idx < m_EnemiesPtr.size(); ++idx)
	{
		temp.push_back(m_EnemiesPtr[idx]->GetEnemyHitBox());
	}
	return temp;
}

void EnemyManager::PushEnemies(BulletManager* bulletManager, Player* player)
{
	//SPIKY
	m_EnemiesPtr.push_back(new Spiky{ Vector2f{2000, 430 }, bulletManager, player });

	//GUNVOLT
	m_EnemiesPtr.push_back(new GunVolt{ Vector2f{3000, 432}, bulletManager, player });
	m_EnemiesPtr.push_back(new GunVolt{ Vector2f{8510, 495}, bulletManager, player });
	m_EnemiesPtr.push_back(new GunVolt{ Vector2f{9670, 495}, bulletManager, player });
	
	//CRUSHER
	//Section 1
	for (int idx{ 0 }; idx <= 6; ++idx)
	{
		Vector2f spawnPos{ 4300 + static_cast<float>(rand() % 1600), 750 + static_cast<float>(rand() % 50) };
		m_EnemiesPtr.push_back(new Crusher{ spawnPos, bulletManager, player });
	}
	//Section 2
	for (int idx{ 0 }; idx <= 6; ++idx)
	{
		Vector2f spawnPos{ 7000 + static_cast<float>(rand() % 3000), 650 + static_cast<float>(rand() % 70) };
		m_EnemiesPtr.push_back(new Crusher{ spawnPos, bulletManager, player });
	}

	//BALLDEVOUX
	m_EnemiesPtr.push_back(new BallDeVoux{ Vector2f{13700,366},bulletManager, player });
	m_EnemiesPtr.push_back(new BallDeVoux{ Vector2f{14080,366},bulletManager, player });

	//BEEBLADER
	m_EnemiesPtr.push_back(new BeeBlader{ Vector2f{12400, 700}, 200.f,bulletManager, player, this });
	m_EnemiesPtr.push_back(new BeeBlader{ Vector2f{15000, 500}, 367.f,bulletManager, player, this });
}