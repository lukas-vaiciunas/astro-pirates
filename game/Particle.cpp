#include "Particle.h"

Particle::Particle(
	float x, float y,
	float velX, float velY,
	float velAngleDeg,
	float durationSecs,
	const sf::Texture &texture)
	:
	Entity(x, y, texture),
	durationClock_(durationSecs),
	velX_(velX),
	velY_(velY),
	scale_(1.0f),
	velAngleDeg_(velAngleDeg),
	angleDeg_(0.0f),
	isLive_(true)
{
	x_ -= width_ * 0.5f;
	y_ -= height_ * 0.5f;

	sprite_.setPosition(x_, y_);
}

void Particle::update(float deltaTime)
{
	x_ += velX_ * deltaTime;
	y_ += velY_ * deltaTime;

	angleDeg_ += velAngleDeg_ * deltaTime;

	sprite_.setPosition(x_, y_);

	durationClock_.update(deltaTime);
	if (durationClock_.isDone())
	{
		durationClock_.reset();
		isLive_ = false;
	}

	scale_ = (durationClock_.getTargetSecs() - durationClock_.getCurrSecs()) / durationClock_.getTargetSecs();
}

void Particle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(scale_, scale_, x_ + width_ * 0.5f, y_ + height_ * 0.5f);
	states.transform.rotate(angleDeg_, x_ + width_ * 0.5f, y_ + height_ * 0.5f);

	Entity::draw(target, states);
}

bool Particle::isLive() const
{
	return isLive_;
}