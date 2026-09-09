#pragma once
#include <vector>
class Texture;
class SoundStream;
class Background;
class BossPlatform;

class Level final
{
public:

	explicit Level();
	~Level();

	void Draw(Vector2f playerPos) const;
	void Update(float elapsedSec, bool bossDead);
	float GetWidth() const;
	float GetHeight() const;
	const std::vector<std::vector<Vector2f>> GetMapHitBoxes() const;

	void SetVolume(const int Volume);

	Vector2f GetFirstBossAreaX() const;
	Vector2f GetSecondBossAreaX() const;

	// RULE OF FIVE
	Level(const Level& other) = delete;
	Level& operator=(const Level& rhs) = delete;
	Level(Level&& rhs) = delete;
	Level& operator=(Level&& rhs) = delete;

private:

	// FUNCTIONS
	void PushHitBoxes();
	void PopHitBoxes();

	// DATAMEMBERS
	Texture* m_LevelTexturePtr;
	std::vector<Texture*> m_CarTexturesPtr;
	Background* m_BackgroundPtr;
	std::vector <std::vector<Vector2f>> m_MapHitBoxes;
	Vector2f m_Scale{ 4.5f, 4.1f };
	SoundStream* m_MusicPtr{ nullptr };
	bool m_MusicPlaying{ false };
	BossPlatform* m_BossPlatform{ nullptr };
};

