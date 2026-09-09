#pragma once
#include "Enemy.h"
#include "Texture.h"
#include "utils.h"
class Fly : public Enemy
{
public:

	Fly(Point2f Position);
	~Fly();
	virtual void Draw() const override;
	virtual void Update(float elapsedsec, std::vector<Rectf> Horizontal, std::vector <Rectf> Vertical, Rectf playerHitBox, std::vector<Bullet*> bulletvctr) override;
	virtual int GetHealth() const override;
	virtual Rectf GetHitboxes() const override;

	Fly(const Fly& other) = delete;
	Fly& operator=(const Fly& rhs) = delete;
	Fly(Fly&& rhs) = delete;
	Fly& operator=(Fly&& rhs) = delete;


private:
	Texture* m_FlyTexturePtr;
	Point2f m_Position;
	Point2f m_TargetPosition;
	int m_Health{ 3 };
	int m_SpriteTimer{ 0 };
	int m_Speed{ 50 };

	bool m_GotHit{false};
	int m_InvTimer{ 0 };
};

