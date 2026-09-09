#pragma once
class Texture;

class GUI final
{
public:

	explicit GUI();
	~GUI();

	void Draw(int health) const;

private:
	//DATA
	Texture* m_HealthBarTexturePtr{ nullptr };
	Texture* m_HealthBarBitTexturePtr{ nullptr };
};

