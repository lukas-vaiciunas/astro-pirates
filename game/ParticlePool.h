#pragma once

#include "Pool.h"
#include "Particle.h"

class ParticlePool :
	public Pool<Particle>,
	public sf::Drawable
{
public:
	ParticlePool(uint16_t capacity);

	void update(float deltaTime);

	void spawnExplosion(float x, float y, uint16_t numParticles);
	void spawnSparks(float x, float y, uint16_t numParticles);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};