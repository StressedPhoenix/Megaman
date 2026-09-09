#pragma once
#include "Enemy.h"

class BallDeVoux final : public Enemy
{
public:

	explicit BallDeVoux(Vector2f position, BulletManager* bulletManager = nullptr, Player* player = nullptr);
	~BallDeVoux();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox, const std::vector<std::vector<Vector2f>>& MapHitBoxes) override;
	virtual void SetVolume(int Volume) const override;

	// RULE OF FIVE
	BallDeVoux(const BallDeVoux& other) = delete;
	BallDeVoux& operator=(const BallDeVoux& rhs) = delete;
	BallDeVoux(BallDeVoux&& rhs) = delete;
	BallDeVoux& operator=(BallDeVoux&& rhs) = delete;

private:

	// ENUM CLASSES
	enum class State
	{
		Roll = 0,
		GetUp = 1,
		Walk = 2
	};

	// DATAMEMBERS
	State m_State{ State::Roll };
};