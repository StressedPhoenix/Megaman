#include "pch.h"
#include "Background.h"
#include "Texture.h"

Background::Background()
	:m_BackgroundTexturePtr{ nullptr }
{
	m_BackgroundTexturePtr = new Texture{ "Level/Background.png" };
}

Background::~Background()
{
	delete m_BackgroundTexturePtr;
	m_BackgroundTexturePtr = nullptr;
}

void Background::Draw(Vector2f playerPos) const
{
	Vector2f scrollSpeed{0.5, 0.3};

	glPushMatrix();

	float paralax = (scrollSpeed.x * playerPos.x) - (m_BackgroundTexturePtr->GetWidth() / 12);

	glTranslatef(paralax, -m_BackgroundTexturePtr->GetHeight() - 40, 0);
	glScalef(3.9f, 3.9f, 0.f);

	m_BackgroundTexturePtr->Draw();

	glPopMatrix();
}