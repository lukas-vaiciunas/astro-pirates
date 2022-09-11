#include "Button.h"
#include "FontData.h"
#include "AudioData.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

Button::Button(float cX, float cY, const std::string &str, const sf::Texture &texture) :
	sf::Drawable(),
	state_(State::None),
	sprite_(texture),
	text_(),
	cX_(cX),
	cY_(cY),
	velScale_(0.75f),
	minScale_(0.75f),
	scale_(1.0f),
	isHovered_(false)
{
	sprite_.setPosition(
		cX - sprite_.getLocalBounds().width * 0.5f,
		cY - sprite_.getLocalBounds().height * 0.5f);

	text_.setFont(FontData::getInstance().getFont());
	text_.setCharacterSize(Config::smallTextSize_);
	text_.setFillColor(sf::Color(220, 220, 220));
	text_.setPosition(cX, cY);
	text_.setString(str);
	text_.setOrigin(
		text_.getLocalBounds().left + text_.getLocalBounds().width * 0.5f,
		text_.getLocalBounds().top + text_.getLocalBounds().height * 0.5f);
}

void Button::updateOnMouseMove(int mouseX, int mouseY)
{
	bool wasHovered = isHovered_;

	isHovered_ = mouseX > cX_ - sprite_.getLocalBounds().width * Config::worldScale * 0.5f
		&& mouseX < cX_ + sprite_.getLocalBounds().width * Config::worldScale * 0.5f
		&& mouseY > cY_ - sprite_.getLocalBounds().height * Config::worldScale * 0.5f
		&& mouseY < cY_ + sprite_.getLocalBounds().height * Config::worldScale * 0.5f;

	if (isHovered_ && !wasHovered)
	{
		AudioData::getInstance().playSound(1);
		state_ = State::Contract;
	}
	else if (wasHovered && !isHovered_)
	{
		scale_ = 1.0f;
		state_ = State::None;
	}
}

void Button::update(float deltaTime)
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

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::RenderStates spriteRenderStates = states;
	spriteRenderStates.transform.scale(Config::worldScale * scale_, Config::worldScale * scale_, cX_, cY_);

	sf::RenderStates textRenderStates = states;
	textRenderStates.transform.scale(scale_, scale_, cX_, cY_);

	target.draw(sprite_, spriteRenderStates);
	target.draw(text_, textRenderStates);
}

bool Button::isHovered() const
{
	return isHovered_;
}