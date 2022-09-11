#pragma once

class BulletPool;
class ParticlePool;

#include "Entity.h"
#include "Destructible.h"

class DestructibleEntity :
	public Entity,
	public Destructible
{
public:
	DestructibleEntity(float x, float y, float maxHealth, const sf::Texture &texture);
	virtual ~DestructibleEntity() {}
protected:
	bool updateBulletCollisions_(
		const BulletPool &bulletPool,
		ParticlePool &particlePool,
		bool isFriendly);
};