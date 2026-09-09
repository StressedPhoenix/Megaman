#pragma once
#include "BaseGame.h"
#include <vector>
class SoundStream;
class SoundEffect;
class Texture;
class Level;
class Camera;
class Player;
class BulletManager;
class EnemyManager;
class MainMenu;
class GUI;

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:

	// ENUM CLASSES
	enum class GameState
	{
		Menu,
		Pause,
		Play,
		Win
	};

	// FUNCTIONS
	void Initialize();
	void Cleanup();
	void ClearBackground() const;
	void ResetLevel();
	void ResetGame();

	// DATAMEMBERS
	Level* m_LevelPtr{ nullptr };
	Camera* m_CameraPtr{ nullptr };
	Player* m_PlayerPtr{ nullptr };
	GameState m_GameState{ GameState::Menu };
	MainMenu* m_MainMenuPtr{ nullptr };
	BulletManager* m_BulletManagerPtr{ nullptr };
	EnemyManager* m_EnemyManagerPtr{ nullptr };
	GUI* m_GUIPtr{ nullptr };

	float m_TickCounter{0};
	int m_Volume{ 100 };
	float m_CurrentFrame{ 0 };

	Texture* m_PausedTextPtr{ nullptr };
	Texture* m_ReadyTextPtr{ nullptr };
	Texture* m_WinTextPtr{ nullptr };
};