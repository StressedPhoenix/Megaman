#pragma once
#include "Enemy.h"

class Texture;

class Crusher final : public Enemy
{
public:

	explicit Crusher(Vector2f position, BulletManager* bulletManager = nullptr, Player* player = nullptr);
	~Crusher();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes) override;
	virtual void SetVolume(int Volume) const override;
	virtual Rectf GetEnemyHitBox() const;

	// RULE OF FIVE
	Crusher(const Crusher& other) = delete;
	Crusher& operator=(const Crusher& rhs) = delete;
	Crusher(Crusher&& rhs) = delete;
	Crusher& operator=(Crusher&& rhs) = delete;

private:

	// ENUM CLASSES
	enum class State
	{
		Move = 0,
		Attack = 1
	};

	// DATAMEMBERS
	State m_State{ State::Move };
	Texture* m_CrusherTexturePtr;
	Vector2f m_CrusherPosition{ 0, 0 };
	bool m_FacingRight{ false };
	Rectf m_CrusherHitBox{ 0,0,0,0 };
	bool m_CrusherUp{ false };
	SoundEffect* m_CrusherHitSound{ nullptr };
};