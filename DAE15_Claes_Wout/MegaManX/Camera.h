#pragma once

class Camera final
{
public:

	explicit Camera(const float ScreenWidth, const float ScreenHeight);

	void Aim(const float levelW, const float levelH, const Vector2f& trackCenter, const bool freeY);
	void Reset();

	// RULE OF FIVE
	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& rhs) = delete;
	Camera(Camera&& rhs) = delete;
	Camera& operator=(Camera&& rhs) = delete;

private:

	// ENUM CLASSES

	// FUNCTIONS

	// DATAMEMBERS
	float m_ScreenWidth;
	float m_ScreenHeight;
};

