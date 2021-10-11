#include "../stdafx.h"
#include "Collider.h"

// Constructors and Destructor:

Collider::Collider(sf::RectangleShape& body)
	: Body(body)
{
	Result = 0;

	DeltaX = 0.f;
	DeltaY = 0.f;

	IntersectX = 0.f;
	IntersectY = 0.f;
}

Collider::~Collider()
{
}


// Functions:

void Collider::Move(const float dx, const float dy)
{
	Body.move(dx, dy);
}

int32 Collider::CheckCollision(Collider& other, float push)
{
	// X = 1, Y = 2, No collision = 0;
	Result = 0;

	OtherPosition = other.GetPosition();
	OtherHalfSize = other.GetHalfSize();

	ThisPosition = GetPosition();
	ThisHalfSize = GetHalfSize();

	DeltaX = OtherPosition.x - ThisPosition.x;
	DeltaY = OtherPosition.y - ThisPosition.y;

	IntersectX = std::abs(DeltaX) - (OtherHalfSize.x + ThisHalfSize.x);
	IntersectY = std::abs(DeltaY) - (OtherHalfSize.y + ThisHalfSize.y);

	if (IntersectX < 0.f && IntersectY < 0.f)
	{
		push = std::min(std::max(push, 0.f), 1.f);

	//	if (std::abs(intersectX) < std::abs(intersectY))
		if (IntersectX > IntersectY)
		{
			if (DeltaX > 0.f)
			{
				Move(IntersectX * (1.f - push), 0.f);
				other.Move(-IntersectX * push, 0.f);
			}
			else
			{
				Move(-IntersectX * (1.f - push), 0.f);
				other.Move(IntersectX * push, 0.f);
			}

			Result = 1;
		}
		else
		{
			if (DeltaY > 0.f)
			{
				Move(0.f, IntersectY * (1.f - push));
				other.Move(0.f, -IntersectY * push);
			}
			else
			{
				Move(0.f, -IntersectY * (1.f - push));
				other.Move(0.f, IntersectY * push);
			}

			Result = 2;
		}		
	}

	return Result;
}


// Accessors:

sf::Vector2f Collider::GetPosition()
{
	return Body.getPosition();
}

sf::Vector2f Collider::GetHalfSize()
{
	return Body.getSize() / 2.f;
}
