#pragma once
#include "Texture.h"
#include <vector>
#include "Enemy.h"
#include "Fly.h"

class Room
{
public:

	Room(const Point2f& Pos, const bool& Up, const bool& Right, const bool& Down, const bool& Left, const bool& Enemies);
	virtual ~Room();
	virtual void Draw();
	virtual void Update(float elapsedSec, Rectf playerHitBox, std::vector<Bullet*> bulletvctr);
	std::vector <Rectf> GetHorizontalRect() const;
	std::vector <Rectf> GetVerticalRect() const;
	virtual std::vector <Enemy*> GetEnemyVctr() const;

	Room(const Room& other) = delete;
	Room& operator=(const Room& rhs) = delete;
	Room(Room&& rhs) = delete;
	Room& operator=(Room&& rhs) = delete;

protected:
	std::vector <Rectf> m_HorizontalRectVctr;
	std::vector <Rectf> m_VerticalRectVctr;

	std::vector <Enemy*> m_EnemyVctr;

	Point2f m_RoomPos;
	bool m_Up;
	bool m_Right;
	bool m_Down;
	bool m_Left;

	float m_RoomHeight;
	float m_RoomWidth;
	float m_DoorHeight;
	float m_DoorWidth;

private:
	
	void PushVectors(const Point2f& Pos, const bool& Up, const bool& Right, const bool& Down, const bool& Left);
	Point2f GetEnemySpawn() const;

	Texture* m_BaseRoomTexture;
	Texture* m_BaseDoorTexture;

	bool m_EnemyAlive{ false };
	bool m_DoorsClosed{ false };
	bool m_DoorsOpen{ false };
	bool m_DoorsPopped{ false };
};

