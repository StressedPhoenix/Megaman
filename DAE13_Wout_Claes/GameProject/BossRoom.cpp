#include "pch.h"
#include "BossRoom.h"

BossRoom::BossRoom(const Point2f& Pos, const bool& Up, const bool& Right, const bool& Down, const bool& Left, const bool& Enemies)
	:Room(Pos, Up, Right, Down, Left, Enemies)
{
	m_BossRoomTexture = new Texture{ "Boss_Room.png" };
	m_BossInDoorTexture = new Texture{ "Inside_Boss_Door.png" };
	m_BossOutDoorTexture = new Texture{ "Boss_Door.png" };
}

BossRoom::~BossRoom()
{
	delete m_BossOutDoorTexture;
	m_BossOutDoorTexture = nullptr;

	delete m_BossInDoorTexture;
	m_BossInDoorTexture = nullptr;

	delete m_BossRoomTexture;
	m_BossRoomTexture = nullptr;
}

void BossRoom::Draw()
{
	bool enemyAlive{ false };

	m_BossRoomTexture->Draw(m_RoomPos);
	if (m_Left)
	{
		int offSetX{ 10 };
		int offSetY{ 5 };
		glPushMatrix();
		glTranslatef((m_RoomPos.x) + (m_DoorHeight + offSetX), ((m_RoomPos.y + m_RoomWidth / 4) + offSetY), 0);
		glRotatef(90, 0, 0, 1);

		m_BossInDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * enemyAlive) / 2, 0, m_DoorWidth / 2, m_DoorHeight });

		glPopMatrix();
	}
	if (m_Right)
	{
		int offSetX{ 10 };
		int offSetY{ 30 };
		glPushMatrix();
		glTranslatef((m_RoomPos.x + m_RoomWidth) - (m_DoorHeight + offSetX), ((m_RoomPos.y + m_RoomWidth / 3) + offSetY), 0);
		glRotatef(-90, 0, 0, 1);

		m_BossInDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * enemyAlive) / 2, 0, m_DoorWidth / 2, m_DoorHeight });

		glPopMatrix();
	}
	if (m_Down)
	{
		int offSet{ 15 };
		glPushMatrix();
		glTranslatef((m_RoomPos.x + m_RoomWidth / 2) + (m_DoorWidth / 4), m_RoomPos.y + m_DoorHeight + offSet, 0);
		glRotatef(180, 0, 0, 1);

		m_BossInDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * enemyAlive) / 2, 0, m_DoorWidth / 2, m_DoorHeight });

		glPopMatrix();
	}
	if (m_Up)
	{
		int offset{ 11 };

		m_BossInDoorTexture->Draw(Point2f{ ((m_RoomPos.x + m_RoomWidth / 2) - (m_DoorWidth / 4)),
			(m_RoomPos.y + m_RoomHeight) - (m_DoorHeight + offset) },
			Rectf{ (m_DoorWidth * enemyAlive) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
	}
}

void BossRoom::Update(float elapsedSec)
{
}
