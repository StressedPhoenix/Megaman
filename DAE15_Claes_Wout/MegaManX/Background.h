#pragma once
class Texture;

class Background final
{
public:

	explicit Background();
	~Background();

	void Draw(Vector2f playerPos) const;

	// RULE OF FIVE
	Background(const Background& other) = delete;
	Background& operator=(const Background& rhs) = delete;
	Background(Background&& rhs) = delete;
	Background& operator=(Background&& rhs) = delete;

private:

	// FUNCTIONS

	// DATAMEMBERS
	Texture* m_BackgroundTexturePtr;
};

