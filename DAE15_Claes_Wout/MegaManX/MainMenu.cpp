#include "pch.h"
#include "MainMenu.h"
#include "Texture.h"
#include "SoundEffect.h"
#include "SoundStream.h"
#include "BulletManager.h"

MainMenu::MainMenu(BulletManager* bulletManager, float windowWidth, float windowHeight)
	:m_BulletManagerPtr{bulletManager}
{
	// SPRITES
	//0
	m_MenuTexturesPtr.push_back(new Texture{ "Main_Menu/Main_Logo.png" });
	//1
	m_MenuTexturesPtr.push_back(new Texture{ "Main_Menu/Start_Text.png" });
	//2
	m_MenuTexturesPtr.push_back(new Texture{ "Main_Menu/Password_Text.png" });
	//3
	m_MenuTexturesPtr.push_back(new Texture{ "Main_Menu/Options_Text.png" });
	//4
	m_MenuTexturesPtr.push_back(new Texture{ "x/x_Base.png" });
	//5
	m_MenuTexturesPtr.push_back(new Texture{ "X/XBullet_Medium.png" });

	// DATA
	m_LogoPos = Vector2f{ windowWidth / 2 - m_MenuTexturesPtr[0]->GetWidth() * m_Scaling.x / 2, windowHeight - m_MenuTexturesPtr[0]->GetHeight() * m_Scaling.y - 25.f };
	m_StartTextPos = Vector2f{ windowWidth / 2 - m_MenuTexturesPtr[1]->GetWidth() * m_Scaling.x / 2, 225.f };
	m_PaswordTextPos = Vector2f{ m_StartTextPos.x,  170.f };
	m_OptionsTextPos = Vector2f{ m_StartTextPos.x,  115.f };
	m_PlayerCharacterPos = Vector2f{ m_StartTextPos.x - 200, m_StartTextPos.y - (m_MenuTexturesPtr[4]->GetHeight() / 2) };

	// SOUNDEFFECTS
	//0
	m_MenuSoundEffectPtr = new SoundEffect{ "Sound/X/Charge_Shot.wav" };

	// MUSIC
	m_MenuMusicPtr = new SoundStream{ "Sound/Music/Main_Menu_Music.mp3" };
	if(m_MenuMusicPtr)
	{
		m_MenuMusicPtr->Play(true);
	}
}

MainMenu::~MainMenu()
{
	delete m_MenuMusicPtr;
	m_MenuMusicPtr = nullptr;
	
	delete m_MenuSoundEffectPtr;
	m_MenuSoundEffectPtr = nullptr;

	for (int idx{ 0 }; idx < m_MenuTexturesPtr.size(); ++idx)
	{
		delete m_MenuTexturesPtr[idx];
		m_MenuTexturesPtr[idx] = nullptr;
	}
	m_MenuTexturesPtr.clear();
}

void MainMenu::Update(float elapsedSec)
{
	if(m_StartSelected)
	{
		m_Timer += 1 * elapsedSec;
	}
	if (m_Timer >= 2)
	{
		m_StartGame = true;
	}
}

void MainMenu::Draw() const
{
	// Menu Items
	glPushMatrix();
	{
		glScalef(m_Scaling.x ,m_Scaling.y, 0);

		m_MenuTexturesPtr[0]->Draw(Vector2f{m_LogoPos.x / m_Scaling.x, m_LogoPos.y / m_Scaling.y });

		m_MenuTexturesPtr[1]->Draw(Vector2f{m_StartTextPos.x / m_Scaling.x, m_StartTextPos.y / m_Scaling.y });

		m_MenuTexturesPtr[2]->Draw(Vector2f{m_PaswordTextPos.x / m_Scaling.x, m_PaswordTextPos.y / m_Scaling.y });

		m_MenuTexturesPtr[3]->Draw(Vector2f{m_OptionsTextPos.x / m_Scaling.x, m_OptionsTextPos.y / m_Scaling.y });
	}
	glPopMatrix();

	// X
	Rectf drawBox{ (m_MenuTexturesPtr[4]->GetWidth() / 2) * m_StartSelected, 0, m_MenuTexturesPtr[4]->GetWidth() / 2 ,m_MenuTexturesPtr[4]->GetHeight()};
	m_MenuTexturesPtr[4]->Draw(m_PlayerCharacterPos, drawBox);
}

bool MainMenu::GetStartGame() const
{
	return m_StartGame;
}

void MainMenu::SetVolume(const int Volume)
{
	if (m_MenuMusicPtr != nullptr)
	{
		m_MenuMusicPtr->SetVolume(Volume);
	}
}

void MainMenu::ShootSelect()
{
	m_MenuSoundEffectPtr->Play(false);
	Vector2f shootPos{ m_PlayerCharacterPos.x, m_PlayerCharacterPos.y + (m_MenuTexturesPtr[4]->GetHeight() / 2) - 25};
	m_BulletManagerPtr->Shoot(shootPos, true, BulletManager::BulletID::XBullet, XBullet::ChargeLevel::HalfCharge);
	m_StartSelected = true;
}

void MainMenu::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	int buttonNr{ static_cast<int>(m_SelectedButton) };

	switch (e.keysym.sym)
	{
	case SDLK_UP:
		--buttonNr;
		break;

	case SDLK_DOWN:
		++buttonNr;
		break;

	case SDLK_SPACE:

		switch (m_SelectedButton)
		{
		case SelectedButton::Start:
			ShootSelect();
			break;
		case SelectedButton::Password:
			//nothing
			break;
		case SelectedButton::Options:
			//nothing
			break;
		}
		break;
	}

	buttonNr += 3;
	m_SelectedButton = static_cast<SelectedButton>(buttonNr % 3);

	switch (m_SelectedButton)
	{
	case MainMenu::SelectedButton::Start:
		m_PlayerCharacterPos = Vector2f{ m_StartTextPos.x - 200, m_StartTextPos.y - (m_MenuTexturesPtr[4]->GetHeight() / 2) };
		break;
	case MainMenu::SelectedButton::Password:
		m_PlayerCharacterPos = Vector2f{ m_StartTextPos.x - 200, m_PaswordTextPos.y - (m_MenuTexturesPtr[4]->GetHeight() / 2) };
		break;
	case MainMenu::SelectedButton::Options:
		m_PlayerCharacterPos = Vector2f{ m_StartTextPos.x - 200, m_OptionsTextPos.y - (m_MenuTexturesPtr[4]->GetHeight() / 2) };
		break;
	}
}