#pragma once
class Camera
{
public:
	Camera(float ScreenWidth, float ScreenHeight, Point2f StartPos);
	void Aim(Point2f trackCenter);
	void Reset();

private:
	float m_ScreenWidth;
	float m_ScreenHeight;
	Point2f m_CameraPos;
};

