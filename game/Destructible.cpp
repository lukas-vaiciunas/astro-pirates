#include "Destructible.h"

Destructible::Destructible(float maxHealth) :
	maxHealth_(maxHealth),
	health_(maxHealth),
	isLive_(true)
{}

void Destructible::hurt(float damage)
{
	health_ -= damage;

	if (health_ <= 0.0f)
	{
		health_ = 0.0f;
		isLive_ = false;
	}
}

bool Destructible::isLive() const
{
	return isLive_;
}