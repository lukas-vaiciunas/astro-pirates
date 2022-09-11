#pragma once

#include "Enemy.h"
#include "DurationClock.h"

class Minion : public Enemy
{
public:
	Minion(
		uint16_t id,
		float x, float y,
		float speed,
		float maxHealth,
		float distanceIdle,
		float distanceApproach,
		float distanceStationary,
		float distanceRetreat,
		float shootingCooldownSecs,
		const sf::Texture &texture);

	void update(
		float deltaTime,
		BulletPool &bulletPool,
		ParticlePool &particlePool,
		const DestructibleEntity &target) override;

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	Minion *clone(float x, float y) const override;
private:
	enum class State : uint8_t
	{
		None,
		Idle,
		Approach,
		Stationary,
		Retreat
	};

	State state_;

	DurationClock shootingCooldownClock_;

	float speed_;

	float distanceIdle_;
	float distanceApproach_;
	float distanceStationary_;
	float distanceRetreat_;

	float velX_;
	float velY_;

	float angleRad_;
	float angleDeg_;

	void updateMovement_(float deltaTime);
	void updateShooting_(float deltaTime, BulletPool &bulletPool);
	void updateAngle_(float dX, float dY);
	void setState_(const State &state);
};