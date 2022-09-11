#pragma once

class BulletPool;
class ParticlePool;

#include "DestructibleEntity.h"
#include "Identifiable.h"

class Enemy :
	public DestructibleEntity,
	public Identifiable
{
public:
	Enemy(uint16_t id, float x, float y, float maxHealth, const sf::Texture &texture);

	virtual void update(
		float deltaTime,
		BulletPool &bulletPool,
		ParticlePool &particlePool,
		const DestructibleEntity &target) = 0;

	virtual Enemy *clone(float x, float y) const = 0;
};