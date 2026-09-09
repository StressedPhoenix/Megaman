#pragma once
#include "BaseGame.h"
#include "Player.h"
#include "Map.h"
#include "utils.h"
#include "Texture.h"
#include "Camera.h"
#include "Fly.h"
#include "SoundStream.h"
#include "UI.h"
#include "PickUp.h"
#include "InnerEye.h"

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

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	// DATAMEMBERS
	
	Player* m_Isaac;
	Map* m_Map;
	Camera* m_Camera;
	SoundStream* m_Music;
	UI* m_UI;
	std::vector <PickUp*> m_PickUpVctr;
};