#pragma once
class PickUp
{
public:

	enum class ID
	{
		InnerEye
	};
	virtual void Draw() const = 0;
	virtual void Update(const Rectf& playerHitBox) = 0;
	virtual bool IsPickedUp() const;
	virtual ID GetID() const = 0;
	ID m_ID;

protected:
	bool m_PickedUp{false};
};

