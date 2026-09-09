#include "pch.h"
#include "Room.h"

Room::Room(const Point2f& Pos, const bool& Up, const bool& Right, const bool& Down, const bool& Left, const bool& Enemies)
	:m_RoomPos{Pos}
	,m_Up{Up}
	,m_Right{Right}
	,m_Down{Down}
	,m_Left{Left}
{
	m_BaseRoomTexture = new Texture{ "Room.png" };
	m_BaseDoorTexture = new Texture{ "Door.png" };

	m_RoomHeight = m_BaseRoomTexture->GetHeight();
	m_RoomWidth = m_BaseRoomTexture->GetWidth();
	m_DoorHeight = m_BaseDoorTexture->GetHeight();
	m_DoorWidth = m_BaseDoorTexture->GetWidth();

	PushVectors(Pos, Up, Right, Down, Left);

	if(Enemies)
	{
		int m_EnemyAmount{ rand() % 3 };
		for (int idx{}; idx < m_EnemyAmount; ++idx)
		{
			m_EnemyVctr.push_back(new Fly{ GetEnemySpawn() });

			m_EnemyAlive = true;
		}
	}
}

Room::~Room()
{
	delete m_BaseDoorTexture;
	m_BaseDoorTexture = nullptr;

	delete m_BaseRoomTexture;
	m_BaseRoomTexture = nullptr;
	
	for (int idx{}; idx < m_EnemyVctr.size(); ++idx)
	{
		delete m_EnemyVctr[idx];
		m_EnemyVctr[idx] = nullptr;
	}
}

void Room::Draw()
{
	m_BaseRoomTexture->Draw(m_RoomPos);
	if (m_Left)
	{
		int offSetX{ 10 };
		int offSetY{ 5 };
		glPushMatrix();
		glTranslatef((m_RoomPos.x) + (m_DoorHeight + offSetX), ((m_RoomPos.y + m_RoomWidth / 4) + offSetY), 0);
		glRotatef(90, 0, 0, 1);

		if (m_DoorsOpen)
		{
			m_BaseDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * 0) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
		}
		else
		{
			m_BaseDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * m_DoorsClosed) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
		}

		glPopMatrix();
	}
	if (m_Right)
	{
		int offSetX{ 10 };
		int offSetY{ 30 };
		glPushMatrix();
		glTranslatef((m_RoomPos.x + m_RoomWidth) - (m_DoorHeight + offSetX), ((m_RoomPos.y + m_RoomWidth / 3) + offSetY), 0);
		glRotatef(-90, 0, 0, 1);

		if (m_DoorsOpen)
		{
			m_BaseDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * 0) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
		}
		else
		{
			m_BaseDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * m_DoorsClosed) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
		}

		glPopMatrix();
	}
	if (m_Down)
	{
		int offSet{ 15 };
		glPushMatrix();
		glTranslatef((m_RoomPos.x + m_RoomWidth / 2) + (m_DoorWidth / 4), m_RoomPos.y + m_DoorHeight + offSet, 0);
		glRotatef(180, 0, 0, 1);

		if (m_DoorsOpen)
		{
			m_BaseDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * 0) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
		}
		else
		{
			m_BaseDoorTexture->Draw(Point2f{ 0,0 }, Rectf{ (m_DoorWidth * m_DoorsClosed) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
		}

		glPopMatrix();
	}
	if (m_Up)
	{
		int offset{ 11 };

		
		if (m_DoorsOpen)
		{
			m_BaseDoorTexture->Draw(Point2f{ ((m_RoomPos.x + m_RoomWidth / 2) - (m_DoorWidth / 4)),
			(m_RoomPos.y + m_RoomHeight) - (m_DoorHeight + offset) },
				Rectf{ (m_DoorWidth * 0) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
		}
		else
		{
			m_BaseDoorTexture->Draw(Point2f{ ((m_RoomPos.x + m_RoomWidth / 2) - (m_DoorWidth / 4)),
			(m_RoomPos.y + m_RoomHeight) - (m_DoorHeight + offset) },
				Rectf{ (m_DoorWidth * m_DoorsClosed) / 2, 0, m_DoorWidth / 2, m_DoorHeight });
		}
	}

	for (int idx{}; idx < m_EnemyVctr.size(); ++idx)
	{
		if (m_EnemyVctr[idx]->GetHealth() > 0)
		{
			m_EnemyVctr[idx]->Draw();
		}
	}
}

void Room::Update(float elapsedSec, Rectf playerHitBox, std::vector<Bullet*> bulletvctr)
{
	if(utils::IsPointInRect(Point2f{ playerHitBox.left + 5, playerHitBox.bottom + 5},Rectf{ m_RoomPos.x + (m_RoomWidth / 9), m_RoomPos.y + (m_RoomHeight / 6), m_RoomWidth - (m_RoomWidth / 4.5f), m_RoomHeight - (m_RoomHeight / 3) }))
	{

		if (m_EnemyAlive && !m_DoorsClosed)
		{
			m_HorizontalRectVctr.push_back(Rectf{ m_RoomPos.x, m_RoomPos.y, m_RoomWidth, m_RoomHeight / 6 });
			m_HorizontalRectVctr.push_back(Rectf{ m_RoomPos.x, m_RoomPos.y + m_RoomHeight - (m_RoomHeight / 6), m_RoomWidth, m_RoomHeight / 6 });
			m_VerticalRectVctr.push_back(Rectf{ m_RoomPos.x, m_RoomPos.y, m_RoomWidth / 9, m_RoomHeight });
			m_VerticalRectVctr.push_back(Rectf{ m_RoomPos.x + m_RoomWidth - (m_RoomWidth / 9) , m_RoomPos.y, m_RoomWidth / 9, m_RoomHeight });

			m_DoorsClosed = true;
		}
		if (!m_EnemyAlive && !m_DoorsPopped)
		{
			m_HorizontalRectVctr.pop_back();
			m_HorizontalRectVctr.pop_back();
			m_VerticalRectVctr.pop_back();
			m_VerticalRectVctr.pop_back();
			m_DoorsPopped = true;
			m_DoorsOpen = true;
		}
	}

	for (int idx{}; idx < m_EnemyVctr.size(); ++idx)
	{
		if (m_EnemyVctr[idx]->GetHealth() > 0)
		{
			m_EnemyVctr[idx]->Update(elapsedSec, m_HorizontalRectVctr, m_VerticalRectVctr, playerHitBox, bulletvctr);
		}
	}

	for (int idx{}; idx < m_EnemyVctr.size(); ++idx)
	{
		if (m_EnemyVctr[idx]->GetHealth() > 0)
		return;

		m_EnemyAlive = false;
	}
}

void Room::PushVectors(const Point2f& Pos, const bool& Up, const bool& Right, const bool& Down, const bool& Left)
{
	// Bottom
	if (Down)
	{
		m_HorizontalRectVctr.push_back(Rectf{ Pos.x, Pos.y, (m_RoomWidth / 2) - (m_DoorWidth / 6), m_RoomHeight / 6 });
		m_HorizontalRectVctr.push_back(Rectf{ Pos.x + (m_RoomWidth / 2) + (m_DoorWidth / 6), Pos.y, (m_RoomWidth / 2) - (m_DoorWidth / 6), m_RoomHeight / 6 });
	}
	else
	{
		m_HorizontalRectVctr.push_back(Rectf{ Pos.x, Pos.y, m_RoomWidth, m_RoomHeight / 6 });
	}
	// Top
	if (Up)
	{
		m_HorizontalRectVctr.push_back(Rectf{ Pos.x, Pos.y + m_RoomHeight - (m_RoomHeight / 6), (m_RoomWidth / 2) - (m_DoorWidth / 6), m_RoomHeight / 6 });
		m_HorizontalRectVctr.push_back(Rectf{ Pos.x + (m_RoomWidth / 2) + (m_DoorWidth / 6), Pos.y + m_RoomHeight - (m_RoomHeight / 6), (m_RoomWidth / 2) - (m_DoorWidth / 6), m_RoomHeight / 6 });
	}
	else
	{
		m_HorizontalRectVctr.push_back(Rectf{ Pos.x, Pos.y + m_RoomHeight - (m_RoomHeight / 6), m_RoomWidth, m_RoomHeight / 6 });
	}
	//Left
	if (Left)
	{
		m_VerticalRectVctr.push_back(Rectf{ Pos.x, Pos.y, m_RoomWidth / 9, (m_RoomHeight / 2) - (m_DoorWidth / 6) });
		m_VerticalRectVctr.push_back(Rectf{ Pos.x, Pos.y + (m_RoomHeight / 2) + (m_DoorWidth / 6), m_RoomWidth / 9, (m_RoomHeight / 2) - (m_DoorWidth / 6) });
	}
	else
	{
		m_VerticalRectVctr.push_back(Rectf{ Pos.x, Pos.y, m_RoomWidth / 9, m_RoomHeight });
	}
	//Right
	if (Right)
	{
		m_VerticalRectVctr.push_back(Rectf{ Pos.x + m_RoomWidth - (m_RoomWidth / 9), Pos.y, m_RoomWidth / 9, (m_RoomHeight / 2) - (m_DoorWidth / 6) });
		m_VerticalRectVctr.push_back(Rectf{ Pos.x + m_RoomWidth - (m_RoomWidth / 9), Pos.y + (m_RoomHeight / 2) + (m_DoorWidth / 6), m_RoomWidth / 9, (m_RoomHeight / 2) - (m_DoorWidth / 6) });
	}
	else
	{
		m_VerticalRectVctr.push_back(Rectf{ Pos.x + m_RoomWidth - (m_RoomWidth / 9) , Pos.y, m_RoomWidth / 9, m_RoomHeight });
	}
}

Point2f Room::GetEnemySpawn() const
{
	Rectf spawnBox{ m_RoomPos.x + (m_RoomWidth / 9), m_RoomPos.y + (m_RoomHeight / 6), m_RoomWidth - (m_RoomWidth / 4.5f), m_RoomHeight - (m_RoomHeight / 3) };

	Point2f spawnPos
	{ 
		m_RoomPos.x + (m_RoomWidth / 9) + rand() % int(m_RoomWidth - (m_RoomWidth / 4.5f))
		,m_RoomPos.y + (m_RoomHeight / 6) + rand() % int(m_RoomHeight - (m_RoomHeight / 3))
	};


	if (utils::IsPointInRect(spawnPos, spawnBox))
	{
		return spawnPos;
	}
	else
	{
		GetEnemySpawn();
	}
}

std::vector<Rectf> Room::GetHorizontalRect() const
{
	return m_HorizontalRectVctr;
}

std::vector<Rectf> Room::GetVerticalRect() const
{
	return m_VerticalRectVctr;
}

std::vector<Enemy*> Room::GetEnemyVctr() const
{
	return m_EnemyVctr;
}