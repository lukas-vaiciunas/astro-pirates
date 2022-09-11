#pragma once

#include "Entity.h"

class Star : public Entity
{
public:
	Star(float windowX, float windowY, float scale, const sf::Texture &texture);

	void updateOffset(float dOffsetX, float dOffsetY);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setWindowX(float windowX);
	void setWindowY(float windowY);
	void setTexture(const sf::Texture &texture);

	float getWindowX() const;
	float getWindowY() const;
private:
	float offsetX_;
	float offsetY_;
	float scale_;
};