#pragma once
#include <vector>
#include "utils.h"
class Texture;
class SoundEffect;
class XBullet;
class BulletManager;

class Player final
{
public:

	explicit Player(Vector2f startingPos = Vector2f{0.f, 0.f}, BulletManager* bulletManager = nullptr);
	~Player();

	void Draw() const;
	void Update(float elapsedSec, const Uint8* pStates, const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	Vector2f GetPosition() const;
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);
	void PlayerHit(int damage);
	int GetPlayerHealth();
	Rectf GetPlayerHitBox() const;
	bool GetIntroPlayed() const;

	virtual void SetVolume(const int Volume);

	// RULE OF FIVE
	Player(const Player& other) = delete;
	Player& operator=(const Player& rhs) = delete;
	Player(Player&& rhs) = delete;
	Player& operator=(Player&& rhs) = delete;

private:

	// ENUM CLASSES
	enum class State
	{
		Still,
		Run,
		Jump,
		WallJump,
		Fall,
		Land,
		Hit
	};

	// FUNCTIONS
	void HandleMovement(float elapsedSec, const Uint8* pStates, const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	void HandleShootCharge(float elapsedSec);
	void HandleVisual() const;
	void UpdateState(float elapsedSec, const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	void ChargeAnimation() const;
	void Shoot();
	Rectf GetCurrentFrameRect(int srpiteNr, int spriteFrames) const;
	bool HitWallUp(const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	bool HitWallDown(const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	bool HitWallLeft(const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	bool HitWallRight(const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	bool IsCloseToGround(const std::vector<std::vector<Vector2f>>& MapHitBoxes);
	void DrawIntro() const;
	void UpdateIntro(float elapsedSec, const std::vector<std::vector<Vector2f>>& MapHitBoxes);

	// DATAMEMBERS
	Vector2f m_PlayerPosition;
	Vector2f m_PlayerVelocity;
	std::vector<Texture*> m_PlayerTexturesPtr;
	BulletManager* m_BulletManagerPtr;
	Rectf m_PlayerHitBox{ 0, 0, 0, 0 };
	float m_FrameNr{ 0 };
	std::vector<float> m_AnimationsStart{};
	bool m_Shooting{ false };
	float m_AirTime{ 0.f };
	bool m_IsCharging{ false };
	float m_ChargeCounter{ 0 };
	float m_PlayerHeight{ 0 };
	float m_PlayerWidth{ 0 };
	bool m_FacingRight{ true };
	int m_PlayerHealth{ 16 };
	State m_State{ State::Still };
	std::vector<SoundEffect*> m_SoundEffectsPtr;
	bool m_SfxPlaying{ false };
	bool m_HitWallRight{ false };
	bool m_Invincible{ false };
	bool m_IntroPlayed{ false };
};

