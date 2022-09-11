#include "EnemyPool.h"
#include <SFML/Graphics/RenderTarget.hpp>

EnemyPool::EnemyPool(uint16_t capacity) :
	Pool(capacity),
	sf::Drawable()
{}

void EnemyPool::update(
	float deltaTime,
	BulletPool &bulletPool,
	ParticlePool &particlePool,
	DestructibleEntity &target)
{
	for (uint16_t i = 0; i < numLive_; )
	{
		objects_[i]->update(deltaTime, bulletPool, particlePool, target);

		if (!objects_[i]->isLive())
		{
			this->removeAtIndex_(i);
		}
		else ++i;
	}
}

void EnemyPool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (uint16_t i = 0; i < numLive_; ++i)
	{
		target.draw(*objects_[i], states);
	}
}