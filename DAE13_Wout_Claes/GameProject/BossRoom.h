#pragma once
#include "Room.h"
#include "Texture.h"

class BossRoom : public Room
{
public:

	BossRoom(const Point2f& Pos, const bool& Up, const bool& Right, const bool& Down, const bool& Left, const bool& Enemies);
	virtual ~BossRoom();
	virtual void Draw() override;
	virtual void Update(float elapsedSec);

	BossRoom(const BossRoom& other) = delete;
	BossRoom& operator=(const BossRoom& rhs) = delete;
	BossRoom(BossRoom&& rhs) = delete;
	BossRoom& operator=(BossRoom&& rhs) = delete;

private:

	Texture* m_BossRoomTexture;
	Texture* m_BossInDoorTexture;
	Texture* m_BossOutDoorTexture;
};