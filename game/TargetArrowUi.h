#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class TargetArrowUi : public sf::Drawable
{
public:
	TargetArrowUi(float offsetRadius, const sf::Texture &arrowTexture);

	void update(float cX, float cY);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	void setTargetX(float x);
	void setTargetY(float y);
private:
	sf::Sprite arrowSprite_;
	float offsetRadius_;
	float targetX_;
	float targetY_;
	float angleToTargetRad_;
	float angleToTargetDeg_;
	bool isClose_;
};