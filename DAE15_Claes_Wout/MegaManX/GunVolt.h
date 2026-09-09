#pragma once
#include "Enemy.h"
class BulletManager;

class GunVolt final : public Enemy
{
public:

	explicit GunVolt(Vector2f position, BulletManager* bulletManager = nullptr, Player* player = nullptr);
	~GunVolt();

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const std::vector<Rectf>& bulletHitBox,const std::vector<std::vector<Vector2f>>& MapHitBoxes) override;
	virtual void SetVolume(int Volume) const override;

	// RULE OF FIVE
	GunVolt(const GunVolt& other) = delete;
	GunVolt& operator=(const GunVolt& rhs) = delete;
	GunVolt(GunVolt&& rhs) = delete;
	GunVolt& operator=(GunVolt&& rhs) = delete;

private:

	// ENUM CLASSES
	enum class State
	{
		Idle = 0,
		AttackStart = 1,
		GroundAttack = 2,
		MissileAttack = 3,
		AttackDone = 4
	};

	// DATAMEMBERS
	State m_State{State::Idle};
	SoundEffect* m_MissileFireSoundPtr{ nullptr };
	SoundEffect* m_GroundBulletFireSoundPtr{ nullptr };
};