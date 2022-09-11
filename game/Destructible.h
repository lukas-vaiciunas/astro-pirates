#pragma once

class Destructible
{
public:
	Destructible(float maxHealth);
	virtual ~Destructible() {}

	void hurt(float damage);

	bool isLive() const;
protected:
	float maxHealth_;
	float health_;
	bool isLive_;
};