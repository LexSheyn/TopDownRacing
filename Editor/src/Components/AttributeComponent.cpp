#include "../stdafx.h"
#include "AttributeComponent.h"

// Constructors and Destructor:

AttributeComponent::AttributeComponent(const int32 hpMax)
	: HpMax(hpMax), Hp(hpMax)
{
}

AttributeComponent::~AttributeComponent()
{
}


// Functions:

void AttributeComponent::GainHp(const int32 hp)
{
	Hp += hp;

	if (Hp > HpMax)
	{
		Hp = HpMax;
	}
}

void AttributeComponent::LoseHp(const int32 hp)
{
	Hp -= hp;

	if (Hp < 0)
	{
		Hp = 0;
	}
}

void AttributeComponent::Update()
{
}


// Accessors:

const bool AttributeComponent::IsDead() const
{
	return Hp <= 0;
}
