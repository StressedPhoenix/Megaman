#include "pch.h"
#include "Player.h"
#include "BulletManager.h"
#include "Texture.h"
#include "SoundEffect.h"
#include <iostream>

Player::Player(Vector2f startingPos, BulletManager* bulletManager)
	:m_PlayerPosition{startingPos}
	,m_BulletManagerPtr{bulletManager}
{
	// SPRITES
	//0
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_Base.png" });
	//1
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_Running.png" });
	//2
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_Shooting_Running.png" });
	//3
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_Jumping.png" });
	//4
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_Jumping_Shooting.png" });
	//5
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_WallJump.png" });
	//6
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_ChargeEffect.png" });
	//7
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_Hit.png" });
	//8
	m_PlayerTexturesPtr.push_back(new Texture{ "x/x_Intro.png" });

	// SOUNDEFFECTS
	//0
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Jump.wav" });
	//1
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Land.wav" });
	//2
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Regular_Shot.wav" });
	//3
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Charge_Shot.wav" });
	//4
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Super_Charge_Shot.wav" });
	//5
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Charge.wav" });
	//6
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Full_Charge.wav" });
	//7
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Hurt.wav" });
	//8
	m_SoundEffectsPtr.push_back(new SoundEffect{ "Sound/X/Fade_In.wav" });

	// DATA
	m_PlayerHeight = m_PlayerTexturesPtr[0]->GetHeight();
	m_PlayerWidth = m_PlayerTexturesPtr[0]->GetWidth() / 2;

	m_PlayerPosition.y += 500.f;

	m_PlayerHitBox = Rectf{ m_PlayerPosition.x, m_PlayerPosition.y, m_PlayerWidth, m_PlayerHeight };

	// idx 0 = Shooting
	m_AnimationsStart.push_back(0.f);
	// idx 1 = Jumping
	m_AnimationsStart.push_back(0.f);
	// idx 2 = Falling
	m_AnimationsStart.push_back(0.f);
	// idx 3 = Charge Effect
	m_AnimationsStart.push_back(0.f);
	// idx 4 = Hit
	m_AnimationsStart.push_back(0.f);
	// idx 5 = Intro
	m_AnimationsStart.push_back(0.f);
}

Player::~Player()
{
	for (int idx{ 0 }; idx < m_SoundEffectsPtr.size(); ++idx)
	{
		delete m_SoundEffectsPtr[idx];
		m_SoundEffectsPtr[idx] = nullptr;
	}
	m_SoundEffectsPtr.clear();

	for (int idx{0}; idx < m_PlayerTexturesPtr.size(); ++idx)
	{
		delete m_PlayerTexturesPtr[idx];
		m_PlayerTexturesPtr[idx] = nullptr;
	}
	m_PlayerTexturesPtr.clear();
}

void Player::Draw() const
{
	if (m_IntroPlayed)
	{
		ChargeAnimation();

		HandleVisual();
	}
	else
	{
		DrawIntro();
	}
}

void Player::Update(float elapsedSec, const Uint8* pStates, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	if(m_IntroPlayed)
	{
		//Data
		m_PlayerHitBox = Rectf{ m_PlayerPosition.x, m_PlayerPosition.y, m_PlayerWidth, m_PlayerHeight };
		//Player Movement
		HandleMovement(elapsedSec, pStates, MapHitBoxes);
		//Bullets Charge
		HandleShootCharge(elapsedSec);
		//Animation
		UpdateState(elapsedSec, MapHitBoxes);
	}
	else
	{
		UpdateIntro(elapsedSec, MapHitBoxes);
	}
}

Vector2f Player::GetPosition() const
{
	return m_PlayerPosition;
}

void Player::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_IsCharging = true;
		m_SoundEffectsPtr[5]->Play(false);
		break;
	}
}

void Player::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	switch ( e.button )
	{
	case SDL_BUTTON_LEFT:
		m_SoundEffectsPtr[5]->StopAll();
		m_SfxPlaying = false;
		Shoot();
		break;
	}
}

void Player::PlayerHit(int damage)
{
	if(!m_Invincible && damage > 0)
	{
		m_Invincible = true;
		m_State = State::Hit;
		m_SoundEffectsPtr[7]->Play(false);
		m_PlayerHealth -= damage;
	}
}

int Player::GetPlayerHealth()
{
	return m_PlayerHealth;
}

Rectf Player::GetPlayerHitBox() const
{
	return m_PlayerHitBox;
}

bool Player::GetIntroPlayed() const
{
	return m_IntroPlayed;
}

void Player::SetVolume(const int Volume)
{
	for (int idx{ 0 }; idx < m_SoundEffectsPtr.size(); ++idx)
	{
		if (m_SoundEffectsPtr[idx] != nullptr)
		{
			m_SoundEffectsPtr[idx]->SetVolume(Volume);
		}
	}
}

void Player::HandleMovement(float elapsedSec, const Uint8* pStates, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	const float speed{ 300.f };
	const float gravity{ 30.f };
	const float jumpSpeed{ 600.f };
	const float wallSlideSpeed{ 30.f };
	bool canWallJump{ false };

	bool hitUp{ HitWallUp(MapHitBoxes) };
	bool hitRight{ HitWallRight(MapHitBoxes) };
	bool hitDown{ HitWallDown(MapHitBoxes) };
	bool hitLeft{ HitWallLeft(MapHitBoxes) };

	// MOVEMENT X
	if (m_Invincible)
	{
		m_PlayerVelocity.x = -200;
	}
	else
	{
		m_PlayerVelocity.x = 0;
	}
	// Movemment to the right
	if (pStates[SDL_SCANCODE_D] && !hitRight)
	{
		m_FacingRight = true;
		m_PlayerVelocity.x = speed;
	}
	// Movement to the left
	else if (pStates[SDL_SCANCODE_A] && !hitLeft)
	{
		m_FacingRight = false;
		m_PlayerVelocity.x = -speed;
	}

	// MOVEMENT Y
	
	// Wall jump
	if (!hitDown && (hitLeft || hitRight))
	{
		m_PlayerVelocity.y -= wallSlideSpeed;
		canWallJump = true;
	}
	else
	{
		canWallJump = false;
	}

	// Jump
	if (pStates[SDL_SCANCODE_SPACE])
	{
		if (hitDown || m_AirTime <= 0.3f)
		{
			m_PlayerVelocity.y = jumpSpeed;
		}
		else if (canWallJump)
		{
			m_PlayerVelocity.y = jumpSpeed;

			if (hitLeft)
			{
				m_PlayerVelocity.x = speed;
			}
			else if (hitRight)
			{
				m_PlayerVelocity.x = -speed;
			}

			m_AirTime = 0.f;

			m_SoundEffectsPtr[0]->Play(false);
		}
		if (hitDown)
		{
			m_FrameNr = 0;
			
			m_SoundEffectsPtr[0]->Play(false);
		}
	}
	// Gravity
	if (!hitDown && !hitLeft && !hitRight)
	{
		if (!(m_PlayerVelocity.y <= -600))
		{
			m_PlayerVelocity.y -= gravity;
		}
		m_AirTime += 1 * elapsedSec;
	}
	else if (hitDown && !pStates[SDL_SCANCODE_SPACE])
	{
		if (m_PlayerVelocity.y != 0)
		{
			m_PlayerVelocity.y = 0;
			m_AirTime = 0.f;
		}
	}

	m_PlayerPosition += m_PlayerVelocity * elapsedSec;
}

void Player::HandleShootCharge(float elapsedSec)
{
	int shotCharger{1};
	if (m_IsCharging)
	{
		m_ChargeCounter += shotCharger * elapsedSec;
	}
	if (m_ChargeCounter > 3.35)
	{
		if(!m_SfxPlaying)
		{
			m_SoundEffectsPtr[6]->Play(100);
			m_SfxPlaying = true;
		}
	}
}

void Player::HandleVisual() const
{
	Rectf drawBox{};
	switch (m_State)
	{
		case State::Still:
			glPushMatrix();
			glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
			glRotatef(180 * !m_FacingRight, 0, 1, 0);

			drawBox = Rectf{ m_PlayerWidth * m_Shooting, 0, m_PlayerWidth, m_PlayerHeight };
			m_PlayerTexturesPtr[0]->Draw(Vector2f{0,0}, drawBox);

			glPopMatrix();
			break;

		case State::Run:
			if(!m_Shooting)
			{
				glPushMatrix();
				glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
				glRotatef(180 * !m_FacingRight, 0, 1, 0);

				drawBox = GetCurrentFrameRect(1, 11);
				m_PlayerTexturesPtr[1]->Draw(Vector2f{ 0,0 }, drawBox);

				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
				glRotatef(180 * !m_FacingRight, 0, 1, 0);

				drawBox = GetCurrentFrameRect(2, 11);
				m_PlayerTexturesPtr[2]->Draw(Vector2f{ 0,0 }, drawBox);

				glPopMatrix();
			}
			break;

		case State::Jump:
			if (!m_Shooting)
			{
				glPushMatrix();
				glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
				glRotatef(180 * !m_FacingRight, 0, 1, 0);
				if((int)m_AnimationsStart[1] <= 3)
				{
					drawBox = GetCurrentFrameRect(3, 7);
				}
				else 
				{
  					drawBox = Rectf((m_PlayerTexturesPtr[3]->GetWidth() / 7) * 3, (m_PlayerTexturesPtr[3]->GetHeight()), m_PlayerTexturesPtr[3]->GetWidth() / 7, m_PlayerTexturesPtr[3]->GetHeight());
				}
				m_PlayerTexturesPtr[3]->Draw(Vector2f{ 0,0 }, drawBox);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
				glRotatef(180 * !m_FacingRight, 0, 1, 0);
				if ((int)m_AnimationsStart[1] <= 3)
				{
					drawBox = GetCurrentFrameRect(4, 7);
				}
				else
				{
					drawBox = Rectf((m_PlayerTexturesPtr[4]->GetWidth() / 7) * 3, (m_PlayerTexturesPtr[4]->GetHeight()), m_PlayerTexturesPtr[4]->GetWidth() / 7, m_PlayerTexturesPtr[4]->GetHeight());
				}
				m_PlayerTexturesPtr[4]->Draw(Vector2f{ 0,0 }, drawBox);
				glPopMatrix();
			}
			break;

		case State::Fall:
			if (!m_Shooting)
			{
				glPushMatrix();
				glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
				glRotatef(180 * !m_FacingRight, 0, 1, 0);

				// Use static falling frame (e.g., frame 3 of row 3)
				drawBox = Rectf((m_PlayerTexturesPtr[3]->GetWidth() / 7) * 3, 0, m_PlayerTexturesPtr[3]->GetWidth() / 7, m_PlayerTexturesPtr[3]->GetHeight());

				m_PlayerTexturesPtr[3]->Draw(Vector2f{ 0,0 }, drawBox);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
				glRotatef(180 * !m_FacingRight, 0, 1, 0);

				// Use static falling frame (e.g., frame 3 of row 4)
				drawBox = Rectf((m_PlayerTexturesPtr[4]->GetWidth() / 7) * 3, 0, m_PlayerTexturesPtr[4]->GetWidth() / 7, m_PlayerTexturesPtr[4]->GetHeight());

				m_PlayerTexturesPtr[4]->Draw(Vector2f{ 0,0 }, drawBox);
				glPopMatrix();
			}
			break;

		case State::Land:
			if(!m_Shooting)
			{
				glPushMatrix();
				glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
				glRotatef(180 * !m_FacingRight, 0, 1, 0);
				if ((int)m_AnimationsStart[2] <= 1)
				{
					drawBox = Rectf((m_PlayerTexturesPtr[3]->GetWidth() / 7) * 5, 0, m_PlayerTexturesPtr[3]->GetWidth() / 7, m_PlayerTexturesPtr[3]->GetHeight());
				}
				else 
				{
					drawBox = Rectf((m_PlayerTexturesPtr[3]->GetWidth() / 7) * 6, 0, m_PlayerTexturesPtr[3]->GetWidth() / 7, m_PlayerTexturesPtr[3]->GetHeight());
				}
				m_PlayerTexturesPtr[3]->Draw(Vector2f{ 0,0 }, drawBox);
				glPopMatrix();
			}
			else
			{
				glPushMatrix();
				glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_FacingRight), m_PlayerPosition.y, 0);
				glRotatef(180 * !m_FacingRight, 0, 1, 0);
				if ((int)m_AnimationsStart[2] <= 1)
				{
					drawBox = Rectf((m_PlayerTexturesPtr[4]->GetWidth() / 7) * 5, 0, m_PlayerTexturesPtr[4]->GetWidth() / 7, m_PlayerTexturesPtr[4]->GetHeight());
				}
				else
				{
					drawBox = Rectf((m_PlayerTexturesPtr[4]->GetWidth() / 7) * 6, 0, m_PlayerTexturesPtr[4]->GetWidth() / 7, m_PlayerTexturesPtr[4]->GetHeight());
				}
				m_PlayerTexturesPtr[4]->Draw(Vector2f{ 0,0 }, drawBox);
				glPopMatrix();
			}
			break;

		case State::WallJump:
			glPushMatrix();
			glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_HitWallRight), m_PlayerPosition.y, 0);
			glRotatef(180 * !m_HitWallRight, 0, 1, 0);

			drawBox = Rectf{ m_PlayerTexturesPtr[5]->GetWidth() / 2 * m_Shooting, 0, (m_PlayerTexturesPtr[5]->GetWidth() / 2) - 15, m_PlayerTexturesPtr[5]->GetHeight()};
			m_PlayerTexturesPtr[5]->Draw(Vector2f{ 0,0 }, drawBox);

			glPopMatrix();
			break;

		case State::Hit:
			glPushMatrix();
			glTranslatef(m_PlayerPosition.x + (m_PlayerWidth * !m_HitWallRight), m_PlayerPosition.y, 0);
			glRotatef(180 * !m_HitWallRight, 0, 1, 0);
			glScalef(4, 4, 0);

			drawBox = GetCurrentFrameRect(7, 10);
			m_PlayerTexturesPtr[7]->Draw(Vector2f{ 0,0 }, drawBox);

			glPopMatrix();
			break;
	}
}

void Player::UpdateState(float elapsedSec, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	int animationSpeed{ 12 };

	// Shoot bool
	if (m_IsCharging)
	{
		m_AnimationsStart[3] += animationSpeed * elapsedSec;
	}
	else if (m_Shooting)
	{
		m_AnimationsStart[0] += 1 * elapsedSec;
		if (m_AnimationsStart[0] >= 0.3)
		{
			m_Shooting = false;
			m_AnimationsStart[0] = 0.f;
		}
	}

	// Frame Update
	m_FrameNr += animationSpeed * elapsedSec;

	// Run state
	if ((m_PlayerVelocity.x != 0) && HitWallDown(MapHitBoxes))
	{
		m_State = State::Run;
	}
	else if (HitWallDown(MapHitBoxes))
	{
		m_State = State::Still;
	}

	// Jump, fall and land state
	if (m_PlayerVelocity.y > 0)
	{
		m_State = State::Jump;
	}
	else if(m_PlayerVelocity.y < 0)
	{
		m_State = State::Fall;
	}

	if (m_PlayerVelocity.y < 0 && IsCloseToGround(MapHitBoxes)) // falling and near ground
	{
		m_State = State::Land;
		m_AnimationsStart[2] = 0.f;
		
		m_SoundEffectsPtr[1]->Play(false);
	}

	if (m_State == State::Jump)
	{
		m_AnimationsStart[1] += animationSpeed * elapsedSec;
	}
	else if (m_State == State::Fall)
	{
		m_AnimationsStart[1] = 0;

		m_AnimationsStart[2] += animationSpeed * elapsedSec;
	}

	if (m_State == State::Land)
	{
		m_AnimationsStart[2] += animationSpeed * elapsedSec;
	}

	// WallJump state
	if ((HitWallLeft(MapHitBoxes) || HitWallRight(MapHitBoxes)) && !HitWallDown(MapHitBoxes))
	{
		m_State = State::WallJump;

		m_HitWallRight = HitWallRight(MapHitBoxes);
	}

	// Hit state
	if (m_Invincible)
	{
		m_State = State::Hit;
		m_AnimationsStart[4] += 1 * elapsedSec;
		if (m_AnimationsStart[4] >= 0.5)
		{
			m_State = State::Still;
			m_Invincible = false;
			m_AnimationsStart[4] = 0;
		}
	}
}

void Player::ChargeAnimation() const
{
	if (m_IsCharging)
	{
		glPushMatrix();
		glTranslatef(m_PlayerPosition.x, m_PlayerPosition.y, 0);
		glScalef(3, 3, 0);

		Rectf drawBox{};
		if (m_ChargeCounter <= 1.7)
		{
			drawBox = Rectf{ (m_PlayerTexturesPtr[6]->GetWidth() / 11) * static_cast<int>(m_AnimationsStart[3]), (m_PlayerTexturesPtr[6]->GetHeight() / 2) * 0,
				m_PlayerTexturesPtr[6]->GetWidth() / 11, m_PlayerTexturesPtr[6]->GetHeight() / 2};
		}
		else if (m_ChargeCounter > 1.7)
		{
			drawBox = Rectf{ (m_PlayerTexturesPtr[6]->GetWidth() / 11) * static_cast<int>(m_AnimationsStart[3]), (m_PlayerTexturesPtr[6]->GetHeight() / 2) * 1,
				m_PlayerTexturesPtr[6]->GetWidth() / 11, m_PlayerTexturesPtr[6]->GetHeight() / 2 };
		}
		m_PlayerTexturesPtr[6]->Draw(Vector2f{0,0}, drawBox);
		glPopMatrix();
	}
}

void Player::Shoot()
{
	m_IsCharging = false;
	m_AnimationsStart[3] = 0.f;
	m_Shooting = true;
	Vector2f shootPos{};

	if (m_State == State::WallJump)
	{
		if (m_HitWallRight)
			shootPos = Vector2f{ m_PlayerPosition.x, m_PlayerPosition.y + m_PlayerWidth / 2 };
		else
			shootPos = Vector2f{ m_PlayerPosition.x + m_PlayerWidth, m_PlayerPosition.y + m_PlayerWidth / 2 };
	}
	else
	{
		if (m_FacingRight)
			shootPos = Vector2f{ m_PlayerPosition.x + m_PlayerWidth, m_PlayerPosition.y + m_PlayerWidth / 2 };
		else
			shootPos = Vector2f{ m_PlayerPosition.x, m_PlayerPosition.y + m_PlayerWidth / 2 };
	}

	XBullet::ChargeLevel m_CurrentChargeLevel{XBullet::ChargeLevel::NoCharge};

	if (m_ChargeCounter > 1.7)
	{
		m_CurrentChargeLevel = XBullet::ChargeLevel::FullCharge;
		m_SoundEffectsPtr[4]->Play(false);
		if (m_State == State::WallJump)
		{
			m_BulletManagerPtr->Shoot(shootPos, !m_HitWallRight, BulletManager::BulletID::XBullet, m_CurrentChargeLevel);
		}
		else
		{
			m_BulletManagerPtr->Shoot(shootPos, m_FacingRight, BulletManager::BulletID::XBullet, m_CurrentChargeLevel);
		}
		m_ChargeCounter = 0;
		return;
	}

	if (m_ChargeCounter < 0.1)
	{
		m_SoundEffectsPtr[2]->Play(false);
		if (m_State == State::WallJump)
		{
			m_BulletManagerPtr->Shoot(shootPos, !m_HitWallRight, BulletManager::BulletID::XBullet, m_CurrentChargeLevel);
		}
		else
		{
			m_BulletManagerPtr->Shoot(shootPos, m_FacingRight, BulletManager::BulletID::XBullet, m_CurrentChargeLevel);
		}
		m_ChargeCounter = 0;
		return;
	}

	if (m_ChargeCounter > 0.1);
	{
		m_CurrentChargeLevel = XBullet::ChargeLevel::HalfCharge;
		m_SoundEffectsPtr[3]->Play(false);
		if (m_State == State::WallJump)
		{
			m_BulletManagerPtr->Shoot(shootPos, !m_HitWallRight, BulletManager::BulletID::XBullet, m_CurrentChargeLevel);
		}
		else
		{
			m_BulletManagerPtr->Shoot(shootPos, m_FacingRight, BulletManager::BulletID::XBullet, m_CurrentChargeLevel);
		}
		m_ChargeCounter = 0;
		return;
	}
}

Rectf Player::GetCurrentFrameRect(int spriteNr, int spriteFrames) const
{
	return Rectf((m_PlayerTexturesPtr[spriteNr]->GetWidth() / spriteFrames) * static_cast<int>(m_FrameNr),(m_PlayerTexturesPtr[spriteNr]->GetHeight()), m_PlayerTexturesPtr[spriteNr]->GetWidth() / spriteFrames, m_PlayerTexturesPtr[spriteNr]->GetHeight());
}

bool Player::HitWallUp(const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	Rectf HitBoxUp{ m_PlayerPosition.x, m_PlayerPosition.y + m_PlayerHeight, m_PlayerWidth, 2.f };
	for (int idx{ 0 }; idx < MapHitBoxes.size(); idx++)
	{
		if (utils::IsOverlapping(MapHitBoxes[idx], HitBoxUp))
		{
			return true;
		}
	}
	return false; 
}

bool Player::HitWallDown(const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	Rectf HitBoxDown{ m_PlayerPosition.x + 10.f, m_PlayerPosition.y, m_PlayerWidth - 20.f, -5.f };
	for (int idx{ 0 }; idx < MapHitBoxes.size(); idx++)
	{
		if (utils::IsOverlapping(MapHitBoxes[idx], HitBoxDown))
		{
			return true;
		}
	}
	return false;
}

bool Player::HitWallLeft(const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	float offset{ 10 };
	Rectf HitBoxLeft{ m_PlayerPosition.x, m_PlayerPosition.y + offset, -2.f, m_PlayerHeight - offset };
	for (int idx{ 0 }; idx < MapHitBoxes.size(); idx++)
	{
		if (utils::IsOverlapping(MapHitBoxes[idx], HitBoxLeft))
		{
			return true;
		}
	}
	return false;
}

bool Player::HitWallRight(const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	float offset{ 10 };
	Rectf HitBoxRight{ m_PlayerPosition.x + m_PlayerWidth, m_PlayerPosition.y + offset, 2.f, m_PlayerHeight - offset };
	for (int idx{ 0 }; idx < MapHitBoxes.size(); idx++)
	{
		if (utils::IsOverlapping(MapHitBoxes[idx], HitBoxRight))
		{
			return true;
		}
	}
	return false;
}

bool Player::IsCloseToGround(const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	Rectf HitBoxDown{ m_PlayerPosition.x, m_PlayerPosition.y, m_PlayerWidth, -45.f };
	for (int idx{ 0 }; idx < MapHitBoxes.size(); ++idx)
	{
		if (utils::IsOverlapping(MapHitBoxes[idx], HitBoxDown))
		{
			return true;
		}
	}
	return false;
}

void Player::DrawIntro() const
{
	glPushMatrix();
	glTranslatef(m_PlayerPosition.x, m_PlayerPosition.y, 0);
	glScalef(4, 4, 0);
	Rectf drawBox{ GetCurrentFrameRect(8,10) };

	m_PlayerTexturesPtr[8]->Draw(Vector2f{0, 0}, drawBox);

	glPopMatrix();
}

void Player::UpdateIntro(float elapsedSec, const std::vector<std::vector<Vector2f>>& MapHitBoxes)
{
	if (!m_SfxPlaying)
	{
		m_SoundEffectsPtr[8]->Play(false);
		m_SfxPlaying = true;
	}
	if(!HitWallDown(MapHitBoxes))
	{
		m_FrameNr = 0;
		m_PlayerVelocity.y = -500.f;
		m_PlayerPosition += m_PlayerVelocity * elapsedSec;
	}
	else
	{
		if (m_AnimationsStart[5] >= 9)
		{
			m_IntroPlayed = true;
			m_SfxPlaying = false;
		}
		else
		{
			m_FrameNr += 12 * elapsedSec;
			m_AnimationsStart[5] += 12 * elapsedSec;
		}
	}
}