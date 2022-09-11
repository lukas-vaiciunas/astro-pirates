#include "Star.h"

Star::Star(float windowX, float windowY, float scale, const sf::Texture &texture) :
	Entity(windowX, windowY, scale, texture),
	offsetX_(0.0f),
	offsetY_(0.0f),
	scale_(scale)
{
	sprite_.setScale(scale_, scale_);
}

void Star::updateOffset(float dOffsetX, float dOffsetY)
{
	offsetX_ += dOffsetX;
	offsetY_ += dOffsetY;
}

void Star::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.translate(offsetX_, offsetY_);

	Entity::draw(target, states);
}

void Star::setWindowX(float windowX)
{
	offsetX_ = windowX - x_;
}

void Star::setWindowY(float windowY)
{
	offsetY_ = windowY - y_;
}

void Star::setTexture(const sf::Texture &texture)
{
	sprite_.setTexture(texture, true);
}

float Star::getWindowX() const
{
	return x_ + offsetX_;
}

float Star::getWindowY() const
{
	return y_ + offsetY_;
}