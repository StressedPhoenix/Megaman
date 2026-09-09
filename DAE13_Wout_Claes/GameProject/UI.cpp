#include "pch.h"
#include "UI.h"
#include "Map.h"

UI::UI()
	:m_CellWidth{40}
	,m_CellHeight{10}
{
	m_HeartSprite = new Texture("UI_Hearts.png");
	m_Crown = new Texture("Reward_Map.png");
	m_Skull = new Texture("Boss_Map.png");
}

UI::~UI()
{
	delete m_Skull;
	m_Skull = nullptr;
	delete m_Crown;
	m_Crown = nullptr;
	delete m_HeartSprite;
	m_HeartSprite = nullptr;
}

void UI::Draw(const Map* map, const int& playerHealth) const
{
	
	// Draw the backkground rectangle
	utils::SetColor(Color4f{ 0.15f,0.1f,0.1f,1.f });
	utils::FillRect(0, map->m_RoomHeight, map->m_RoomWidth, map->m_RoomHeight / 3);
	// Draw the hearts
	if (playerHealth == 6)
	{
		m_HeartSprite->Draw(Point2f{ (map->m_RoomWidth - map->m_RoomWidth / 3) - 50, map->m_RoomHeight + map->m_RoomHeight / 10 },
		Rectf{ 0, (m_HeartSprite->GetHeight() / 6) * 6, m_HeartSprite->GetWidth(), m_HeartSprite->GetHeight() / 6 });
	}
	if (playerHealth == 5)
	{
		m_HeartSprite->Draw(Point2f{ (map->m_RoomWidth - map->m_RoomWidth / 3) - 50, map->m_RoomHeight + map->m_RoomHeight / 10 },
			Rectf{ 0, (m_HeartSprite->GetHeight() / 6) * 1, m_HeartSprite->GetWidth(), m_HeartSprite->GetHeight() / 6 });
	}
	if (playerHealth == 4)
	{
		m_HeartSprite->Draw(Point2f{ (map->m_RoomWidth - map->m_RoomWidth / 3) - 50, map->m_RoomHeight + map->m_RoomHeight / 10 },
			Rectf{ 0, ((m_HeartSprite->GetHeight() / 6) * 2) - 3, m_HeartSprite->GetWidth(), m_HeartSprite->GetHeight() / 6 });
	}
	if (playerHealth == 3)
	{
		m_HeartSprite->Draw(Point2f{ (map->m_RoomWidth - map->m_RoomWidth / 3) - 50, map->m_RoomHeight + map->m_RoomHeight / 10 },
			Rectf{ 0, ((m_HeartSprite->GetHeight() / 6) * 3) - 3, m_HeartSprite->GetWidth(), m_HeartSprite->GetHeight() / 6 });
	}
	if (playerHealth == 2)
	{
		m_HeartSprite->Draw(Point2f{ (map->m_RoomWidth - map->m_RoomWidth / 3) - 50, map->m_RoomHeight + map->m_RoomHeight / 10 },
			Rectf{ 0, ((m_HeartSprite->GetHeight() / 6) * 4) - 3, m_HeartSprite->GetWidth(), m_HeartSprite->GetHeight() / 6 });
	}
	if (playerHealth == 1)
	{
		m_HeartSprite->Draw(Point2f{ (map->m_RoomWidth - map->m_RoomWidth / 3) - 50, map->m_RoomHeight + map->m_RoomHeight / 10 },
			Rectf{ 0, (m_HeartSprite->GetHeight() / 6) * 5, m_HeartSprite->GetWidth(), m_HeartSprite->GetHeight() / 6 });
	}

	// Draw the map
	utils::SetColor(Color4f{ 0.f, 0.f, 0.f, 1.f });
	for (int rowIndex{}; rowIndex < map->m_ROWS; ++rowIndex)
	{
		for (int columnIndex{}; columnIndex <map-> m_COLUMNS; ++columnIndex)
		{
			if (map->m_RoomArray[rowIndex][columnIndex].m_Discoverd)
			{
				const float xPos{ (float)(columnIndex * m_CellWidth) - 50.f };
				const float yPos{ map->m_RoomHeight + 10 + rowIndex * m_CellHeight };
				if (map->m_RoomArray[rowIndex][columnIndex].m_CurrentRoom)
				{
					utils::SetColor(Color4f{ 1.f,1.f,1.f,1.f });
				}
				else
				{
					utils::SetColor(Color4f{ 0.3f,0.3f,0.3f,1.f });
				}
				utils::FillRect(xPos, yPos, m_CellWidth, m_CellHeight);
				utils::SetColor(Color4f{ 0.f,0.f,0.f,1.f });
				utils::DrawRect(xPos, yPos, m_CellWidth, m_CellHeight);
				if (map->m_RoomArray[rowIndex][columnIndex].m_RoomType == Map::RoomType::Boss)
				{
					m_Skull->Draw(Rectf{xPos + 10, yPos - 5, 20,20});
				}
				if (map->m_RoomArray[rowIndex][columnIndex].m_RoomType == Map::RoomType::Reward)
				{
					m_Crown->Draw(Rectf{ xPos + 10, yPos - 5, 20,20 });
				}
			}
		}

	}
}
