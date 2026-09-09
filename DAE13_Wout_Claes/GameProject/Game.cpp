#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:BaseGame{ window }
{
	Initialize();
}

Game::~Game( )
{
	Cleanup();
}

void Game::Initialize()
{
	m_Map = new Map();
	m_UI = new UI();
	m_Camera = new Camera(GetViewPort().width, GetViewPort().height, m_Map->SpawnLocation());
	m_Isaac = new Player{m_Map->SpawnLocation()};
	m_Music = new SoundStream("Background_Music.mp3");
	if (m_Music->IsLoaded())
	{
		m_Music->Play(true);
	}
	m_PickUpVctr.push_back(new InnerEye{ m_Map->GetMiddelRewardRoom() });
}

void Game::Cleanup( )
{
	m_PickUpVctr.clear();
	delete m_Music;
	m_Music = nullptr;
	delete m_Isaac;
	m_Isaac = nullptr;
	delete m_Camera;
	m_Camera = nullptr;
	delete m_UI;
	m_UI = nullptr;
	delete m_Map;
	m_Map = nullptr;
}

void Game::Update( float elapsedSec )
{
	m_Isaac->Update(elapsedSec, m_Map->GetHorizontalRect(m_Isaac->GetPlayerPos()), m_Map->GetVerticalRect(m_Isaac->GetPlayerPos()), m_PickUpVctr, m_Map->GetEnemyVctr(m_Isaac->GetPlayerPos()));
	m_Map->update(m_Isaac->GetPlayerPos(), elapsedSec, m_Isaac->GetPlayerHitbox(), m_Isaac->GetBulletPtrVctr());
	for (PickUp* PickUp : m_PickUpVctr)
	{
		PickUp->Update(m_Isaac->GetPlayerHitbox());
	}
}

void Game::Draw( ) const
{
	ClearBackground();
	
	m_Camera->Aim(m_Map->GetRoom(m_Isaac->GetPlayerPos()));
	m_Map->Draw();
	m_Isaac->Draw(m_PickUpVctr);
	for (const PickUp* PickUp : m_PickUpVctr)
	{
		PickUp->Draw();
	}
	m_Camera->Reset();
	m_UI->Draw(m_Map, m_Isaac->GetPlayerHealth());
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_Isaac->ProcessKeyDownEvent(e);
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{

}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.f, 0.f, 0.f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}