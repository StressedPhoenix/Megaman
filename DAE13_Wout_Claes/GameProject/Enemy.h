#pragma once
#include <vector>
#include "Bullet.h"
class Enemy
{
public:

	virtual void Draw() const = 0;
	virtual void Update(float elapsedsec, std::vector<Rectf> Horizontal, std::vector <Rectf> Vertical, Rectf playerHitBox, std::vector<Bullet*> bulletvctr) = 0;
	virtual int GetHealth() const = 0;
	virtual Rectf GetHitboxes() const = 0;

protected:
	
	Rectf m_Hitboxes;
};

