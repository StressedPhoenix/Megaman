#pragma once
#include "Room.h"
#include "Texture.h"

class RewardRoom : public Room
{
public:

	RewardRoom(const Point2f& Pos, const bool& Up, const bool& Right, const bool& Down, const bool& Left, const bool& Enemies);
	virtual ~RewardRoom();
	virtual void Draw() override;
	virtual void Update(float elapsedSec);

	RewardRoom(const RewardRoom& other) = delete;
	RewardRoom& operator=(const RewardRoom& rhs) = delete;
	RewardRoom(RewardRoom&& rhs) = delete;
	RewardRoom& operator=(RewardRoom&& rhs) = delete;

private:

	Texture* m_RewardRoomTexture;
	Texture* m_RewardInDoorTexture;
};