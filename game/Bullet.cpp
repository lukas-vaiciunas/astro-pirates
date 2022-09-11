#include "Bullet.h"
#include <SFML/Graphics/RenderTarget.hpp>

Bullet::Bullet(
	float x, float y,
	float velX, float velY,
	float damage,
	float durationSecs,
	bool isFromPlayer,
	const sf::Texture &texture)
	:
	Entity(x, y, texture),
	durationClock_(durationSecs),
	velX_(velX),
	velY_(velY),
	damage_(damage),
	isFromPlayer_(isFromPlayer),
	isLive_(true)
{
	x_ -= width_ * 0.5f;
	y_ -= height_ * 0.5f;

	sprite_.setPosition(x_, y_);
}

void Bullet::update(float deltaTime)
{
	x_ += velX_ * deltaTime;
	y_ += velY_ * deltaTime;

	sprite_.setPosition(x_, y_);

	durationClock_.update(deltaTime);
	if (durationClock_.isDone())
	{
		durationClock_.reset();
		isLive_ = false;
	}
}

void Bullet::kill()
{
	isLive_ = false;
}

float Bullet::getDamage() const
{
	return damage_;
}

bool Bullet::isFromPlayer() const
{
	return isFromPlayer_;
}

bool Bullet::isLive() const
{
	return isLive_;
}