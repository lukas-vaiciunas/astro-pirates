#include "HealthUi.h"
#include "TextureData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

HealthUi::HealthUi(float x, float y, uint16_t numIcons) :
	sf::Drawable(),
	sprites_(numIcons, sf::Sprite(TextureData::getInstance().getTexture(605))),
	healthIconSprite_(TextureData::getInstance().getTexture(603)),
	numIcons_(numIcons)
{
	healthIconSprite_.setPosition(x, y);
	healthIconSprite_.setOrigin(
		healthIconSprite_.getLocalBounds().width * 0.5f,
		healthIconSprite_.getLocalBounds().height * 0.5f);
	healthIconSprite_.setScale(Config::worldScale, Config::worldScale);

	for (uint16_t i = 0; i < numIcons_; ++i)
	{
		sprites_[i].setPosition(
			x + healthIconSprite_.getLocalBounds().width * Config::worldScale + sprites_[i].getLocalBounds().width * Config::worldScale + sprites_[i].getLocalBounds().width * Config::worldScale * i * 2.0f,
			y);
		sprites_[i].setOrigin(
			sprites_[i].getLocalBounds().width * 0.5f,
			sprites_[i].getLocalBounds().height * 0.5f);
		sprites_[i].setScale(Config::worldScale, Config::worldScale);
	}
}

void HealthUi::update(float healthRatio)
{
	uint16_t numFullIcons = static_cast<uint16_t>(numIcons_ * healthRatio);

	for (uint16_t i = 0; i < numFullIcons; ++i)
	{
		sprites_[i].setTexture(TextureData::getInstance().getTexture(605));
	}

	for (uint16_t i = numFullIcons; i < numIcons_; ++i)
	{
		sprites_[i].setTexture(TextureData::getInstance().getTexture(604));
	}
}

void HealthUi::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(healthIconSprite_, states);

	for (const sf::Sprite &sprite : sprites_)
	{
		target.draw(sprite, states);
	}
}