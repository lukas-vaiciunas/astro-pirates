#include "TargetArrowUi.h"
#include "Config.h"
#include "Constants.h"
#include <SFML/Graphics/RenderTarget.hpp>

TargetArrowUi::TargetArrowUi(float offsetRadius, const sf::Texture &arrowTexture) :
	sf::Drawable(),
	arrowSprite_(arrowTexture),
	offsetRadius_(offsetRadius),
	targetX_(0.0f),
	targetY_(0.0f),
	angleToTargetRad_(0.0f),
	angleToTargetDeg_(0.0f),
	isClose_(false)
{}

void TargetArrowUi::update(float cX, float cY)
{
	float dX = targetX_ - cX;
	float dY = targetY_ - cY;

	float worldOffsetRadius = offsetRadius_ / Config::worldScale;

	isClose_ = dX * dX + dY * dY <= worldOffsetRadius * worldOffsetRadius;

	if (isClose_)
		return;

	angleToTargetRad_ = atan2f(dY, dX);
	angleToTargetDeg_ = angleToTargetRad_ * 180.0f / Constants::pi;

	arrowSprite_.setPosition(
		Config::windowWidth * 0.5f + offsetRadius_ * cosf(angleToTargetRad_),
		Config::windowHeight * 0.5f + offsetRadius_ * sinf(angleToTargetRad_));
}

void TargetArrowUi::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	if (isClose_)
		return;

	float cX = arrowSprite_.getPosition().x + arrowSprite_.getLocalBounds().width * 0.5f;
	float cY = arrowSprite_.getPosition().y + arrowSprite_.getLocalBounds().height * 0.5f;

	states.transform.scale(Config::worldScale, Config::worldScale, cX, cY);
	states.transform.rotate(angleToTargetDeg_, cX, cY);

	target.draw(arrowSprite_, states);
}

void TargetArrowUi::setTargetX(float x)
{
	targetX_ = x;
}

void TargetArrowUi::setTargetY(float y)
{
	targetY_ = y;
}