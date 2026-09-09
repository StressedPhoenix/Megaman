#pragma once
#include "Texture.h"
#include <iostream>
#include "SoundEffect.h"
class Bullet
{
public:
	Bullet(Point2f startpos, bool left, bool right, bool up, bool down);
	~Bullet();

	void Draw() const;
	void Update(float elapsedSec);
	bool HitGround();
	Rectf GetBulletHitBox() const;

	void Hit();
	bool GetHit() const;

	Bullet(const Bullet& other) = delete;
	Bullet& operator=(const Bullet& rhs) = delete;
	Bullet(Bullet&& rhs) = delete;
	Bullet& operator=(Bullet&& rhs) = delete;
private:
	// functions

	// enum classes
	enum class BulletDirection
	{
		Up,
		Down,
		Left,
		Right
	};

	// datamembers
	const int m_BulletSpeed{ 150 };
	float m_BulletDistance{ 0.f };
	float m_MaxDistance{ 200 };
	float m_Gravity{ 0 };
	const float bulletScale{ 14 };
	SoundEffect* m_BulletSound;
	BulletDirection m_BulletDirection;
	Texture* m_BulletTexturePtr;
	Point2f m_BulletPosition;
	bool m_Hit{ false };
};

