#pragma once

#include "Entity.h"
#include "DurationClock.h"

class Bullet : public Entity
{
public:
	Bullet(
		float x, float y,
		float velX, float velY,
		float damage,
		float durationSecs,
		bool isFromPlayer,
		const sf::Texture &texture);

	void update(float deltaTime);

	void kill();

	float getDamage() const;
	bool isFromPlayer() const;
	bool isLive() const;
private:
	DurationClock durationClock_;
	float velX_;
	float velY_;
	float damage_;
	bool isFromPlayer_;
	bool isLive_;
};