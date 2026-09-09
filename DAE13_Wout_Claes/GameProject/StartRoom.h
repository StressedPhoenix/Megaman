#pragma once
#include "Room.h"
#include "Texture.h"

class StartRoom : public Room 
{
public:

	StartRoom(const Point2f& Pos, const bool& Up, const bool& Right, const bool& Down, const bool& Left, const bool& Enemies);
	virtual ~StartRoom();
	virtual void Draw() override;
	virtual void Update(float elapsedSec);

	StartRoom(const StartRoom& other) = delete;
	StartRoom& operator=(const StartRoom& rhs) = delete;
	StartRoom(StartRoom&& rhs) = delete;
	StartRoom& operator=(StartRoom&& rhs) = delete;

private:

	Texture* m_StartRoomTexture;
	Texture* m_BaseDoorTexture;
};

