#include "Entity.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

Entity::Entity(float x, float y, const sf::Texture &texture) :
	Aabb(x, y, static_cast<float>(texture.getSize().x), static_cast<float>(texture.getSize().y)),
	sf::Drawable(),
	sprite_(texture)
{
	sprite_.setPosition(x_, y_);
}

Entity::Entity(float x, float y, float scale, const sf::Texture &texture) :
	Aabb(x, y, texture.getSize().x * scale, texture.getSize().y * scale),
	sf::Drawable(),
	sprite_(texture)
{}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}