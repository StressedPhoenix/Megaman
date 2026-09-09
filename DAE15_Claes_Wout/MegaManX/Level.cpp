#include "pch.h"
#include "Level.h"
#include "Background.h"
#include "Texture.h"
#include "SoundStream.h"
#include "BossPlatform.h"

Level::Level()
	:m_LevelTexturePtr{nullptr}
	,m_BackgroundPtr{ nullptr }
{
	m_LevelTexturePtr = new Texture{ "Level/IntroStage.png" };

	m_BackgroundPtr = new Background{};

	PushHitBoxes();

	// Boss Platforms
	std::vector<Vector2f> temp{};

	temp.push_back(Vector2f{ 11510,300 });
	temp.push_back(Vector2f{ 12550,300 });
	temp.push_back(Vector2f{ 11510,500 });
	temp.push_back(Vector2f{ 12550,500 });

	m_BossPlatform = new BossPlatform{ temp };

	temp.clear();

	//Music
	m_MusicPtr = new SoundStream{ "Sound/Music/Opening_Stage_Music.mp3" };
}

Level::~Level()
{
	delete m_BossPlatform;
	m_BossPlatform = nullptr;

	delete m_MusicPtr;
	m_MusicPtr = nullptr;

	delete m_LevelTexturePtr;
	m_LevelTexturePtr = nullptr;

	delete m_BackgroundPtr;
	m_BackgroundPtr = nullptr;

	PopHitBoxes();
}

void Level::Draw(Vector2f playerPos) const
{
	// Background
	m_BackgroundPtr->Draw(playerPos);

	// Boss Platform
	m_BossPlatform->Draw();

	// Actual level
	glPushMatrix();
	{
		glTranslatef(-20, -m_LevelTexturePtr->GetHeight() * 2, 0);
		glScalef(m_Scale.x, m_Scale.y, 1);

		m_LevelTexturePtr->Draw(Vector2f{ 0.f, 0.f });
	}
	glPopMatrix();
}

void Level::Update(float elapsedSec, bool bossDead)
{
	m_BossPlatform->Update(elapsedSec, bossDead);

	if(!m_MusicPlaying)
	{
		m_MusicPtr->Stop();
		if (m_MusicPtr)
		{
			m_MusicPtr->Play(true);
		}
		m_MusicPlaying = true;
	}
}

float Level::GetWidth() const
{
	return m_LevelTexturePtr->GetWidth() * m_Scale.x;
}

float Level::GetHeight() const
{
	return m_LevelTexturePtr->GetHeight() * m_Scale.y;
}

const std::vector<std::vector<Vector2f>> Level::GetMapHitBoxes() const
{
	std::vector<std::vector<Vector2f>> temp{ m_MapHitBoxes };

	temp.push_back(m_BossPlatform->GetHitBox());

	return temp;
}

void Level::SetVolume(const int Volume)
{
	if (m_MusicPtr != nullptr)
	{
		m_MusicPtr->SetVolume(Volume);
	}
}

Vector2f Level::GetFirstBossAreaX() const
{

	return Vector2f{11500.f, 12500.f};
}

Vector2f Level::GetSecondBossAreaX() const
{
	return Vector2f{11500.f, 12500.f};
}

void Level::PushHitBoxes()
{
	std::vector<Vector2f> temp{};
	temp.reserve(40);

	// FIRST POLYGON
	temp.push_back(Vector2f{ 2,950 });
	temp.push_back(Vector2f{ 217, 958 });
	temp.push_back(Vector2f{ 217, 431 });
	temp.push_back(Vector2f{ 3606, 431 });
	temp.push_back(Vector2f{ 3606, 250 });
	temp.push_back(Vector2f{ 3453, 250 });
	temp.push_back(Vector2f{ 3453, 42 });
	temp.push_back(Vector2f{ -3, 42 });
	m_MapHitBoxes.push_back(temp);
	temp.clear();

	// SECOND POLYGON
	temp.push_back(Vector2f{ 3744, 377 });
	temp.push_back(Vector2f{ 3744, 564 });
	temp.push_back(Vector2f{ 5909, 564 });
	temp.push_back(Vector2f{ 5909, 373 });
	temp.push_back(Vector2f{ 5763, 373 });
	temp.push_back(Vector2f{ 5763, 22 });
	temp.push_back(Vector2f{ 3886, 22 });
	temp.push_back(Vector2f{ 3886, 376 });
	m_MapHitBoxes.push_back(temp);
	temp.clear();

	// THIRD POLYGON
	temp.push_back(Vector2f{ 6044,494 });
	temp.push_back(Vector2f{ 6044,312 });
	temp.push_back(Vector2f{ 6190,312 });
	temp.push_back(Vector2f{ 6190,44 });
	temp.push_back(Vector2f{ 6333,44 });
	temp.push_back(Vector2f{ 6333,303 });
	temp.push_back(Vector2f{ 6763,303 });
	temp.push_back(Vector2f{ 6763,44 });
	temp.push_back(Vector2f{ 6913,44 });
	temp.push_back(Vector2f{ 6913,308 });
	temp.push_back(Vector2f{ 7339,308 });
	temp.push_back(Vector2f{ 7339,45 });
	temp.push_back(Vector2f{ 7488,45 });
	temp.push_back(Vector2f{ 7488,312 });
	temp.push_back(Vector2f{ 7916,312 });
	temp.push_back(Vector2f{ 7916,45 });
	temp.push_back(Vector2f{ 8066,45 });
	temp.push_back(Vector2f{ 8062,312 });
	temp.push_back(Vector2f{ 8497,312 });
	temp.push_back(Vector2f{ 8497,42 });
	temp.push_back(Vector2f{ 8641,42 });
	temp.push_back(Vector2f{ 8641,310 });
	temp.push_back(Vector2f{ 9071,310 });
	temp.push_back(Vector2f{ 9071,48 });
	temp.push_back(Vector2f{ 9218,48 });
	temp.push_back(Vector2f{ 9211,309 });
	temp.push_back(Vector2f{ 9652,309 });
	temp.push_back(Vector2f{ 9652,47 });
	temp.push_back(Vector2f{ 9789,47 });
	temp.push_back(Vector2f{ 9789,310 });
	temp.push_back(Vector2f{ 10225,310 });
	temp.push_back(Vector2f{ 10225,47 });
	temp.push_back(Vector2f{ 10373,47 });
	temp.push_back(Vector2f{ 10370,313 });
	temp.push_back(Vector2f{ 10503,313 });
	temp.push_back(Vector2f{ 10503,492 });
	m_MapHitBoxes.push_back(temp);
	temp.clear();


	// FOURTH POLYGON
	temp.push_back(Vector2f{ 10730, 321 });
	temp.push_back(Vector2f{ 10730, 504 });
	temp.push_back(Vector2f{ 11519, 498 });
	temp.push_back(Vector2f{ 11519, -604 });
	temp.push_back(Vector2f{ 11595, -604 });
	temp.push_back(Vector2f{ 11595, -416 });
	temp.push_back(Vector2f{ 12456, -425 });
	temp.push_back(Vector2f{ 12456, -610 });
	temp.push_back(Vector2f{ 12528, -610 });
	temp.push_back(Vector2f{ 12528, 504 });
	temp.push_back(Vector2f{ 13024, 491 });
	temp.push_back(Vector2f{ 13024, 312 });
	temp.push_back(Vector2f{ 12672, 312 });
	temp.push_back(Vector2f{ 12672, -613 });
	temp.push_back(Vector2f{ 12808, -613 });
	temp.push_back(Vector2f{ 12808, -942 });
	temp.push_back(Vector2f{ 12393, -942 });
	temp.push_back(Vector2f{ 12384, -611 });
	temp.push_back(Vector2f{ 11665, -611 });
	temp.push_back(Vector2f{ 11665, -933 });
	temp.push_back(Vector2f{ 11229, -933 });
	temp.push_back(Vector2f{ 11232, -614 });
	temp.push_back(Vector2f{ 11375, -614 });
	temp.push_back(Vector2f{ 11375, 313 });
	temp.push_back(Vector2f{ 10945, 313 });
	temp.push_back(Vector2f{ 10945, 45 });
	temp.push_back(Vector2f{ 10797, 45 });
	temp.push_back(Vector2f{ 10797, 317 });
	m_MapHitBoxes.push_back(temp);
	temp.clear();

	// FIFTH POLYGON
	temp.push_back(Vector2f{ 13241, 367 });
	temp.push_back(Vector2f{ 13241, 183 });
	temp.push_back(Vector2f{ 13101, 171 });
	temp.push_back(Vector2f{ 13101, -608 });
	temp.push_back(Vector2f{ 12958, -608 });
	temp.push_back(Vector2f{ 12958, -929 });
	temp.push_back(Vector2f{ 13381, -929 });
	temp.push_back(Vector2f{ 13381, -615 });
	temp.push_back(Vector2f{ 13381, -615 });
	temp.push_back(Vector2f{ 13246, -615 });
	temp.push_back(Vector2f{ 13246, 168 });
	temp.push_back(Vector2f{ 13677, 168 });
	temp.push_back(Vector2f{ 13677, -601 });
	temp.push_back(Vector2f{ 13540, -601 });
	temp.push_back(Vector2f{ 13540, -931 });
	temp.push_back(Vector2f{ 13966, -931 });
	temp.push_back(Vector2f{ 13966, -619 });
	temp.push_back(Vector2f{ 13820, -600 });
	temp.push_back(Vector2f{ 13820, 180 });
	temp.push_back(Vector2f{ 14252, 180 });
	temp.push_back(Vector2f{ 14252, -596 });
	temp.push_back(Vector2f{ 14107, -613 });
	temp.push_back(Vector2f{ 14107, -932 });
	temp.push_back(Vector2f{ 14541, -932 });
	temp.push_back(Vector2f{ 14541, -610 });
	temp.push_back(Vector2f{ 15253, -610 });
	temp.push_back(Vector2f{ 15268, -934 });
	temp.push_back(Vector2f{ 15692, -934 });
	temp.push_back(Vector2f{ 15692, -611 });
	temp.push_back(Vector2f{ 15556, -611 });
	temp.push_back(Vector2f{ 15556, 181 });
	temp.push_back(Vector2f{ 15981, 181 });
	temp.push_back(Vector2f{ 15981, 42 });
	temp.push_back(Vector2f{ 16125, 42 });
	temp.push_back(Vector2f{ 16125, 184 });
	temp.push_back(Vector2f{ 16555, 184 });
	temp.push_back(Vector2f{ 16555, 40 });
	temp.push_back(Vector2f{ 16703, 40 });
	temp.push_back(Vector2f{ 16703, 363 });
	temp.push_back(Vector2f{ 15397, 363 });
	temp.push_back(Vector2f{ 15406, -593 });
	temp.push_back(Vector2f{ 15335, -593 });
	temp.push_back(Vector2f{ 15335, -416 });
	temp.push_back(Vector2f{ 14462, -416 });
	temp.push_back(Vector2f{ 14462, -598 });
	temp.push_back(Vector2f{ 14398, -598 });
	temp.push_back(Vector2f{ 14398, 375 });
	m_MapHitBoxes.push_back(temp);
	temp.clear();

	//SIXTH POLYGON
	temp.push_back(Vector2f{ 15410, 367 });
	temp.push_back(Vector2f{ 15410, 100 });
	temp.push_back(Vector2f{ 14400, 100 });
	temp.push_back(Vector2f{ 14400, 367 });
	m_MapHitBoxes.push_back(temp);
	temp.clear();
}

void Level::PopHitBoxes()
{
	m_MapHitBoxes.clear();
}
