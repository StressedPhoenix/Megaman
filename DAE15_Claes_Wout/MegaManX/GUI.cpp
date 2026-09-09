#include "pch.h"
#include "GUI.h"
#include "Texture.h"

GUI::GUI()
{
	m_HealthBarTexturePtr = new Texture{ "GUI/HealthBar.png" };
	m_HealthBarBitTexturePtr = new Texture{ "GUI/HealthBit.png" };
}

GUI::~GUI()
{
	delete m_HealthBarBitTexturePtr;
	m_HealthBarBitTexturePtr = nullptr;

	delete m_HealthBarTexturePtr;
	m_HealthBarTexturePtr = nullptr;
}

void GUI::Draw(int health) const
{
	float scale{ 3 };
	glPushMatrix();
	{
		glTranslatef(25, 450, 0.f);
		glScalef(scale, scale, 1.f);
		m_HealthBarTexturePtr->Draw();

		glTranslatef(4.f, 17.f, 0.f);

		for (int idx{ 0 }; idx < health; ++idx)
		{
			m_HealthBarBitTexturePtr->Draw();
			glTranslatef(0.f, m_HealthBarBitTexturePtr->GetHeight() * 2, 0.f);
		}
	}
	glPopMatrix();
}
