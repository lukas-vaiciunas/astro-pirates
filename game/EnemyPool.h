#pragma once

#include "Pool.h"
#include "Enemy.h"

class EnemyPool :
	public Pool<Enemy>,
	public sf::Drawable
{
public:
	EnemyPool(uint16_t capacity);

	void update(
		float deltaTime,
		BulletPool &bulletPool,
		ParticlePool &particlePool,
		DestructibleEntity &target);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};