#pragma once
#include "Enemy.h"

class Spiky final : public Enemy
{
public:

	explicit Spiky(Vector2f position, BulletManager* bulletManager = nullptr, Player* player = nullptr);
	~Spiky();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes) override;
	virtual void SetVolume(int Volume) const override;

	// RULE OF FIVE
	Spiky(const Spiky& other) = delete;
	Spiky& operator=(const Spiky& rhs) = delete;
	Spiky(Spiky&& rhs) = delete;
	Spiky& operator=(Spiky&& rhs) = delete;

private:

	// ENUM CLASSES
	enum class State
	{
		Normal = 0,
		FallDown = 1
	};

	// DATAMEMBERS
	State m_State{ State::Normal };
};