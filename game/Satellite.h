#pragma once

#include "Entity.h"

class Satellite : public Entity
{
public:
	Satellite(float x, float y, float velAngleDeg, const sf::Texture &texture);

	void update(float deltaTime);

	void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
	float velAngleDeg_;
	float angleDeg_;
};