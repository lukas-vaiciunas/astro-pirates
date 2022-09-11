#include "ParticlePool.h"
#include "Rng.h"
#include "TextureData.h"
#include <SFML/Graphics/RenderTarget.hpp>

ParticlePool::ParticlePool(uint16_t capacity) :
	Pool(capacity),
	sf::Drawable()
{}

void ParticlePool::update(float deltaTime)
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

void ParticlePool::spawnExplosion(float x, float y, uint16_t numParticles)
{
	std::mt19937 &eng = Rng::getInstance().getEng();
	std::uniform_real_distribution<float> velXDis(-64.0f, 64.0f);
	std::uniform_real_distribution<float> velYDis(-64.0f, 64.0f);
	std::uniform_real_distribution<float> velAngleDegDis(-30.0f, 30.0f);
	std::uniform_int_distribution<uint16_t> textureIdDis(401, 403);

	for(uint16_t i = 0; i < numParticles; ++i)
	{
		if (this->isFull())
			break;

		this->add(
			new Particle(
				x, y,
				velXDis(eng), velYDis(eng),
				velAngleDegDis(eng),
				1.0f,
				TextureData::getInstance().getTexture(textureIdDis(eng))));
	}
}

void ParticlePool::spawnSparks(float x, float y, uint16_t numParticles)
{
	std::mt19937 &eng = Rng::getInstance().getEng();
	std::uniform_real_distribution<float> velXDis(-64.0f, 64.0f);
	std::uniform_real_distribution<float> velYDis(-64.0f, 64.0f);
	std::uniform_real_distribution<float> velAngleDegDis(-30.0f, 30.0f);
	std::uniform_int_distribution<uint16_t> textureIdDis(402, 403);

	for (uint16_t i = 0; i < numParticles; ++i)
	{
		if (this->isFull())
			break;

		this->add(
			new Particle(
				x, y,
				velXDis(eng), velYDis(eng),
				velAngleDegDis(eng),
				0.5f,
				TextureData::getInstance().getTexture(textureIdDis(eng))));
	}
}

void ParticlePool::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	for (uint16_t i = 0; i < numLive_; ++i)
	{
		target.draw(*objects_[i], states);
	}
}