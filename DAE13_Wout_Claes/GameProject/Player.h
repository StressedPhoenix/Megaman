#pragma once
#include "Texture.h"
#include <vector>
#include "utils.h"
#include "Enemy.h"
#include "SoundEffect.h"
#include "PickUp.h"
#include "InnerEye.h"
class Bullet;

class Player
{
public:
	
	Player(Point2f startPos);
	~Player();
	void Draw(std::vector<PickUp*> items) const;
	void Update(float elapsedSec, std::vector<Rectf> Horizontal, std::vector <Rectf> Vertical, std::vector<PickUp*> items, std::vector <Enemy*> enemies);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	Point2f GetPlayerPos();
	Rectf GetPlayerHitbox() const;
	int GetPlayerHealth() const;
	std::vector<Bullet*> GetBulletPtrVctr() const;

	Player(const Player& other) = delete;
	Player& operator=(const Player& rhs) = delete;
	Player(Player&& rhs) = delete;
	Player& operator=(Player&& rhs) = delete;
private:
	// functions
	void DrawHead(std::vector<PickUp*> items) const;
	void DrawBody() const;
	bool HitWallUp(std::vector<Rectf> Horizontal);
	bool HitWallDown(std::vector<Rectf> Horizontal);
	bool HitWallLeft(std::vector<Rectf> Vertical);
	bool HitWallRight(std::vector<Rectf> Vertical);

	// enum classes
	enum class HeadRotation
	{
		down,
		left,
		right,
		up
	};
	enum class MovementDirection
	{
		Still,
		Up,
		Down,
		Left,
		Right,
	};
	
	// datamembers
	Point2f m_IsaacPos;
	Texture* m_IsaacHeadSpritePtr;
	Texture* m_IsaacBodySpritePtr;
	Texture* m_IsaacHeadInnerEyeSpritePtr;
	int m_CurrentFrame{ 0 };
	HeadRotation m_HeadRotation;
	MovementDirection m_MovementDirection;
	float m_HeadResetCounter{ 1 };
	const int m_MovementSpeed{ 100 };
	float m_FrameCounter{ 0 };
	std::vector <Bullet*> m_BulletPtrVctr;
	int m_BulletsDeleted{ 0 };
	float m_BulletDelay{ 0 };
	int m_Health{ 6 };
};

