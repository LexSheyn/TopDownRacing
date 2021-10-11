#pragma once

#include "Base/Component.h"

class AttributeComponent : public Component
{
public:

// Constructors and Destructor:

	AttributeComponent(const int32 hpMax);

	~AttributeComponent();

// Functions:

	void GainHp(const int32 hp);

	void LoseHp(const int32 hp);

	void Update();

// Accessors:

	const bool IsDead() const;

private:

// Variables:

	int32 HpMax;

	int32 Hp;
};

