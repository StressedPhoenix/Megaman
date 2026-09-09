#pragma once
#include "Texture.h"
class Map;

class UI
{
public:
	
	UI();
	~UI();
	void Draw(const Map* map, const int& playerHealth) const;

	UI(const UI& other) = delete;
	UI& operator=(const UI& rhs) = delete;
	UI(UI&& rhs) = delete;
	UI& operator=(UI&& rhs) = delete;

private:
	Texture* m_HeartSprite;
	Texture* m_Crown;
	Texture* m_Skull;

	int m_CellWidth;
	int m_CellHeight;
};

