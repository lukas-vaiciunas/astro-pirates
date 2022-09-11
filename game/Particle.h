#pragma once

#include "Entity.h"
#include "DurationClock.h"

class Particle : public Entity
{
public:
	Particle(
		float x, float y,
		float velX, float velY,
		float velAngleDeg,
		float durationSecs,
		const sf::Texture &texture);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool isLive() const;
private:
	DurationClock durationClock_;
	float velX_;
	float velY_;
	float scale_;
	float velAngleDeg_;
	float angleDeg_;
	bool isLive_;
};