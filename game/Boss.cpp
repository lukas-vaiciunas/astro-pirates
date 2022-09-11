#include "Boss.h"
#include "BulletPool.h"
#include "ParticlePool.h"
#include "TextureData.h"
#include "AudioData.h"
#include "EventQueue.h"
#include "Event.h"
#include "Constants.h"

Boss::Boss(
	uint16_t id,
	float x, float y,
	float maxHealth,
	float distanceAggro,
	float shootingCooldownSecs,
	float phaseDurationSecs,
	const sf::Texture &texture)
	:
	Enemy(id, x, y, maxHealth, texture),
	state_(State::None),
	shootingCooldownClock_(shootingCooldownSecs),
	phaseDurationClock_(phaseDurationSecs),
	distanceAggro_(distanceAggro)
{
	state_ = State::Idle;
}

void Boss::update(
	float deltaTime,
	BulletPool &bulletPool,
	ParticlePool &particlePool,
	const DestructibleEntity &target)
{
	if (!target.isLive())
		return;

	float dX = (target.getX() + target.getWidth() * 0.5f) - (x_ + width_ * 0.5f);
	float dY = (target.getY() + target.getHeight() * 0.5f) - (y_ + height_ * 0.5f);

	float sqDistanceToTarget = dX * dX + dY * dY;

	switch (state_)
	{
		case State::Idle:
			if (sqDistanceToTarget <= distanceAggro_ * distanceAggro_)
			{
				state_ = State::Circle;
			}
			break;
		case State::Circle:
			shootingCooldownClock_.update(deltaTime);
			if (shootingCooldownClock_.isDone())
			{
				shootingCooldownClock_.reset();

				for (float angle = 0.0f; angle < Constants::pi * 2.0f; angle += Constants::pi * 0.1f)
				{
					if (!bulletPool.isFull())
					{
						bulletPool.add(
							new Bullet(
								x_ + width_ * 0.5f, y_ + height_ * 0.5f,
								128.0f * cosf(angle), 128.0f * sinf(angle),
								10.0f,
								2.0f,
								false,
								TextureData::getInstance().getTexture(102)));
					}
				}
			}
			phaseDurationClock_.update(deltaTime);
			if (phaseDurationClock_.isDone())
			{
				phaseDurationClock_.reset();

				state_ = State::Target;
			}
			this->updateDeaggro_(sqDistanceToTarget);
			break;
		case State::Target:
			shootingCooldownClock_.update(deltaTime);
			if (shootingCooldownClock_.isDone())
			{
				shootingCooldownClock_.reset();

				float angleToTargetRad = atan2f(dY, dX);

				if (!bulletPool.isFull())
				{
					bulletPool.add(
						new Bullet(
							x_ + width_ * 0.5f, y_ + height_ * 0.5f,
							128.0f * cosf(angleToTargetRad), 128.0f * sinf(angleToTargetRad),
							10.0f,
							2.0f,
							false,
							TextureData::getInstance().getTexture(102)));
				}
			}
			phaseDurationClock_.update(deltaTime);
			if (phaseDurationClock_.isDone())
			{
				phaseDurationClock_.reset();

				state_ = State::Circle;
			}
			this->updateDeaggro_(sqDistanceToTarget);
			break;
	}

	this->updateBulletCollisions_(bulletPool, particlePool, false);
	if (!this->isLive())
	{
		particlePool.spawnExplosion(x_ + width_ * 0.5f, y_ + height_ * 0.5f, 40);
		if (!particlePool.isFull())
		{
			particlePool.add(
				new Particle(
					x_ + width_ * 0.5f, y_ + height_ * 0.5f,
					0.0f, 0.0f,
					30.0f,
					5.0f,
					TextureData::getInstance().getTexture(501)));
		}

		AudioData::getInstance().playSound(6);

		EventQueue::getInstance().send(new EventTargetDestroyed(id_));
	}
}

Boss *Boss::clone(float x, float y) const
{
	return new Boss(
		id_,
		x, y,
		maxHealth_,
		distanceAggro_,
		shootingCooldownClock_.getTargetSecs(),
		phaseDurationClock_.getTargetSecs(),
		*sprite_.getTexture());
}

void Boss::updateDeaggro_(float sqDistanceToTarget)
{
	if (sqDistanceToTarget >= distanceAggro_ * distanceAggro_)
	{
		state_ = State::Idle;
		shootingCooldownClock_.reset();
	}
}