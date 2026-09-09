#pragma once
#include "PickUp.h"
#include "Texture.h"

class InnerEye : public PickUp
{
public:

	InnerEye(Point2f SpawnPos);
	virtual ~InnerEye();
	virtual void Draw() const override;
	virtual void Update(const Rectf& playerHitBox) override;
	virtual PickUp::ID GetID() const override;

	InnerEye(const InnerEye& other) = delete;
	InnerEye& operator=(const InnerEye& rhs) = delete;
	InnerEye(InnerEye&& rhs) = delete;
	InnerEye& operator=(InnerEye&& rhs) = delete;

private:
	Texture* m_InnerEyePickUpSritePtr;
	Point2f m_Position;
};
