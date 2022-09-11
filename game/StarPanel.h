#pragma once

#include "Star.h"
#include <SFML/Graphics/Drawable.hpp>
#include <vector>

class StarPanel : public sf::Drawable
{
public:
	StarPanel(uint16_t numStars, float distanceFactor);

	void updateFocus(float dX, float dY);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	std::vector<Star> stars_;
	float distanceFactor_;

	void randomize_();
};