#pragma once
#include "Texture.h"
#include "utils.h"
#include <iostream>
#include "UI.h"
#include "Room.h"
#include "StartRoom.h"
#include "BossRoom.h"
#include "RewardRoom.h"

class Map
{
public:
	Map();
	~Map();

	void Draw() const;
	void update(const Point2f& PlayerPos, float elapsedSec, Rectf playerHitBox, std::vector<Bullet*> bulletvctr);
	Point2f SpawnLocation();
	Point2f GetRoom(const Point2f& PlayerPos) const;
	Point2f GetRoomArray(const Point2f& PlayerPos) const;
	Point2f GetMiddelRewardRoom() const;
	std::vector <Rectf> GetHorizontalRect(const Point2f& PlayerPos) const;
	std::vector <Rectf> GetVerticalRect(const Point2f& PlayerPos) const;
	std::vector <Enemy*> GetEnemyVctr(const Point2f& PlayerPos) const;
	
	friend void UI::Draw(const Map* map, const int& playerHealth) const;

	Map(const Map& other) = delete;
	Map& operator=(const Map& rhs) = delete;
	Map(Map&& rhs) = delete;
	Map& operator=(Map&& rhs) = delete;

private:
	void Preload();
	
	void GenerateRooms();
	void AssignBossRoom();
	void AssignRewardRoom();
	void AssignRoomObj();

	bool AdjecentUp(int Row, int Column);
	bool AdjecentRight(int Row, int Column);
	bool AdjecentDown(int Row, int Column);
	bool AdjecentLeft(int Row, int Column);
	void AdjacentRooms(const int& Row, const int& Column);
	void CanReachStartroom(const int& Row, const int& Column);

	enum class RoomType
	{
		Empty,
		Spawn,
		Normal,
		Reward,
		Boss
	};

	enum class EnemyPresence
	{
		Unaware,
		Hostile,
		Dead
	};

	struct RoomStr
	{
		RoomType m_RoomType{ RoomType::Empty };
		EnemyPresence m_EnemyPresence{EnemyPresence::Unaware};

		bool m_Up{ false };
		bool m_Right{ false };
		bool m_Down{ false };
		bool m_Left{ false };
		bool m_OneSideRoom{ false };
		bool m_checked{ false };
		bool m_Discoverd{ false };
		bool m_CurrentRoom{ false };

		Room* m_RoomObj;
	};

	static const int m_ROWS{ 9 };
	static const int m_COLUMNS{ 9 };
	RoomStr m_RoomArray[m_ROWS][m_COLUMNS];
	std::vector <Rectf> m_HorizontalRectVctr;
	std::vector <Rectf> m_VerticalRectVctr;

	float m_RoomWidth;
	float m_RoomHeight;
	float m_DoorHeight;
	float m_DoorWidth;
};