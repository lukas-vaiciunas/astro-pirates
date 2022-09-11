#pragma once

#include "Enemy.h"
#include "DurationClock.h"

class Boss : public Enemy
{
public:
	Boss(
		uint16_t id,
		float x, float y,
		float maxHealth,
		float distanceAggro,
		float shootingCooldownSecs,
		float phaseDurationSecs,
		const sf::Texture &texture);

	void update(
		float deltaTime,
		BulletPool &bulletPool,
		ParticlePool &particlePool,
		const DestructibleEntity &target) override;

	Boss *clone(float x, float y) const override;
private:
	enum class State
	{
		None,
		Idle,
		Circle,
		Target
	};

	State state_;

	DurationClock shootingCooldownClock_;
	DurationClock phaseDurationClock_;

	float distanceAggro_;

	void updateDeaggro_(float sqDistanceToTarget);
};