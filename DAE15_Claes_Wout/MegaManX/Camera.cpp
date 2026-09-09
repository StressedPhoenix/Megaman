#include "pch.h"
#include "Camera.h"

Camera::Camera(const float ScreenWidth, const float ScreenHeight)
	:m_ScreenWidth{ScreenWidth}
	,m_ScreenHeight{ScreenHeight}
{
}

void Camera::Aim(const float levelW, const float levelH, const Vector2f& trackCenter, const bool freeY)
{
	enum class CameraState
	{
		Normal,
		FreeY,
	};
	CameraState cameraState{ CameraState::Normal };

	if (freeY)
	{
		cameraState = CameraState::FreeY;
	}

	glPushMatrix();

	if (cameraState == CameraState::Normal)
	{
		Vector2f baseCamera{ trackCenter.x - m_ScreenWidth / 2, 520 - m_ScreenHeight / 2 };
		if (baseCamera.x <= 0)
			baseCamera.x = 0;

		if ((baseCamera.x + m_ScreenWidth) >= levelW)
			baseCamera.x = (levelW - m_ScreenWidth);

		if (baseCamera.y <= 0)
			baseCamera.y = 0;

		if ((baseCamera.y + m_ScreenHeight) >= levelH)
			baseCamera.y = (levelH - m_ScreenHeight);

		glTranslatef(-baseCamera.x, -baseCamera.y, 0);
	}
	if (cameraState == CameraState::FreeY)
	{
		Vector2f baseCamera{ trackCenter.x - m_ScreenWidth / 2, trackCenter.y - m_ScreenHeight / 2 };
		if (baseCamera.x <= 0)
			baseCamera.x = 0;

		if ((baseCamera.x + m_ScreenWidth) >= levelW)
			baseCamera.x = (levelW - m_ScreenWidth);

		if (baseCamera.y <= 0)
			baseCamera.y = 0;

		if (baseCamera.y > (520 - m_ScreenHeight / 2))
			baseCamera.y = 520 - m_ScreenHeight / 2;

		glTranslatef(-baseCamera.x, -baseCamera.y, 0);
	}
}

void Camera::Reset()
{
	glPopMatrix();
}
