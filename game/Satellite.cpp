#include "Satellite.h"

Satellite::Satellite(float x, float y, float velAngleDeg, const sf::Texture &texture) :
	Entity(x, y, texture),
	velAngleDeg_(velAngleDeg),
	angleDeg_(0.0f)
{}

void Satellite::update(float deltaTime)
{
	angleDeg_ += velAngleDeg_ * deltaTime;
}

void Satellite::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.rotate(angleDeg_, x_ + width_ * 0.5f, y_ + height_ * 0.5f);

	Entity::draw(target, states);
}