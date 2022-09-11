#include "PulsatingText.h"
#include "FontData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

PulsatingText::PulsatingText(
	float cX, float cY,
	float velScale,
	float minScale,
	const std::string &str)
	:
	sf::Drawable(),
	state_(State::Contract),
	text_(),
	cX_(cX),
	cY_(cY),
	velScale_(velScale),
	minScale_(minScale),
	scale_(1.0f)
{
	text_.setFont(FontData::getInstance().getFont());
	text_.setCharacterSize(Config::largeTextSize_);
	text_.setLetterSpacing(2.0f);
	text_.setOutlineThickness(Config::worldScale * 2.0f);
	text_.setOutlineColor(sf::Color(220, 220, 220));
	text_.setFillColor(sf::Color(8, 8, 8));
	text_.setPosition(cX, cY);
	text_.setString(str);
	text_.setOrigin(
		text_.getLocalBounds().left + text_.getLocalBounds().width * 0.5f,
		text_.getLocalBounds().top + text_.getLocalBounds().height * 0.5f);
}

void PulsatingText::update(float deltaTime)
{
	switch (state_)
	{
		case State::Expand:
			scale_ += velScale_ * deltaTime;
			if (scale_ >= 1.0f)
			{
				scale_ = 1.0f;
				state_ = State::Contract;
			}
			break;
		case State::Contract:
			scale_ -= velScale_ * deltaTime;
			if (scale_ <= minScale_)
			{
				scale_ = minScale_;
				state_ = State::Expand;
			}
			break;
	}
}

void PulsatingText::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	states.transform.scale(scale_, scale_, cX_, cY_);
	
	target.draw(text_, states);
}