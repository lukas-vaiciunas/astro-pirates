#include "Background.h"
#include "TextureData.h"
#include "Rng.h"
#include "Config.h"
#include <SFML/Graphics/RenderTarget.hpp>

Background::Background() :
	panel1_(100, 0.75f),
	panel2_(100, 0.5f),
	panel3_(100, 0.25f),
	lastFocusX_(0.0f),
	lastFocusY_(0.0f)
{}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(panel3_, states);
	target.draw(panel2_, states);
	target.draw(panel1_, states);
}

void Background::setFocus(float x, float y)
{
	float dX = lastFocusX_ - x;
	float dY = lastFocusY_ - y;

	panel1_.updateFocus(dX, dY);
	panel2_.updateFocus(dX, dY);
	panel3_.updateFocus(dX, dY);

	lastFocusX_ = x;
	lastFocusY_ = y;
}