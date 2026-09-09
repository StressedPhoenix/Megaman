#include "pch.h"
#include "Player.h"
#include <iostream>
#include "Bullet.h"

Player::Player(Point2f startPos)
	:m_IsaacPos{startPos}
	,m_HeadRotation{HeadRotation::down}
	,m_MovementDirection{MovementDirection::Down}
{
	m_IsaacHeadSpritePtr = new Texture("Isaac_Head.PNG");
	m_IsaacBodySpritePtr = new Texture("Isaac_Body.PNG");
	m_IsaacHeadInnerEyeSpritePtr = new Texture("Isaac_Head_InnerEye.png");
	m_BulletPtrVctr.reserve(200);
}

Player::~Player()
{
	delete m_IsaacHeadSpritePtr;
	m_IsaacHeadSpritePtr = nullptr;

	delete m_IsaacBodySpritePtr;
	m_IsaacBodySpritePtr = nullptr;

}

void Player::Draw(std::vector<PickUp*> items) const
{
	DrawBody();
	DrawHead(items);
	if (m_BulletPtrVctr.size() > 0)
	{
		for (int idx{ m_BulletsDeleted }; idx < m_BulletPtrVctr.size(); ++idx)
		{
			if(!m_BulletPtrVctr[idx]->GetHit())
			{
				m_BulletPtrVctr[idx]->Draw();
			}
		}
	}
}

void Player::Update(float elapsedSec, std::vector<Rectf> Horizontal, std::vector <Rectf> Vertical, std::vector<PickUp*> items, std::vector <Enemy*> enemies)
{
	// update the bullets
	if (m_BulletPtrVctr.size() > 0)
	{
		for (int idx{ m_BulletsDeleted }; idx < m_BulletPtrVctr.size(); ++idx)
		{
			m_BulletPtrVctr[idx]->Update(elapsedSec);

			if (m_BulletPtrVctr[idx]->HitGround())
			{
				delete m_BulletPtrVctr[m_BulletsDeleted];
				++m_BulletsDeleted;
			}
		}
	}

	if (m_BulletDelay >= 1)
	{
		m_BulletDelay += 1 * elapsedSec;
		
		float bulletDelay{ 1.5f };
		bool innerEye{false};
		for (PickUp* PickUp : items)
		{
			if(PickUp->GetID() == PickUp::ID::InnerEye)
			{
				innerEye = PickUp->IsPickedUp();
			}
		}
		if(innerEye)
		{
			bulletDelay = 1.25f;
		}
		if (m_BulletDelay > bulletDelay) m_BulletDelay = 0;
	}

	// Update the head
	if (m_HeadRotation != HeadRotation::down)
	{
		m_HeadResetCounter += (2 * elapsedSec);
		int headReset{ (int)m_HeadResetCounter % 2 };
		if (headReset == 0)
		{
			m_HeadRotation = HeadRotation::down;
			m_HeadResetCounter = 1;
		}
	}

	// Update the position
	
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	// read the key values
	const bool isLeft{ bool(pStates[SDL_SCANCODE_A]) };
	const bool isRight{ bool(pStates[SDL_SCANCODE_D]) };
	const bool isUp{ bool(pStates[SDL_SCANCODE_W]) };
	const bool isDown{ bool(pStates[SDL_SCANCODE_S]) };

	//update position and sprite direction
	m_MovementDirection = MovementDirection::Still;
	if (isLeft)
	{
		if (!HitWallLeft(Vertical))
		{
			m_IsaacPos.x -= m_MovementSpeed * elapsedSec;
			m_MovementDirection = MovementDirection::Left;
		}
			m_FrameCounter += (9.5f * elapsedSec);
			m_CurrentFrame = (int)m_FrameCounter % 11;
		
	}
	if (isRight)
	{
		if (!HitWallRight(Vertical))
		{
			m_IsaacPos.x += m_MovementSpeed * elapsedSec;
			m_MovementDirection = MovementDirection::Right;
		}
			m_FrameCounter += (9.5f * elapsedSec);
			m_CurrentFrame = (int)m_FrameCounter % 11;
		
	}
	if (isUp)
	{
		if (!HitWallUp(Horizontal))
		{
			m_IsaacPos.y += m_MovementSpeed * elapsedSec;
			m_MovementDirection = MovementDirection::Up;
		}
			m_FrameCounter += (9.5f * elapsedSec);
			m_CurrentFrame = (int)m_FrameCounter % 11;
		
	}
	if (isDown)
	{
		if (!HitWallDown(Horizontal))
		{
			m_IsaacPos.y -= m_MovementSpeed * elapsedSec;
			m_MovementDirection = MovementDirection::Down;
		}
			m_FrameCounter += (9.5f * elapsedSec);
			m_CurrentFrame = (int)m_FrameCounter % 11;
	}
	//Update the body
	if (isLeft || isRight || isUp || isDown);
	else
	{
		m_FrameCounter = 0;
		m_CurrentFrame = 0;
	}

	
}

void Player::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	int headReset{ (int)m_HeadResetCounter % 2 };
	switch (e.keysym.sym)
	{
	case SDLK_LEFT:
		//Head
		m_HeadRotation = HeadRotation::left;
		m_HeadResetCounter = 1;
		// Bullet
		if (m_BulletDelay == 0)
		{
			m_BulletPtrVctr.push_back(new Bullet(m_IsaacPos, true, false, false, false));
			m_BulletDelay = 1;
		}
		break;
	case SDLK_RIGHT:
		//Head
		m_HeadRotation = HeadRotation::right;
		m_HeadResetCounter = 1;
		//Bullet
		if (m_BulletDelay == 0)
		{
			m_BulletPtrVctr.push_back(new Bullet(m_IsaacPos, false, true, false, false));
			m_BulletDelay = 1;
		}
	break;
	case SDLK_UP:
		//Head
		m_HeadRotation = HeadRotation::up;
		m_HeadResetCounter = 1;
		//Bullet
		if (m_BulletDelay == 0)
		{
			m_BulletPtrVctr.push_back(new Bullet(m_IsaacPos, false, false, true, false));
			m_BulletDelay = 1;
		}
	break;
	case SDLK_DOWN:
		//Head
		m_HeadRotation = HeadRotation::down;
		//Bullet
		if (m_BulletDelay == 0)
		{
			m_BulletPtrVctr.push_back(new Bullet(m_IsaacPos, false, false, false, true));
			m_BulletDelay = 1;
		}
	break;
	}
}

Point2f Player::GetPlayerPos()
{
	return m_IsaacPos;
}

Rectf Player::GetPlayerHitbox() const
{
	return Rectf{ m_IsaacPos.x - m_IsaacBodySpritePtr->GetWidth() / 15, m_IsaacPos.y - m_IsaacBodySpritePtr->GetHeight() / 4,
		m_IsaacHeadSpritePtr->GetWidth() / 10, m_IsaacHeadSpritePtr->GetHeight() + m_IsaacBodySpritePtr->GetHeight() / 4 };
}

int Player::GetPlayerHealth() const
{
	return m_Health;
}

std::vector<Bullet*> Player::GetBulletPtrVctr() const
{
	return m_BulletPtrVctr;
}

void Player::DrawHead(std::vector<PickUp*> items) const
{
	bool innerEye{ false };
	for (PickUp* PickUp : items)
	{
		if (PickUp->GetID() == PickUp::ID::InnerEye)
		{
			innerEye = PickUp->IsPickedUp();
		}
	}
	if (innerEye)
	{
		Rectf drawRect{ 0, 0, m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8, m_IsaacHeadInnerEyeSpritePtr->GetHeight() };
		switch (m_HeadRotation)
		{
		case HeadRotation::down:
			drawRect = Rectf{ m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8 * 0, 0,
				m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8, m_IsaacHeadInnerEyeSpritePtr->GetHeight() };
			break;
		case Player::HeadRotation::left:
			drawRect = Rectf{ m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8 * 6, 0,
				m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8, m_IsaacHeadInnerEyeSpritePtr->GetHeight() };
			break;
		case Player::HeadRotation::right:
			drawRect = Rectf{ m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8 * 2, 0,
				m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8, m_IsaacHeadInnerEyeSpritePtr->GetHeight() };
			break;
		case Player::HeadRotation::up:
			drawRect = Rectf{ m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8 * 4, 0,
				m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 8, m_IsaacHeadInnerEyeSpritePtr->GetHeight() };
			break;
		}
		m_IsaacHeadInnerEyeSpritePtr->Draw(Point2f{ m_IsaacPos.x - m_IsaacHeadInnerEyeSpritePtr->GetWidth() / 16, m_IsaacPos.y }, drawRect);
	}
	else
	{
		Rectf drawRect{ 0, 0, m_IsaacHeadSpritePtr->GetWidth() / 8, m_IsaacHeadSpritePtr->GetHeight() };
		switch (m_HeadRotation)
		{
		case HeadRotation::down:
			drawRect = Rectf{ m_IsaacHeadSpritePtr->GetWidth() / 8 * 0, 0,
				m_IsaacHeadSpritePtr->GetWidth() / 8, m_IsaacHeadSpritePtr->GetHeight() };
			break;
		case Player::HeadRotation::left:
			drawRect = Rectf{ m_IsaacHeadSpritePtr->GetWidth() / 8 * 6, 0,
				m_IsaacHeadSpritePtr->GetWidth() / 8, m_IsaacHeadSpritePtr->GetHeight() };
			break;
		case Player::HeadRotation::right:
			drawRect = Rectf{ m_IsaacHeadSpritePtr->GetWidth() / 8 * 2, 0,
				m_IsaacHeadSpritePtr->GetWidth() / 8, m_IsaacHeadSpritePtr->GetHeight() };
			break;
		case Player::HeadRotation::up:
			drawRect = Rectf{ m_IsaacHeadSpritePtr->GetWidth() / 8 * 4, 0,
				m_IsaacHeadSpritePtr->GetWidth() / 8, m_IsaacHeadSpritePtr->GetHeight() };
			break;
		}
		m_IsaacHeadSpritePtr->Draw(Point2f{ m_IsaacPos.x - m_IsaacHeadSpritePtr->GetWidth() / 16, m_IsaacPos.y }, drawRect);
	}

}

void Player::DrawBody() const
{
	int offset{ 8 };
	Rectf drawRect{ 0, 0, m_IsaacBodySpritePtr->GetWidth() / 10, m_IsaacBodySpritePtr->GetHeight() / 3 };
	switch (m_MovementDirection)
	{
	case MovementDirection::Still:
		drawRect = Rectf{ 0, 0, m_IsaacBodySpritePtr->GetWidth() / 10, m_IsaacBodySpritePtr->GetHeight() / 3 };
	case MovementDirection::Up:
		drawRect = Rectf{m_IsaacBodySpritePtr->GetWidth() / 10 * m_CurrentFrame, 0,
			m_IsaacBodySpritePtr->GetWidth() / 10, m_IsaacBodySpritePtr->GetHeight() / 3};
		break;
	case MovementDirection::Down:
		drawRect = Rectf{ m_IsaacBodySpritePtr->GetWidth() / 10 * m_CurrentFrame, 0,
			m_IsaacBodySpritePtr->GetWidth() / 10, m_IsaacBodySpritePtr->GetHeight() / 3 };
		break;
	case MovementDirection::Left:
		drawRect = Rectf{m_IsaacBodySpritePtr->GetWidth() / 10 * m_CurrentFrame, (m_IsaacBodySpritePtr->GetHeight() / 3) * 2,
			m_IsaacBodySpritePtr->GetWidth() / 10, m_IsaacBodySpritePtr->GetHeight() / 3};
		break;
	case MovementDirection::Right:
		drawRect = Rectf{ m_IsaacBodySpritePtr->GetWidth() / 10 * m_CurrentFrame, m_IsaacBodySpritePtr->GetHeight() / 3,
			m_IsaacBodySpritePtr->GetWidth() / 10, m_IsaacBodySpritePtr->GetHeight() / 3 };
		break;
	}
	m_IsaacBodySpritePtr->Draw(Point2f{ m_IsaacPos.x - m_IsaacBodySpritePtr->GetWidth() / 20,
		m_IsaacPos.y - (m_IsaacBodySpritePtr->GetHeight() - offset) / 3 }, drawRect);
}

bool Player::HitWallUp(std::vector<Rectf> Horizontal)
{
	Point2f hitPos{ m_IsaacPos.x , m_IsaacPos.y };

	for (const Rectf rect : Horizontal)
	{
		if (utils::IsPointInRect(hitPos, rect))
		{
			return true;
		}
	}
	return false;
}

bool Player::HitWallDown(std::vector<Rectf> Horizontal)
{
	Point2f hitPos{ m_IsaacPos.x , m_IsaacPos.y - (m_IsaacBodySpritePtr->GetHeight() / 6) };

	for (const Rectf rect : Horizontal)
	{
		if (utils::IsPointInRect(hitPos, rect))
		{
			return true;
		}
	}
	return false;
}

bool Player::HitWallLeft(std::vector<Rectf> Vertical)
{
	Point2f hitPos{ m_IsaacPos.x - (m_IsaacHeadSpritePtr->GetWidth() / 16) , m_IsaacPos.y - (m_IsaacBodySpritePtr->GetHeight() / 6)};

	for (const Rectf rect : Vertical)
	{
		if (utils::IsPointInRect(hitPos, rect))
		{
			return true;
		}
	}
	return false;
}

bool Player::HitWallRight(std::vector<Rectf> Vertical)
{
	Point2f hitPos{ m_IsaacPos.x + (m_IsaacHeadSpritePtr->GetWidth() / 16) , m_IsaacPos.y - (m_IsaacBodySpritePtr->GetHeight() / 6) };

	for (const Rectf rect : Vertical)
	{
		if (utils::IsPointInRect(hitPos, rect))
		{
			return true;
		}
	}
	return false;
}