#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>

class HealthUi : public sf::Drawable
{
public:
	HealthUi(float x, float y, uint16_t numIcons);

	void update(float healthRatio);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	std::vector<sf::Sprite> sprites_;
	sf::Sprite healthIconSprite_;
	uint16_t numIcons_;
};