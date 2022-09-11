#include "DestructibleEntity.h"
#include "BulletPool.h"
#include "ParticlePool.h"

DestructibleEntity::DestructibleEntity(float x, float y, float maxHealth, const sf::Texture &texture) :
	Entity(x, y, texture),
	Destructible(maxHealth)
{}

bool DestructibleEntity::updateBulletCollisions_(
	const BulletPool &bulletPool,
	ParticlePool &particlePool,
	bool isFriendly)
{
	for (auto it = bulletPool.begin(); it != bulletPool.end(); ++it)
	{
		if ((*it)->isFromPlayer() != isFriendly && this->isCollidingWith(**it))
		{
			this->hurt((*it)->getDamage());
			(*it)->kill();

			if (!this->isLive())
				return true;
			else
			{
				particlePool.spawnSparks(x_ + width_ * 0.5f, y_ + height_ * 0.5f, 10);
			}

			return true;
		}
	}

	return false;
}