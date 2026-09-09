#pragma once
#include <vector>
class Texture;

class BossPlatform
{
public:

	BossPlatform(std::vector<Vector2f> startVector);
	~BossPlatform();

	void Update(float elapsedSec, const bool bossDead);
	void Draw() const;
	std::vector<Vector2f> GetHitBox() const;

private:

	Texture* m_BossPlatformTexturePtr{ nullptr };
	Texture* m_DestroyedBossPlatformTexturePtr{ nullptr };
	std::vector<Vector2f> m_HitBox;
	Vector2f m_Position{ 0,0 };
	bool m_Destroyed{ false };
};