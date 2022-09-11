#include "Minion.h"
#include "BulletPool.h"
#include "ParticlePool.h"
#include "TextureData.h"
#include "EventQueue.h"
#include "Event.h"
#include "AudioData.h"
#include "Constants.h"

Minion::Minion(
	uint16_t id,
	float x, float y,
	float speed,
	float maxHealth,
	float distanceIdle,
	float distanceApproach,
	float distanceStationary,
	float distanceRetreat,
	float shootingCooldownSecs,
	const sf::Texture &texture)
	:
	Enemy(id, x, y, maxHealth, texture),
	state_(State::None),
	shootingCooldownClock_(shootingCooldownSecs),
	speed_(speed),
	distanceIdle_(distanceIdle),
	distanceApproach_(distanceApproach),
	distanceStationary_(distanceStationary),
	distanceRetreat_(distanceRetreat),
	velX_(0.0f),
	velY_(0.0f),
	angleRad_(0.0f),
	angleDeg_(0.0f)
{
	this->setState_(State::Idle);
}

void Minion::update(
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
			if (sqDistanceToTarget < distanceApproach_ * distanceApproach_)
			{
				this->setState_(State::Approach);
			}
			break;
		case State::Approach:
			this->updateAngle_(dX, dY);

			velX_ = speed_ * cosf(angleRad_);
			velY_ = speed_ * sinf(angleRad_);

			this->updateMovement_(deltaTime);
			this->updateShooting_(deltaTime, bulletPool);

			if (sqDistanceToTarget < distanceStationary_ * distanceStationary_)
			{
				this->setState_(State::Stationary);
			}
			break;
		case State::Stationary:
			this->updateAngle_(dX, dY);
			this->updateShooting_(deltaTime, bulletPool);

			if (sqDistanceToTarget > distanceStationary_ * distanceStationary_)
			{
				this->setState_(State::Approach);
			}
			else if (sqDistanceToTarget < distanceRetreat_ * distanceRetreat_)
			{
				this->setState_(State::Retreat);
			}
			break;
		case State::Retreat:
			this->updateAngle_(dX, dY);

			velX_ = -speed_ * cosf(angleRad_);
			velY_ = -speed_ * sinf(angleRad_);

			this->updateMovement_(deltaTime);
			this->updateShooting_(deltaTime, bulletPool);

			if (sqDistanceToTarget > distanceRetreat_ * distanceRetreat_)
			{
				this->setState_(State::Stationary);
			}
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

void Minion::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.rotate(angleDeg_, x_ + width_ * 0.5f, y_ + height_ * 0.5f);

	DestructibleEntity::draw(target, states);
}

Minion *Minion::clone(float x, float y) const
{
	return new Minion(
		id_,
		x, y,
		speed_,
		maxHealth_,
		distanceIdle_, distanceApproach_, distanceStationary_, distanceRetreat_,
		shootingCooldownClock_.getTargetSecs(),
		*sprite_.getTexture());
}

void Minion::updateMovement_(float deltaTime)
{
	float sqCurrSpeed = velX_ * velX_ + velY_ * velY_;

	if (sqCurrSpeed > speed_ * speed_)
	{
		float fixRatio = speed_ / sqrt(sqCurrSpeed);

		velX_ *= fixRatio;
		velY_ *= fixRatio;
	}

	x_ += velX_ * deltaTime;
	y_ += velY_ * deltaTime;

	sprite_.setPosition(x_, y_);
}

void Minion::updateShooting_(float deltaTime, BulletPool &bulletPool)
{
	shootingCooldownClock_.update(deltaTime);

	if (shootingCooldownClock_.isDone())
	{
		shootingCooldownClock_.reset();

		if (!bulletPool.isFull())
		{
			bulletPool.add(
				new Bullet(
					x_ + width_ * 0.5f, y_ + height_ * 0.5f,
					128.0f * cosf(angleRad_), 128.0f * sinf(angleRad_),
					10.0f,
					2.0f,
					false,
					TextureData::getInstance().getTexture(102)));
		}

		AudioData::getInstance().playSound(4);
	}
}

void Minion::updateAngle_(float dX, float dY)
{
	angleRad_ = atan2f(dY, dX);
	angleDeg_ = angleRad_ * 180.0f / Constants::pi;
}

void Minion::setState_(const State &state)
{
	if (state_ == state)
		return;

	state_ = state;

	switch (state_)
	{
		case State::Idle:
			velX_ = 0.0f;
			velY_ = 0.0f;
			shootingCooldownClock_.reset();
			break;
		case State::Stationary:
			velX_ = 0.0f;
			velY_ = 0.0f;
			break;
	}
}