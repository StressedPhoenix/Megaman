#pragma once
#include <vector>
class Texture;
class SoundEffect;
class SoundStream;
class BulletManager;

class MainMenu final
{
public:

	explicit MainMenu(BulletManager* bulletManager, float windowWidth, float windowHeight);
	~MainMenu();

	void Update(float elapsedSec);
	void Draw() const;
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);

	bool GetStartGame() const;

	virtual void SetVolume(const int Volume);

	// RULE OF FIVE
	MainMenu(const MainMenu& other) = delete;
	MainMenu& operator=(const MainMenu& rhs) = delete;
	MainMenu(MainMenu&& rhs) = delete;
	MainMenu& operator=(MainMenu&& rhs) = delete;

private:
	// ENUM CLASSES
	enum class SelectedButton
	{
		Start = 0,
		Password = 1,
		Options = 2
	};
	// FUNCTIONS
	void ShootSelect();

	// DATAMEMBERS
	std::vector<Texture*> m_MenuTexturesPtr;
	SoundStream* m_MenuMusicPtr;
	SoundEffect* m_MenuSoundEffectPtr;
	SelectedButton m_SelectedButton{ SelectedButton::Start };
	bool m_StartGame{ false };
	bool m_StartSelected{ false };
	Vector2f m_PlayerCharacterPos;
	BulletManager* m_BulletManagerPtr;
	float m_Timer{ 0.f };

	Vector2f m_Scaling{ 3,3 };
	Vector2f m_LogoPos;
	Vector2f m_StartTextPos;
	Vector2f m_PaswordTextPos;
	Vector2f m_OptionsTextPos;
};

