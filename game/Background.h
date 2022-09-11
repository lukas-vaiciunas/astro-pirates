#pragma once

#include "StarPanel.h"

class Background : public sf::Drawable
{
public:
	Background();

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setFocus(float x, float y);
private:
	StarPanel panel1_;
	StarPanel panel2_;
	StarPanel panel3_;

	float lastFocusX_;
	float lastFocusY_;
};