#include "pch.h"
#include "InnerEye.h"
#include "utils.h"

InnerEye::InnerEye(Point2f SpawnPos)
	:PickUp()
	,m_Position{SpawnPos}
{
	m_ID = ID::InnerEye;
	m_InnerEyePickUpSritePtr = new Texture("PowerUp_InnerEye.png");
}

InnerEye::~InnerEye()
{
	delete m_InnerEyePickUpSritePtr;
	m_InnerEyePickUpSritePtr = nullptr;
}

void InnerEye::Draw() const
{
	if (!m_PickedUp)
	{
		m_InnerEyePickUpSritePtr->Draw(Point2f{ m_Position.x - (m_InnerEyePickUpSritePtr->GetWidth() / 2),
			m_Position.y - (m_InnerEyePickUpSritePtr->GetHeight() / 2) }, Rectf{0,0,m_InnerEyePickUpSritePtr->GetWidth() ,
			m_InnerEyePickUpSritePtr->GetHeight() });
	}
}

void InnerEye::Update(const Rectf& playerHitBox)
{
	if (utils::IsOverlapping(playerHitBox, Rectf{ m_Position.x - (m_InnerEyePickUpSritePtr->GetWidth() / 2),
	m_Position.y - (m_InnerEyePickUpSritePtr->GetHeight() / 2) ,m_InnerEyePickUpSritePtr->GetWidth() ,
	m_InnerEyePickUpSritePtr->GetHeight() }))
	{
		m_PickedUp = true;
	}
}

PickUp::ID InnerEye::GetID() const
{
	return m_ID;
}
