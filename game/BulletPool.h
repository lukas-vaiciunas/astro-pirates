#pragma once

#include "Pool.h"
#include "Bullet.h"
#include <SFML/Graphics/Drawable.hpp>

class BulletPool :
	public Pool<Bullet>,
	public sf::Drawable
{
public:
	BulletPool(uint16_t capacity);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};