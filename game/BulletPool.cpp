#include "BulletPool.h"
#include <SFML/Graphics/RenderTarget.hpp>

BulletPool::BulletPool(uint16_t capacity) :
	Pool(capacity),
	sf::Drawable()
{}

void BulletPool::update(float deltaTime)
{
	for (uint16_t i = 0; i < numLive_; )
	{
		objects_[i]->update(deltaTime);

		if (!objects_[i]->isLive())
		{
			this->removeAtIndex_(i);
		}
		else ++i;
	}
}

void BulletPool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (uint16_t i = 0; i < numLive_; ++i)
	{
		target.draw(*objects_[i], states);
	}
}