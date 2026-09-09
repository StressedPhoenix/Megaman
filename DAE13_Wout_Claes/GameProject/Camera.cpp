#include "pch.h"
#include "Camera.h"

Camera::Camera(float ScreenWidth, float ScreenHeight, Point2f StartPos)
	:m_ScreenWidth{ ScreenWidth }
	,m_ScreenHeight{ ScreenHeight }
	,m_CameraPos{ StartPos.x - m_ScreenWidth / 2, (StartPos.y - m_ScreenHeight / 3) - 15 }
{
}

void Camera::Aim(Point2f trackCenter)
{
	float speed{ 5 };
	Point2f cameraTarget{ trackCenter.x - m_ScreenWidth / 2, (trackCenter.y - m_ScreenHeight / 3) - 15 };

	if (m_CameraPos.x < cameraTarget.x)
	{
		m_CameraPos.x += speed;
	}
	if (m_CameraPos.x > cameraTarget.x)
	{
		m_CameraPos.x -= speed;
	}

	if (m_CameraPos.y < cameraTarget.y)
	{
		m_CameraPos.y += speed;
	}
	if (m_CameraPos.y > cameraTarget.y)
	{
		m_CameraPos.y -= speed;
	}
	
	glPushMatrix();
	glTranslatef(-m_CameraPos.x, -m_CameraPos.y, 0);
}

void Camera::Reset()
{
	glPopMatrix();
}
