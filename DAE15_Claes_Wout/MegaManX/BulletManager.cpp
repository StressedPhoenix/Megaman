#include "pch.h"
#include "BulletManager.h"
#include "Bullet.h"
#include "GunVoltMissile.h"
#include "GunVoltGroundBullet.h"
#include "Player.h"
#include "EnemyManager.h"
#include "BeeBladerBullet.h"
#include "BeeBladerMissile.h"

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
	for (int idx{ 0 }; idx < m_BulletsPtr.size(); ++idx)
	{
		delete m_BulletsPtr[idx];
		m_BulletsPtr[idx] = nullptr;
	}
	m_BulletsPtr.clear();
}

void BulletManager::SetPlayerPtr(Player* player)
{
	m_PlayerPtr = player;
}

void BulletManager::SetEnemyManagerPtr(EnemyManager* enemyManager)
{
	m_EnemyManagerPtr = enemyManager;
}

void BulletManager::Update(float elapsedSec, const std::vector<Rectf>& EnemyHitBoxes, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	for (int idx{ 0 }; idx < m_BulletsPtr.size(); ++idx)
	{
		Bullet* temp{ m_BulletsPtr[idx] };
		if(m_BulletIDs[idx] == BulletID::XBullet)
		{
			Rectf placeholder{ 0,0,0,0 };
			temp->Update(elapsedSec, EnemyHitBoxes, MapHitBoxes, placeholder);
			if (temp->GetEnemyHit())
			{
				m_EnemyManagerPtr->Hit(temp->GetHitEnemy(), temp->GetDamage());
			}
		}
		else
		{
			std::vector<Rectf> placeholder;
			placeholder.push_back(Rectf{ 0,0,0,0 });
			temp->Update(elapsedSec, placeholder, MapHitBoxes, m_PlayerPtr->GetPlayerHitBox());
			if (temp->GetPlayerHit())
			{
				m_PlayerPtr->PlayerHit(temp->GetDamage());
			}
		}
	}
}

void BulletManager::Draw() const
{
	for (int idx{ 0 }; idx < m_BulletsPtr.size(); ++idx)
	{
		m_BulletsPtr[idx]->Draw();
	}
}

void BulletManager::Shoot(const Vector2f& startPos, bool rightDirection, const BulletID shooterID, const XBullet::ChargeLevel chargeLevel)
{
	Bullet* temp;
	switch (shooterID)
	{
	case BulletID::XBullet:
		temp = new XBullet{ startPos, rightDirection, chargeLevel };
		break;
	case BulletID::GunVoltBullet:
		temp = new GunVoltGroundBullet{ startPos, rightDirection };
		break;
	case BulletID::GunVoltMissile:
		temp = new GunVoltMissile(startPos, rightDirection);
		break;
	case BulletID::BeeBladerBullet:
		temp = new BeeBladerBullet(startPos, rightDirection);
		break;
	case BulletID::BeeBladerMissile:
		temp = new BeeBladerMissile(startPos, rightDirection);
	}

	m_BulletsPtr.push_back(temp);
	m_BulletIDs.push_back(shooterID);
}

std::vector<Rectf> BulletManager::GetBulletHitBoxes() const
{
	std::vector<Rectf> result;
	for (int idx{ 0 }; idx < m_BulletsPtr.size(); ++idx)
	{
		result.push_back(m_BulletsPtr[idx]->GetBulletHitBox());
	}

	return result;
}

void BulletManager::SetVolume(const int Volume)
{
	for (int idx{ 0 }; idx < m_BulletsPtr.size(); ++idx)
	{
		m_BulletsPtr[idx]->SetVolume(Volume);
	}
}
