#pragma once

#include "Aabb.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Entity :
	public Aabb,
	public sf::Drawable
{
public:
	Entity(float x, float y, const sf::Texture &texture);
	Entity(float x, float y, float scale, const sf::Texture &texture);
	virtual ~Entity() {}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
protected:
	sf::Sprite sprite_;
};