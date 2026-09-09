#include "pch.h"
#include "Game.h"
#include "Level.h"
#include "Camera.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "MainMenu.h"
#include "GUI.h"
#include "SoundStream.h"
#include "SoundEffect.h"
#include "Texture.h"

Game::Game( const Window& window )
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize( )
{
	// Level
	m_LevelPtr = new Level{};

	// Bullets
	m_BulletManagerPtr = new BulletManager{};

	// Camera
	m_CameraPtr = new Camera{ GetViewPort().width, GetViewPort().height };

	// Player
	m_PlayerPtr = new Player{ Vector2f{ 500.f, 500.f}, m_BulletManagerPtr };

	// Bullet Player Link
	m_BulletManagerPtr->SetPlayerPtr(m_PlayerPtr);

	// Enemies
	m_EnemyManagerPtr = new EnemyManager{ m_BulletManagerPtr , m_PlayerPtr};

	// Bullet Enemy Link
	m_BulletManagerPtr->SetEnemyManagerPtr(m_EnemyManagerPtr);

	// Main Menu
	m_MainMenuPtr = new MainMenu{ m_BulletManagerPtr,GetViewPort().width, GetViewPort().height };

	// GUI
	m_GUIPtr = new GUI{};

	// Paused Text
	m_PausedTextPtr = new Texture{ "Extra/Paused.png" };

	// Ready Text
	m_ReadyTextPtr = new Texture{ "Extra/Ready.png" };

	// Win Text
	m_WinTextPtr = new Texture{ "Extra/Win.png" };

	// Volume
	m_MainMenuPtr->SetVolume(m_Volume);
	m_LevelPtr->SetVolume(m_Volume);
	m_BulletManagerPtr->SetVolume(m_Volume);
	m_PlayerPtr->SetVolume(m_Volume);
	m_EnemyManagerPtr->SetVolume(m_Volume);
}

void Game::Cleanup( )
{
	// Win Text
	delete m_WinTextPtr;
	m_WinTextPtr = nullptr;

	// Ready Text
	delete m_ReadyTextPtr;
	m_ReadyTextPtr = nullptr;

	// PausedText
	delete m_PausedTextPtr;
	m_PausedTextPtr = nullptr;

	//GUI
	delete m_GUIPtr;
	m_GUIPtr = nullptr;

	//Main Menu
	delete m_MainMenuPtr;
	m_MainMenuPtr = nullptr;

	//Enemies
	delete m_EnemyManagerPtr;
	m_EnemyManagerPtr = nullptr;

	// Player
	delete m_PlayerPtr;
	m_PlayerPtr = nullptr;

	// Camera
	delete m_CameraPtr;
	m_CameraPtr = nullptr;

	// Bullets
	delete m_BulletManagerPtr;
	m_BulletManagerPtr = nullptr;

	// Level
	delete m_LevelPtr;
	m_LevelPtr = nullptr;
}

void Game::Update(float elapsedSec)
{
	//Make sure the volume is correct
	m_MainMenuPtr->SetVolume(m_Volume);
	m_LevelPtr->SetVolume(m_Volume);
	m_BulletManagerPtr->SetVolume(m_Volume);
	m_PlayerPtr->SetVolume(m_Volume);
	m_EnemyManagerPtr->SetVolume(m_Volume);

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	if (m_GameState == GameState::Menu)
	{
		std::vector<Rectf> tempRect{};
		tempRect.push_back(Rectf{ 0,0,0,0 });

		std::vector<std::vector<Vector2f>> tempVector{};
		std::vector<Vector2f> temp{};
		temp.push_back(Vector2f{ 0,0 });
		tempVector.push_back(temp);

		m_BulletManagerPtr->Update(elapsedSec, tempRect, tempVector);

		m_MainMenuPtr->Update(elapsedSec);
	}

	if(m_GameState == GameState::Play || m_GameState == GameState::Win)
	{
		// Data
		if(m_CurrentFrame <= 11)
		{
			m_CurrentFrame += 20 * elapsedSec;
		}

		// Level
		m_LevelPtr->Update(elapsedSec, m_EnemyManagerPtr->GetBossDead());

		// Enemies
		m_EnemyManagerPtr->Update(elapsedSec, m_BulletManagerPtr->GetBulletHitBoxes(), m_LevelPtr->GetMapHitBoxes());

		//Player
		m_PlayerPtr->Update(elapsedSec, pStates, m_LevelPtr->GetMapHitBoxes());

		// Bullets
		m_BulletManagerPtr->Update(elapsedSec, m_EnemyManagerPtr->GetEnemyHitBoxes(), m_LevelPtr->GetMapHitBoxes());

		// Reset
		if (m_PlayerPtr->GetPosition().y <= -200)
		{
			ResetLevel();
		}
		if (m_PlayerPtr->GetPlayerHealth() <= 0)
		{
			ResetLevel();
		}
	}

	if (m_MainMenuPtr->GetStartGame() && m_GameState == GameState::Menu)
	{
		m_GameState = GameState::Play;
	}

	if (m_EnemyManagerPtr->GetFinalBossDead())
	{
		m_GameState = GameState::Win;
	}
}

void Game::Draw() const
{
	ClearBackground();
	if (m_GameState == GameState::Menu)
	{
		m_MainMenuPtr->Draw();

		m_BulletManagerPtr->Draw();
	}

	if (m_GameState == GameState::Play || m_GameState == GameState::Pause || m_GameState == GameState::Win)
	{
		bool freeY
		{
			(m_PlayerPtr->GetPosition().x > m_LevelPtr->GetFirstBossAreaX().x &&
			m_PlayerPtr->GetPosition().x < m_LevelPtr->GetFirstBossAreaX().y) ||
			(m_PlayerPtr->GetPosition().x > m_LevelPtr->GetSecondBossAreaX().x &&
			m_PlayerPtr->GetPosition().x < m_LevelPtr->GetSecondBossAreaX().y)
		};

		m_CameraPtr->Aim(m_LevelPtr->GetWidth(), m_LevelPtr->GetHeight(), Vector2f{ m_PlayerPtr->GetPosition().x + 20, m_PlayerPtr->GetPosition().y}, freeY);
		{
			// Level
			m_LevelPtr->Draw(m_PlayerPtr->GetPosition());

			// Enemies
			m_EnemyManagerPtr->Draw();

			// Player
			m_PlayerPtr->Draw();

			// Bullets
			m_BulletManagerPtr->Draw();
		}
		m_CameraPtr->Reset();

		if (!m_PlayerPtr->GetIntroPlayed())
		{
			glPushMatrix();
			{
				glTranslatef((GetViewPort().width / 2) - m_ReadyTextPtr->GetWidth() / 12, (GetViewPort().height / 2) - m_PausedTextPtr->GetHeight() / 2, 0);
				glScalef(5, 5, 0);

				Rectf drawBox{(m_ReadyTextPtr->GetWidth() / 12) * static_cast<int>(m_CurrentFrame), 0, m_ReadyTextPtr->GetWidth() / 12, m_ReadyTextPtr->GetHeight()};
				m_ReadyTextPtr->Draw(Vector2f{0, 0}, drawBox);
			}
			glPopMatrix();
		}

		m_GUIPtr->Draw(m_PlayerPtr->GetPlayerHealth());
	}

	if (m_GameState == GameState::Pause)
	{
		glPushMatrix();
		{
			glTranslatef((GetViewPort().width / 2) - m_PausedTextPtr->GetWidth() * 2, (GetViewPort().height / 2) - m_PausedTextPtr->GetHeight() / 2, 0);
			glScalef(5, 5, 0);

			m_PausedTextPtr->Draw();
		}
		glPopMatrix();
	}
	if (m_GameState == GameState::Win)
	{
		glPushMatrix();
		{
			glTranslatef((GetViewPort().width / 2) - m_WinTextPtr->GetWidth() * 2, (GetViewPort().height / 2) - m_WinTextPtr->GetHeight() / 2, 0);
			glScalef(5, 5, 0);

			m_WinTextPtr->Draw();
		}
		glPopMatrix();
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	switch (e.keysym.sym)
	{
	case SDLK_PAGEUP:
		m_Volume += 5;
		break;
	case SDLK_PAGEDOWN:
		m_Volume -= 5;
		break;
	}

	m_MainMenuPtr->SetVolume(m_Volume);
	m_LevelPtr->SetVolume(m_Volume);
	m_BulletManagerPtr->SetVolume(m_Volume);
	m_PlayerPtr->SetVolume(m_Volume);
	m_EnemyManagerPtr->SetVolume(m_Volume);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	if (m_GameState == GameState::Menu)
	{
		m_MainMenuPtr->ProcessKeyUpEvent(e);
	}
	switch (e.keysym.sym)
	{
	case SDLK_ESCAPE:
		if(m_GameState == GameState::Play)
		{
			m_GameState = GameState::Pause;
		}
		else if (m_GameState == GameState::Pause)
		{
			m_GameState = GameState::Play;
		}
		break;
	case SDLK_BACKSPACE:
		ResetGame();
		break;
	case SDLK_k:
		ResetLevel();
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	if (m_GameState == GameState::Play)
	{
		m_PlayerPtr->ProcessMouseDownEvent(e);
	}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	if (m_GameState == GameState::Play)
	{
		m_PlayerPtr->ProcessMouseUpEvent(e);
	}
}

void Game::ClearBackground() const
{
	// Changing the background color to black
	glClearColor( 0.f, 0.f, 0.f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::ResetLevel()
{
	Cleanup();
	Initialize();
	m_GameState = GameState::Play;
}

void Game::ResetGame()
{
	Cleanup();
	Initialize();
	m_GameState = GameState::Menu;
}