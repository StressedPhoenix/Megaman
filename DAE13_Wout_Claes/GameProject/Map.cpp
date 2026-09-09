#include "pch.h"
#include "Map.h"

Map::Map()
{
	Preload();
	GenerateRooms();
	AssignRoomObj();
}

Map::~Map()
{
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			RoomStr Roomarray{ m_RoomArray[rowIndex][columnIndex] };
			if (Roomarray.m_RoomType != RoomType::Empty)
			{
				delete Roomarray.m_RoomObj;
				Roomarray.m_RoomObj = nullptr;
			}
		}
	}
}

void Map::Draw() const
{
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			RoomStr roomArray{ m_RoomArray[rowIndex][columnIndex] };

			if (roomArray.m_RoomType != RoomType::Empty)
			{
				roomArray.m_RoomObj->Draw();
			}
		}
	}
}

void Map::update(const Point2f& PlayerPos, float elapsedSec, Rectf playerHitBox, std::vector<Bullet*> bulletvctr)
{
	Point2f roomArrayPoint{ GetRoomArray(PlayerPos).x, GetRoomArray(PlayerPos).y };
	RoomStr roomArray{ m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y] };
	
	//update minimap
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			m_RoomArray[rowIndex][columnIndex].m_CurrentRoom = false;
		}
	}
	if (m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y].m_RoomType != RoomType::Empty)
	{
		m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y].m_Discoverd = true;
		m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y].m_CurrentRoom = true;
	}
	if (m_RoomArray[(int)roomArrayPoint.x + 1][(int)roomArrayPoint.y].m_RoomType != RoomType::Empty)
	{
		m_RoomArray[(int)roomArrayPoint.x + 1][(int)roomArrayPoint.y].m_Discoverd = true;
	}
	if (m_RoomArray[(int)roomArrayPoint.x - 1][(int)roomArrayPoint.y].m_RoomType != RoomType::Empty)
	{
		m_RoomArray[(int)roomArrayPoint.x - 1][(int)roomArrayPoint.y].m_Discoverd = true;
	}
	if (m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y + 1].m_RoomType != RoomType::Empty)
	{
		m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y + 1].m_Discoverd = true;
	}
	if (m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y - 1].m_RoomType != RoomType::Empty)
	{
		m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y - 1].m_Discoverd = true;
	}

	roomArray.m_RoomObj->Update(elapsedSec, playerHitBox, bulletvctr);
}

Point2f Map::SpawnLocation()
{
	Point2f Spawn{(m_RoomWidth * 4) + (m_RoomWidth / 2), (m_RoomHeight * 4) + (m_RoomHeight / 2)};
	return Spawn;
}

Point2f Map::GetRoom(const Point2f& PlayerPos) const
{
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			const float xPos{ columnIndex * m_RoomWidth };
			const float yPos{ rowIndex * m_RoomHeight };
			Rectf roomRect{ xPos, yPos, m_RoomWidth, m_RoomHeight };

			if (utils::IsPointInRect(PlayerPos, roomRect))
			{
				return Point2f{xPos + (m_RoomWidth / 2) , yPos + (m_RoomHeight / 2) };
			}
		}
	}
	
}

std::vector <Rectf> Map::GetHorizontalRect(const Point2f& PlayerPos) const
{
	RoomStr Roomarray{ m_RoomArray[(int)GetRoomArray(PlayerPos).x][(int)GetRoomArray(PlayerPos).y] };
	
	return Roomarray.m_RoomObj->GetHorizontalRect();
}

std::vector <Rectf> Map::GetVerticalRect(const Point2f& PlayerPos) const
{
	RoomStr Roomarray{ m_RoomArray[(int)GetRoomArray(PlayerPos).x][(int)GetRoomArray(PlayerPos).y] };

	return Roomarray.m_RoomObj->GetVerticalRect();
}

std::vector<Enemy*> Map::GetEnemyVctr(const Point2f& PlayerPos) const
{
	Point2f roomArrayPoint{ GetRoomArray(PlayerPos).x, GetRoomArray(PlayerPos).y };
	RoomStr roomArray{ m_RoomArray[(int)roomArrayPoint.x][(int)roomArrayPoint.y] };

	if (roomArray.m_RoomType == RoomType::Normal)
	{
		return roomArray.m_RoomObj->GetEnemyVctr();
	}
}

Point2f Map::GetRoomArray(const Point2f& PlayerPos) const
{
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			const float xPos{ columnIndex * m_RoomWidth };
			const float yPos{ rowIndex * m_RoomHeight };
			Rectf roomRect{ xPos, yPos, m_RoomWidth, m_RoomHeight };

			if (utils::IsPointInRect(PlayerPos, roomRect))
			{
				return Point2f{ (float)rowIndex, (float)columnIndex };
			}
		}
	}
}

Point2f Map::GetMiddelRewardRoom() const
{
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			const float xPos{ columnIndex * m_RoomWidth };
			const float yPos{ rowIndex * m_RoomHeight };
			if (m_RoomArray[rowIndex][columnIndex].m_RoomType == RoomType::Reward)
			{
				return Point2f{xPos + (m_RoomWidth / 2), yPos + (m_RoomHeight / 2)};
			}
		}
	}
}

void Map::Preload()
{
	Texture* m_BaseRoomTexture = new Texture{ "Room.png" };
	m_RoomWidth = m_BaseRoomTexture->GetWidth();
	m_RoomHeight = m_BaseRoomTexture->GetHeight();
	delete m_BaseRoomTexture;
	m_BaseRoomTexture = nullptr;

	Texture* m_DoorTexture = new Texture{ "Door.png" };
	m_DoorWidth = m_DoorTexture->GetWidth();
	m_DoorHeight = m_DoorTexture->GetHeight();
	delete m_DoorTexture;
	m_DoorTexture = nullptr;

}

#pragma region CreateArray
#pragma region Assign
void Map::GenerateRooms()
{
	static const int maxRooms{ 15 };
	static const int minRooms{ 7 };

	const int roomAmount{ minRooms + (rand() % (maxRooms - minRooms)) };
	std::cout << roomAmount << std::endl;

	//Re-initialize in case of recall function
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			RoomStr& Roomarray{ m_RoomArray[rowIndex][columnIndex] };

			Roomarray.m_RoomType = RoomType::Empty;
			Roomarray.m_Up = false;
			Roomarray.m_Right = false;
			Roomarray.m_Down = false;
			Roomarray.m_Left = false;
			Roomarray.m_checked = false;
			Roomarray.m_OneSideRoom = false;
		}
	}

	// SpawnRoom (Never changes)
	m_RoomArray[m_ROWS / 2][m_COLUMNS / 2].m_RoomType = RoomType::Spawn;

	for (int index{ 0 }; index < roomAmount; ++index)
	{
		int rowPlaceHolder{ 5 };
		int columnPlaceHolder{ 5 };
		int randRows{ (rand() % rowPlaceHolder) + (m_ROWS / 4) };
		int randColumns{ (rand() % columnPlaceHolder) + (m_COLUMNS / 4) };

		RoomStr& Roomarray { m_RoomArray[randRows][randColumns] };

		if (Roomarray.m_RoomType == RoomType::Empty)
		{
			Roomarray.m_RoomType = RoomType::Normal;
		}
		else
		{
			--index;
		}
	}

	//set all the values for the rooms
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			if (m_RoomArray[rowIndex][columnIndex].m_RoomType != RoomType::Empty)
			{
				AdjacentRooms(rowIndex, columnIndex);
			}
		}
	}
	CanReachStartroom(m_ROWS / 2, m_COLUMNS / 2);

	AssignBossRoom();
	AssignRewardRoom();

	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			if (m_RoomArray[rowIndex][columnIndex].m_RoomType != RoomType::Empty)
			{
				if (!m_RoomArray[rowIndex][columnIndex].m_checked)
				{
					GenerateRooms();
				}
			}
		}
	}
}

void Map::AssignBossRoom()
{
	std::vector<Point2f> posibleRooms{};

	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			RoomStr& Roomarray{ m_RoomArray[rowIndex][columnIndex] };
			if (Roomarray.m_RoomType == RoomType::Normal && Roomarray.m_OneSideRoom)
			{
				posibleRooms.push_back(Point2f{float(rowIndex), float(columnIndex)});
			}
		}
	}
	if (posibleRooms.size() > 0)
	{
		Point2f chosenRoom{ posibleRooms[rand() % posibleRooms.size()] };
		m_RoomArray[int(chosenRoom.x)][int(chosenRoom.y)].m_RoomType = RoomType::Boss;
	}
	else
	{
		AssignBossRoom();
	}
}

void Map::AssignRewardRoom()
{
	std::vector<Point2f> posibleRooms{};

	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			RoomStr& Roomarray{ m_RoomArray[rowIndex][columnIndex] };
			if (Roomarray.m_RoomType == RoomType::Normal)
			{
				posibleRooms.push_back(Point2f{ float(rowIndex), float(columnIndex) });
			}
		}
	}
	if (posibleRooms.size() > 0)
	{
		Point2f chosenRoom{ posibleRooms[rand() % posibleRooms.size()] };
		m_RoomArray[int(chosenRoom.x)][int(chosenRoom.y)].m_RoomType = RoomType::Reward;
	}
	else
	{
		AssignRewardRoom();
	}
}

void Map::AssignRoomObj()
{
	for (int rowIndex{}; rowIndex < m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex < m_COLUMNS; ++columnIndex)
		{
			RoomStr& Roomarray{ m_RoomArray[rowIndex][columnIndex] };
			const float xPos{ columnIndex * m_RoomWidth };
			const float yPos{ rowIndex * m_RoomHeight };
			Point2f RoomPos{ xPos, yPos };

			if (Roomarray.m_RoomType == RoomType::Normal)
			{
				Roomarray.m_RoomObj = new Room{ RoomPos, Roomarray.m_Up, Roomarray.m_Right, Roomarray.m_Down, Roomarray.m_Left, true };
			}
			if (Roomarray.m_RoomType == RoomType::Spawn)
			{
				Roomarray.m_RoomObj = new StartRoom{ RoomPos, Roomarray.m_Up, Roomarray.m_Right, Roomarray.m_Down, Roomarray.m_Left, false };
			}
			if (Roomarray.m_RoomType == RoomType::Boss)
			{
				Roomarray.m_RoomObj = new BossRoom{ RoomPos, Roomarray.m_Up, Roomarray.m_Right, Roomarray.m_Down, Roomarray.m_Left, false };
			}
			if (Roomarray.m_RoomType == RoomType::Reward)
			{
				Roomarray.m_RoomObj = new RewardRoom{ RoomPos, Roomarray.m_Up, Roomarray.m_Right, Roomarray.m_Down, Roomarray.m_Left, false };
			}
		}
	}
}
#pragma endregion

#pragma region Checks
void Map::AdjacentRooms(const int& Row, const int& Column)
{
	RoomStr& Roomarray{ m_RoomArray[Row][Column] };

	Roomarray.m_Up = AdjecentUp(Row, Column);
	Roomarray.m_Right = AdjecentRight(Row, Column);
	Roomarray.m_Down = AdjecentDown(Row, Column);
	Roomarray.m_Left = AdjecentLeft(Row, Column);

	if (Roomarray.m_Up && !Roomarray.m_Right && !Roomarray.m_Down && !Roomarray.m_Left)
	{
		Roomarray.m_OneSideRoom = true;
		return;
	}

	if (Roomarray.m_Right && !Roomarray.m_Up && !Roomarray.m_Down && !Roomarray.m_Left)
	{
		Roomarray.m_OneSideRoom = true;
		return;
	}

	if (Roomarray.m_Down && !Roomarray.m_Up && !Roomarray.m_Right && !Roomarray.m_Left)
	{
		Roomarray.m_OneSideRoom = true;
		return;
	}

	if (Roomarray.m_Left && !Roomarray.m_Up && !Roomarray.m_Right && !Roomarray.m_Down)
	{
		Roomarray.m_OneSideRoom = true;
		return;
	}
}

bool Map::AdjecentUp(int Row, int Column)
{
	if (m_RoomArray[Row + 1][Column].m_RoomType == RoomType::Normal || m_RoomArray[Row + 1][Column].m_RoomType == RoomType::Spawn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::AdjecentRight(int Row, int Column)
{
	if (m_RoomArray[Row][Column + 1].m_RoomType == RoomType::Normal || m_RoomArray[Row][Column + 1].m_RoomType == RoomType::Spawn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::AdjecentDown(int Row, int Column)
{
	if (m_RoomArray[Row - 1][Column].m_RoomType == RoomType::Normal || m_RoomArray[Row - 1][Column].m_RoomType == RoomType::Spawn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Map::AdjecentLeft(int Row, int Column)
{
	if (m_RoomArray[Row][Column - 1].m_RoomType == RoomType::Normal || m_RoomArray[Row][Column - 1].m_RoomType == RoomType::Spawn)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Map::CanReachStartroom(const int& Row, const int& Column)
{
	RoomStr& Roomarray{ m_RoomArray[Row][Column] };

	Roomarray.m_checked = true;

	if (Roomarray.m_Up && !m_RoomArray[Row + 1][Column].m_checked)
	{
		CanReachStartroom(Row + 1, Column);
	}

	if (Roomarray.m_Right && !m_RoomArray[Row][Column + 1].m_checked)
	{
		CanReachStartroom(Row, Column + 1);
	}

	if (Roomarray.m_Down && !m_RoomArray[Row - 1][Column].m_checked)
	{
		CanReachStartroom(Row - 1, Column);
	}

	if (Roomarray.m_Left && !m_RoomArray[Row][Column - 1].m_checked)
	{
		CanReachStartroom(Row, Column - 1);
	}
}
#pragma endregion
#pragma endregion